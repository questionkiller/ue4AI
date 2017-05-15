// Fill out your copyright notice in the Description page of Project Settings.

#include "AITest.h"
#include "EnemyBear.h"
#include "EnemyBearAIController.h"
#include "AITestCharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "Delegate.h"


// Sets default values
AEnemyBear::AEnemyBear()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AEnemyBearAIController::StaticClass();

	totalHP = 100;
	AttackRange = 100;
	AttackDamage = 10;
	isDead = false;
	isAttacking = false;
	auto MMesh = AEnemyBear::GetMesh();

	bUseControllerRotationYaw = true;

	PawnSensor = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Pawn Sensor"));
	PawnSensor->SensingInterval = .25f;
	PawnSensor->bOnlySensePlayers = true;
	//周边视觉角
	PawnSensor->SetPeripheralVisionAngle(85.f);
	

	bodySphereTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("BodySphereTrigger"));
	bodySphereTrigger->SetSphereRadius(150.f);
	bodySphereTrigger->AttachTo(MMesh,"body",EAttachLocation::SnapToTarget);

	FColor HandsTriggerColor = FColor(0, 0, 255, 255);

	leftHandTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("LeftHandTrigger"));
	leftHandTrigger->SetSphereRadius(70.f);
	leftHandTrigger->AttachTo(MMesh, "hand_lf", EAttachLocation::SnapToTarget);
	leftHandTrigger->ShapeColor = HandsTriggerColor;
	leftHandTrigger->bGenerateOverlapEvents = 0;

	rightHandTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("RightHandTrigger"));
	rightHandTrigger->SetSphereRadius(70.f);
	rightHandTrigger->AttachTo(MMesh, "hand_rt", EAttachLocation::SnapToTarget);
	rightHandTrigger->ShapeColor = HandsTriggerColor;
	rightHandTrigger->bGenerateOverlapEvents = 0;

	//
	GetCharacterMovement()->NavAgentProps.AgentRadius = 400.f;
	GetCharacterMovement()->SetUpdateNavAgentWithOwnersCollisions(false);


}

// Called when the game starts or when spawned
void AEnemyBear::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyBear::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}


void AEnemyBear::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	//为pawnsensor组件注册代理function
	PawnSensor->OnSeePawn.AddDynamic(this, &AEnemyBear::OnSeePawn);
	PawnSensor->OnHearNoise.AddDynamic(this, &AEnemyBear::OnHearNoise);
	//为左右手注册代理function
	leftHandTrigger->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBear::OnHandTriggerOverlap);
	rightHandTrigger->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBear::OnHandTriggerOverlap);
}


void AEnemyBear::OnPerformAttack()
{
	isAttacking = true;
}

void AEnemyBear::OnPreAttack()
{
	leftHandTrigger->bGenerateOverlapEvents = 1;
	rightHandTrigger->bGenerateOverlapEvents = 1;
}

void AEnemyBear::OnPostAttack()
{
	isAttacking = false;
	leftHandTrigger->bGenerateOverlapEvents = 0;
	rightHandTrigger->bGenerateOverlapEvents = 0;
}

void AEnemyBear::OnHearNoise(APawn * OtherPawn, const FVector & Location, float Volume)
{

}

void AEnemyBear::OnSeePawn(APawn * OtherPawn)
{
	
}

void AEnemyBear::OnHandTriggerOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AAITestCharacter* const _tempPlayer = Cast<AAITestCharacter>(OtherActor);
	if (_tempPlayer) {
		leftHandTrigger->bGenerateOverlapEvents = 0;
		rightHandTrigger->bGenerateOverlapEvents = 0;
	}

}





