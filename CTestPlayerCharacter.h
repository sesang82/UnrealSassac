// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "CTestPlayerCharacter.generated.h"

UCLASS()


/*
ACharacter���� private ����� ���� �޾Ƴ��� �޽��� �׷��͵��� ���ٸ��ϰ� ���Ҵ�.
�� ������ get �Լ��� �������ִµ� �츰 �̰� �̿��ؼ� �޽��� �������� �ȴ�.

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

	// ���� ���ۺ��� ������ �Ҷ�� ������
	UPROPERTY(VisibleAnywhere)
	URotatingMovementComponent* mRotMovement;

	// TSubclassOf : UClass ������ �����ϴ� ���ø� ��ü�̴�.
	TSubclassOf<AActor>	mAttackClass;

	// === ��Ÿ���� ���� �� 
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
	// ��Ʈ�ѷ��� ������ �� Vector2�� �������� c++������ � ��Ұ� ������ �𸣱� ������
// �ϴ� �Ʒ�ó�� ���ָ� �ȴ�. 

	void MoveAction(const FInputActionValue& Value);
	void RotationAction(const FInputActionValue& Value);
	void AttackAction(const FInputActionValue& Value);
	void ShieldAction(const FInputActionValue& Value);
	void TripleShotAction(const FInputActionValue& Value);
};
