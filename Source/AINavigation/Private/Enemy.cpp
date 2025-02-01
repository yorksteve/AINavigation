// Fill out your copyright notice in the Description page of Project Settings.


#include "AINavigation/Public/Enemy.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	EnemyController = Cast<AAIController>(GetController());
	if (EnemyController && PatrolTarget)
	{
		FAIMoveRequest MoveRequest = FAIMoveRequest(PatrolTarget);
		MoveRequest.SetAcceptanceRadius(20.f);

		FNavPathSharedPtr NavPath;
		
		EnemyController->MoveTo(MoveRequest, &NavPath);

		DrawDebugSphere(GetWorld(), PatrolTarget->GetActorLocation(), 10.f, 18, FColor::Red);
	}
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

