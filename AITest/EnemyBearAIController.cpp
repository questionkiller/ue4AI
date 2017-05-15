// Fill out your copyright notice in the Description page of Project Settings.

#include "AITest.h"
#include "AITestCharacter.h"
#include "EnemyBearAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

//构造
AEnemyBearAIController::AEnemyBearAIController() {

	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComp"));
	
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));

	//Specifies if this AI wants its own PlayerState.
	bWantsPlayerState = true;

}

void AEnemyBearAIController::Possess(APawn* InPawn) {
	Super::Possess(InPawn);
	//将inpawn强转为enemy
	AEnemyBear* _tempBear = Cast<AEnemyBear>(InPawn);
	//对象存在，且行为树也存在
	if (_tempBear && _tempBear->BearBehaviorTree) {
		//加载当前黑板
		BlackboardComp->InitializeBlackboard(*_tempBear->BearBehaviorTree->BlackboardAsset);
		EnemyKeyID = BlackboardComp->GetKeyID("Enemy");
		EnemyPositionKeyID = BlackboardComp->GetKeyID("EnemyPosition");
		//启动行为树
		BehaviorTreeComp->StartTree(*_tempBear->BearBehaviorTree);


	}
}

void AEnemyBearAIController::BeginInactiveState()
{
	Super::BeginInactiveState();
}

void AEnemyBearAIController::SetPlayer(APawn * InPawn)
{
	if (BlackboardComp) {
		BlackboardComp->SetValue<UBlackboardKeyType_Object>(EnemyKeyID, InPawn);
		BlackboardComp->SetValue<UBlackboardKeyType_Vector>(EnemyPositionKeyID, InPawn->GetActorLocation());
		//
		SetFocus(InPawn);
	}
}

AAITestCharacter * AEnemyBearAIController::GetPlayer() const
{
	if (BlackboardComp) {
		return Cast<AAITestCharacter>(BlackboardComp->GetValue<UBlackboardKeyType_Object>(EnemyKeyID));
	}
	return nullptr;
}



void AEnemyBearAIController::UpdateControlRotation(float deltatime, bool bUpdatePawn)
{
	FVector Center = GetFocalPoint();
	if (!Center.IsZero() && GetPawn()) {
		FVector Direction = Center - GetPawn()->GetActorLocation();
		FRotator NewRotation = Direction.Rotation();
		//限定yaw在0-360
		NewRotation.Yaw = FRotator::ClampAxis(NewRotation.Yaw);
		SetControlRotation(NewRotation);
		APawn* const _tempPawn = GetPawn();
		if (_tempPawn&&bUpdatePawn) {
			_tempPawn->FaceRotation(NewRotation, deltatime);
		}
	}
}

bool AEnemyBearAIController::PawnCanBeSeen(APawn * target)
{

	return true;
}

void AEnemyBearAIController::onSearchForPlayer() {
	APawn* _tempPawn = GetPawn();
	if (_tempPawn == NULL) {
		return;
	}

	const FVector _tempLoaction = _tempPawn->GetActorLocation();
	float BestDisSq = MAX_FLT;
	AAITestCharacter* PlayerPawn = NULL;

	for (FConstPawnIterator it = GetWorld()->GetPawnIterator();it;++it) {
		if (PawnCanBeSeen(*it)) {
			AAITestCharacter* TestPawn = Cast<AAITestCharacter>(*it);
			AEnemyBear* const _testEnemy = Cast<AEnemyBear>(TestPawn);
			if (_testEnemy){
			}
			else
			{
				//还活着
				if (TestPawn) {
					//向量的平方
					const float _distanceSq = (TestPawn->GetActorLocation() - _tempLoaction).SizeSquared();
					if (_distanceSq < BestDisSq) {
						BestDisSq = _distanceSq;
						PlayerPawn = TestPawn;
					}
				}
			}
		}

	}
	if (PlayerPawn) {
		SetPlayer(PlayerPawn);
	}
}