// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "EnemyBear.generated.h"

UCLASS()
class AITEST_API AEnemyBear : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyBear();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	//
	virtual void PostInitializeComponents() override;
	//3��trigger
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Triggers, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* bodySphereTrigger;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Triggers, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* leftHandTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Triggers, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* rightHandTrigger;
	//behavior
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyBehaviors")
		float totalHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyBehaviors")
		float AttackRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyBehaviors")
		float AttackDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyBehaviors")
		bool isDead;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyBehaviors")
		bool isAttacking;
	//��֪���
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bear AI")
		class UPawnSensingComponent* PawnSensor;
	//��Ϊ����
	UPROPERTY(EditAnywhere, Category = "Bear AI")
		class UBehaviorTree* BearBehaviorTree;
	//attack��ǰ��
	UFUNCTION(BlueprintCallable, Category = "Bear AI")
		void OnPerformAttack();
	UFUNCTION(BlueprintCallable, Category = "Bear AI")
		void OnPreAttack();
	UFUNCTION(BlueprintCallable, Category = "Bear AI")
		void OnPostAttack();
	//UFUNCTION(BlueprintCallable, Category = "Bear AI");
	//sensor����µĹ���
	UFUNCTION()
		void OnHearNoise(APawn* OtherPawn,const FVector &Location,float Volume);
	UFUNCTION()
		void OnSeePawn(APawn* OtherPawn);
	//����������
	UFUNCTION() 
		void OnHandTriggerOverlap(UPrimitiveComponent* OverlappedComponent ,class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	FORCEINLINE class USphereComponent* GetBodySphereTrigger() const { return bodySphereTrigger; }
};
