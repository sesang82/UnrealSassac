// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "CTestPlayerCharacter.generated.h"

UCLASS()


/*
ACharacter에서 private 멤버를 보면 받아놓은 메쉬나 그런것들을 접근못하게 막았다.
이 때문에 get 함수를 지원해주는데 우린 이걸 이용해서 메쉬를 꺼내오면 된다.

*/

class SAC6_API ACTestPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACTestPlayerCharacter();

protected:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* mArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* mCamera;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* mRotation;

	// 방패 빙글빙글 돌리게 할라고 만들어둠
	UPROPERTY(VisibleAnywhere)
	URotatingMovementComponent* mRotMovement;

	// TSubclassOf : UClass 정보를 저장하는 템플릿 객체이다.
	TSubclassOf<AActor>	mAttackClass;

	// === 쿨타임을 위한 것 
	bool	mShieldEnable = true;
	float	mShieldTime = 0.f;
	float	mShieldCoolDown = 6.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// 컨트롤러를 맵핑할 때 Vector2로 해줬지만 c++에서는 어떤 요소가 들어올지 모르기 때문에
// 일단 아래처럼 해주면 된다. 

	void MoveAction(const FInputActionValue& Value);
	void RotationAction(const FInputActionValue& Value);
	void AttackAction(const FInputActionValue& Value);
	void ShieldAction(const FInputActionValue& Value);
	void TripleShotAction(const FInputActionValue& Value);
};
