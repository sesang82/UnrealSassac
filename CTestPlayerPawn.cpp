// Fill out your copyright notice in the Description page of Project Settings.


#include "CTestPlayerPawn.h"

// Sets default values
ACTestPlayerPawn::ACTestPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*
	�����ڿ����� �� �� ����(������ ���� �Լ�) :
	CreateDefaultSubobject ���ø� �Լ���.
	�𸮾��� U������Ʈ�� ��ӹ��� Ŭ������ ��ü�� �������ִ� �Լ���.
	<>���ٰ� staticMeshComponet�� ����� �ʹٸ�
	<> �ȿ��ٰ� Ÿ�� �̸��� �־��ָ� �ȴ�.

	���� ������ �����ϴ� �׷� ������ ������ �ϴ� �ֵ� ����ü�� �̸� �տ� t�� ���δٰ� �߾���.

	FName�� �̸��� �ٿ��� ?? ����ϴ� Ÿ���̴�.
	�𸮾� ������ �����ڵ� ���ڿ��� ����Ѵ�. 2����Ʈ wide char�� ����Ѵ�.
	���࿡ ���� �̸��� �ٿ��ְ� �ʹٸ� TEXT("") ��ũ�θ� ����Ѵ�.
	�̷��� �ϸ� �����ڵ� ���ڿ��� ������ش�.

	�ش� �Լ��� <>�� ������ Ÿ���� �ּҸ� ��ȯ���ش�.
	�׷��� �����Ѵٰ� Actor�� ���ԵǴ°� �ƴϴ�.
	�׳� ������ ���� ���̴�.


*/
	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	// �޽��� �ش� ������Ʈ ������Ʈ�� ���� �Ѹ��� �����Ѵ�.
	SetRootComponent(mMesh);

	// Camera�� �θ� Component�� Mesh�� �����Ѵ�.
	mCamera->SetupAttachment(mMesh);

	// ======= ī�޶� ��ǥ (�����ǥ, ������ǥ)
	// ��� ��ġ,��,������ �ñ��ϸ� �׳� �������� �˾ƺ���
	mCamera->SetRelativeLocation(FVector(-240.0, 0.0, 90.0));
	mCamera->SetRelativeRotation(FRotator(-20.0, 0.0, 0.0));

	// true�� �صθ� �𸮾� �����Ϳ����� �갡 ��� �ִ����� ǥ�����ش�.
	// ��ó���� �̿��ؼ� �����Ϳ����� �������� �ƴ����� �� ������ָ� ���� �ϴ�.
	// �Ʒ� ��ũ�δ� Character Ŭ���� �ȿ� ����.	
	// ���࿡ �Ʒ� �ɼ��� �ڴʰ� �߰��ϸ� �� ���Ŀ� ������� ��ü�� ��� �ִ����� ���̰�
	// ������ ������� ��� �Ⱥ���. �����ڴ� ��ü�� ������ ?? ȣ��Ǳ� ����.
#if WITH_EDITORONLY_DATA
	mMesh->bVisualizeComponent = true;
#endif
}

// Called when the game starts or when spawned
void ACTestPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACTestPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACTestPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

