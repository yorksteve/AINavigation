// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class AINAVIGATION_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

	UPROPERTY()
	class AAIController* EnemyController;

	UPROPERTY(EditInstanceOnly, Category="AI Navigation")
	AActor* PatrolTarget;

	// Array of patrol targets
	UPROPERTY(EditInstanceOnly, Category="AI Navigation")
	TArray<AActor*> PatrolTargetArray;

	UPROPERTY(EditAnywhere, Category="AI Navigation")
	double PatrolRange = 200.f;

	FTimerHandle PatrolTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool InTargetRange(AActor* Target, double Range);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void PatrolTimerFinished();

private:
	void Move(AActor* Target);

	AActor* UpdateSelectedTarget();

	int32 CurrentIndex = 0;
};
