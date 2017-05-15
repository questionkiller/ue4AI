// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "EnemyBear.h"
#include "AITestCharacter.h"
#include "EnemyBearAIController.generated.h"

/**
 * 
 */
UCLASS()
class AITEST_API AEnemyBearAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyBearAIController();
	//�ڰ�
	UPROPERTY(transient)
		UBlackboardComponent* BlackboardComp;
	//��Ϊ�����
	UPROPERTY(transient)
		UBehaviorTreeComponent* BehaviorTreeComp;

	//��дpossess
	virtual void Possess(class APawn* InPawn) override;
	//��дbegin inactive state
	virtual void BeginInactiveState() override;

	//ˢ��enemy״̬
	UFUNCTION(BlueprintCallable, Category = Behavior)
		void SetPlayer(class APawn* InPawn);
	//��ȡplayer
	UFUNCTION(BlueprintCallable, Category = Behavior)
		class AAITestCharacter* GetPlayer() const;

	//UFUNCTION(BlueprintCallable, Category = Behavior)
	 virtual void UpdateControlRotation(float deltatime, bool bUpdatePawn = true) override;
	UFUNCTION(BlueprintCallable, Category = Behavior)
		bool PawnCanBeSeen(APawn* target);
	UFUNCTION(BlueprintCallable, Category = Behavior)
		void onSearchForPlayer();
	/*UFUNCTION(BlueprintCallable, Category = Behavior)
		void takeAwalk();
	UFUNCTION(BlueprintCallable, Category = Behavior)
		void walkBack();*/
protected:
	int32 EnemyKeyID;
	int32 EnemyPositionKeyID;
	
	

};
