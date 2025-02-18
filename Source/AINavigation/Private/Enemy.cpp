// Fill out your copyright notice in the Description page of Project Settings.


#include "AINavigation/Public/Enemy.h"
#include "TimerManager.h"
#include "AIController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Navigation/PathFollowingComponent.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	PawnSensingComponent->SightRadius = 200.f;
	PawnSensingComponent->SetPeripheralVisionAngle(45.f);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	EnemyController = Cast<AAIController>(GetController());
	CurrentIndex = 0;

	PatrolTarget = UpdateSelectedTarget();
	Move(PatrolTarget);
	
	PawnSensingComponent->OnSeePawn.AddDynamic(this, &AEnemy::PawnSeen);
}

bool AEnemy::InTargetRange(AActor* Target, double Range)
{
	if (Target == nullptr) return false;
	
	const double DistanceToTarget = (Target->GetActorLocation() - GetActorLocation()).Size();
	
	return DistanceToTarget <= Range;
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AgentState == EAgentState::EAS_Patrolling)
	{
		CheckPatrolTarget();
	}
	
	
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemy::PatrolTimerFinished()
{
	Move(PatrolTarget);
}

void AEnemy::PawnSeen(APawn* SeenPawn)
{
	UE_LOG(LogTemp, Warning, TEXT("PawnSeen"));
}

void AEnemy::Move(AActor* Target)
{
	if (EnemyController == nullptr || Target == nullptr) return;

	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalActor(Target);
	MoveRequest.SetAcceptanceRadius(20.f);
	EnemyController->MoveTo(MoveRequest);
        
	DrawDebugSphere(GetWorld(), Target->GetActorLocation(), 10.f, 18, FColor::Green);
}

AActor* AEnemy::UpdateSelectedTarget()
{
	const int32 NumberOfPatrolTargets = PatrolTargetArray.Num();

	if (NumberOfPatrolTargets == 0) return nullptr;
	AActor* NewTarget  = PatrolTargetArray[CurrentIndex];
	CurrentIndex = (CurrentIndex + 1) % NumberOfPatrolTargets;
	
	return NewTarget;
}

void AEnemy::CheckPatrolTarget()
{
	if (InTargetRange(PatrolTarget, PatrolRange))
	{
		PatrolTarget = UpdateSelectedTarget();

		GetWorldTimerManager().SetTimer(PatrolTimer, this, &AEnemy::PatrolTimerFinished, GetRandomDelay());
	}
}

float AEnemy::GetRandomDelay()
{
	return UKismetMathLibrary::RandomFloatInRange(MinPatrolWait, MaxPatrolWait);
}
