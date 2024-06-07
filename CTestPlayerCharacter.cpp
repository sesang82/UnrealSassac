// Fill out your copyright notice in the Description page of Project Settings.


#include "CTestPlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputData.h"
#include "CTestPlayerPawn.h"
#include "CTestShield.h"

// Sets default values
ACTestPlayerCharacter::ACTestPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// === ������Ʈ �����Ѵ�.
	mArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	mRotation = CreateDefaultSubobject<USceneComponent>(TEXT("Rotation"));

	//�� ������Ʈ�� �ƴ϶� ��Ʈ ������Ʈ�� ���� �ʿ� ����.(�� ������Ʈ�� ���� ������
	// �ڵ����� ������ ���ݱ��� rottcomponent�� �������ִ� ���ŷο��� ����� ��)
	//  ������ �׷��⿡ �� �༮�� � ������Ʈ�� ������Ʈ�� �༮������ ����������Ѵ�. 
	mRotMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotMovement"));

	// rotation ������Ʈ�� ������Ʈ�� �༮���� ��������
	mRotation->SetupAttachment(RootComponent);

	mRotMovement->SetUpdatedComponent(mRotation);

	mArm->SetupAttachment(RootComponent); // arm�� �ֻ��� root������Ʈ�� ����ش�.


	mCamera->SetupAttachment(mArm); // ī�޶��� �θ�� arm�� ����ش�.

	// �츮�� �����Ϳ� �ҷ��� ���̷��� �޽��� �ҷ��´�. �� ���� �޽��� �����Ϳ��� ���̷��� �޽� ���Ͽ�
	// ������ ���콺 ������ ���۷��� ���� ����� �ִ�. �װ� ������ ��.
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGideon/Characters/Heroes/Gideon/Skins/Tough/Meshes/Gideon_Tough.Gideon_Tough'"));

	if (MeshAsset.Succeeded())
	{
		// �޽����ٰ� ���̷��� ���� �޽��� �������ش�.

		GetMesh()->SetSkeletalMeshAsset(MeshAsset.Object);
	}

	// ĳ���Ϳ� �ִ� ĸ�� ������Ʈ�� ĸ�� ���� ���̸� �������ش�. (��ġ�� �����Ϳ��� ���ذ� �״��)
	GetCapsuleComponent()->SetCapsuleHalfHeight(94.f);


	// �� �޽��� �ٴڿ� �Ⱥپ �츮�� �޽��� ��ġ ȸ������ �ٲ������Ƿ� �̺κе� ������ش�.
	// �̷��� �صθ� �������� �� �޽��� �ҷ����� �̷��� ������ �� �״�� �ҷ�������. 
	GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, -94.0));
	GetMesh()->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	mArm->SetRelativeLocation(FVector(0.0, 0.0, 70.0));
	mArm->SetRelativeRotation(FRotator(-10.0, 0.0, 0.0));
	mArm->TargetArmLength = 500.f;

	// �� ��Ʈ�ѷ��� ĳ���Ϳ� ��Ī�ǰ� ȸ�� ����� ���شٰ� �����ϸ� �ȴ�.
	bUseControllerRotationYaw = true;

	// �� �Ʒ��� ��� ������ �Ǵ� ������ �־ false����.
	mArm->bInheritPitch = false;

	mArm->bEnableCameraLag = true;

	// FClassFinder�� �̿��Ͽ� Ŭ���� ������ �о������ �ϸ�
	// ����� �ڿ� �ݵ�� _C �� �ٿ��־�� �Ѵ�.
	static ConstructorHelpers::FClassFinder<AActor>
		AttackClass(TEXT("/Script/Engine.Blueprint'/Game/Test/TestBlueprint/BP_TestActor.BP_TestActor_C'"));

	if (AttackClass.Succeeded())
		mAttackClass = AttackClass.Class;

	// �޽��� no �ø����� �ؼ� �� �޽��� �浹�� �ȵǰ� �ƿ� ������ ���̴�.
	// �޽��� �浹 ������ �����ٰ� ��. �׷��� �ڽ��� �밳 �޽� �浹 ���ٰ� ��
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// ĸ�� ������Ʈ�� �浹ä���� �������ش�. 
	// �Ʊ� ���� Player �浹�� ���ش�. �׷� �� player �浹 ������ ĸ��������Ʈ��
	// �浹�� �����ϰ� �ȴ�. 
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
}

// Called when the game starts or when spawned
void ACTestPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// ���� ĳ���Ϳ� ���ǵǾ� �ִ� ��Ʈ�ѷ��� PlayerController��
	// �´��� Ȯ���ϰ� �´ٸ� EnhancedInputSubsystem �� ������
	// �Ѵ�.

	// �� Cast�� �𸮾󿡼� ���̳��� ĳ����ó�� ������ �Լ���.
	// ��ü������ UObject Ÿ������ ����ȯ�� �� �ְԲ� �س���. ���࿡ �߸��� ����ȯ�� �ҽ� nullptr ��ȯ
	APlayerController* PlayerController = 
		Cast<APlayerController>(GetController());

	if (PlayerController)
	{
		// �̰� �̿��Ͽ� �÷��̾� ��Ʈ�ѷ��� ������ �� �ִ�.
		UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		// Ŭ���� ����Ʈ ������Ʈ�� ���´�.
		const UTestInputData* InputData = GetDefault< UTestInputData>();

		// �̸� ���ؽ�Ʈ�� ���� �� �������� �� �� �ִ�.
		// ���ؽ�Ʈ => �׷��ϱ� IMC_Test ���� ���ϴ°�. ��, InputData�� CDO(Ŭ��������Ʈ������Ʈ)��
		// ����� ���̴�. uobject�� ��ӹ޴� �𸮾� ������Ʈ Ŭ�������� �� Ÿ������ CDO�� �ڵ�����
		// �������´�. �츮�� �� CDO�� �̿��ؼ� �� ���µ��� ������ ���⸸ �ϸ� �ȴ�.
		Subsystem->AddMappingContext(InputData->mDefaultContext,
			0);
	}
}

// Called every frame
void ACTestPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ���� ��Ÿ�� üũ
	// ��� �Ұ��� ������ �� �ð� ���
	if (!mShieldEnable)
	{
		mShieldTime += DeltaTime;

		if (mShieldTime >= mShieldCoolDown)
			mShieldEnable = true;
	}
}

// Called to bind functionality to input
void ACTestPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// ��ǲ ������Ʈ�� �̿��Ͽ� ȣ���� �༮�� �������ش�. 
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputCom =
		Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputCom)
	{
		// Ŭ���� ����Ʈ ������Ʈ�� ���´�.
		const UTestInputData* InputData = GetDefault< UTestInputData>();

		// �̷��� �ؼ� ȣ���� �Լ� ���� ����
		// ==== Ű�� �Է¿� ���� �Լ������� ���� �����Ѵ�. (���º���)
		// move Ű ����

		EnhancedInputCom->BindAction(InputData->mMove,
			ETriggerEvent::Triggered,
			this, &ACTestPlayerCharacter::MoveAction);

		EnhancedInputCom->BindAction(InputData->mRotation,
			ETriggerEvent::Triggered,
			this, &ACTestPlayerCharacter::RotationAction);

		EnhancedInputCom->BindAction(InputData->mAttack,
			ETriggerEvent::Started,
			this, &ACTestPlayerCharacter::AttackAction);

		EnhancedInputCom->BindAction(InputData->mShield,
			ETriggerEvent::Started,
			this, &ACTestPlayerCharacter::ShieldAction);

		EnhancedInputCom->BindAction(InputData->mTripleShot,
			ETriggerEvent::Started,
			this, &ACTestPlayerCharacter::TripleShotAction);

		//GetWorld()->SpawnActor<>();
	}
}

void ACTestPlayerCharacter::MoveAction(
	const FInputActionValue& Value)
{
	FVector	Axis = Value.Get<FVector>();

	AddMovementInput(GetActorForwardVector(), Axis.Y);

	// x���� �Է��� �� �ش� ���� ȣ��
	AddMovementInput(GetActorRightVector(), Axis.X);
}

void ACTestPlayerCharacter::RotationAction(
	const FInputActionValue& Value)
{
	FVector	Axis = Value.Get<FVector>();

	AddControllerYawInput(Axis.X);
	
	// GetWorld() => ���� ��ü�� �ٷ� ������� �Լ�. ������ actor�� �������ְ� �ִµ� �����θ� ����
	// ������ ������ �� ������ �ڽ��� ����� �������ְ� �ִ�. ������ �����ڿ����� ��� ����
	// ��ư �̰� ���ؼ� ��ŸŸ���� ���� �� �� �ִ�. 

	// ��������Ϳ� ���� ��ó�� ������ arm�� y���� ��ŸŸ���� ���Ͽ� ȸ���ǰԲ� ���ش�. 
	mArm->AddRelativeRotation(FRotator(
		Axis.Y * 90.0 * GetWorld()->GetDeltaSeconds(),
		0.0, 0.0));

	// AddOnScreenDebugMessage : ����Ʈ�� ���ϴ� ���ڿ���
	// ������ִ� �Լ��̴�.
	// �̷��� �صθ� �Է����� ���� float �� ������ �Ʒ� ���ڿ��� x�� y�� ������ش�.
	/*GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red,
		FString::Printf(TEXT("X : %f Y : %f"), Axis.X,
			Axis.Y));*/
}

void ACTestPlayerCharacter::AttackAction(
	const FInputActionValue& Value)
{
	FVector	Location = GetActorLocation() +
		GetActorForwardVector() * 100.f;

	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::Undefined;

	GetWorld()->SpawnActor<AActor>(mAttackClass, Location,
		GetActorRotation(), param);

	/*GetWorld()->SpawnActor<ACTestPlayerPawn>(GetActorLocation(),
		GetActorRotation());*/
}

void ACTestPlayerCharacter::ShieldAction(
	const FInputActionValue& Value)
{
	// ��� �Ұ��� ������ ��� ó�� ���� ��ȯ�Ѵ�.
	if (!mShieldEnable)
		return;

	// ���� ������ ���� true���� ���� false�� �ʱ�ȭ
	mShieldEnable = false;

	// �ð� ����� �����ؾ� �ϱ� ������ 0���� �ʱ�ȭ
	mShieldTime = 0.f;

	for (int32 i = 0; i < 4; ++i)
	{
		FVector	Location;
		FRotator	Rot = FRotator::ZeroRotator;
		
		switch (i)
		{
		case 0:
			Location = GetActorLocation() +
				GetActorForwardVector() * 200.f;
			break;
		case 1:
			Location = GetActorLocation() +
				GetActorRightVector() * 200.f;
			Rot.Yaw = 90.0;
			break;
		case 2:
			Location = GetActorLocation() +
				GetActorForwardVector() * -200.f;
			Rot.Yaw = 180.0;
			break;
		case 3:
			Location = GetActorLocation() +
				GetActorRightVector() * -200.f;
			Rot.Yaw = 270.0;
			break;
		}

		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::Undefined;

		// ACTestShield::StaticClass() : UClass ������ �����´�.
		ACTestShield* Shield = 
			GetWorld()->SpawnActor<ACTestShield>(
			ACTestShield::StaticClass(), Location,
				GetActorRotation() + Rot, param);

		Shield->AttachToComponent(mRotation,
			FAttachmentTransformRules::KeepWorldTransform);
	}
}

void ACTestPlayerCharacter::TripleShotAction(
	const FInputActionValue& Value)
{
	// �׳� ������ Ŭ������ �׽�Ʈ ���͸� ������ ������ 	?
	// �÷��̾��� ���⺤�͸� �̿��Ͽ� �Ѿ� 3���� ��ġ�� �������ش�. 
	FVector	Location = GetActorLocation() +
		GetActorForwardVector() * 100.f +
		GetActorRightVector() * -100.f;

	FRotator	Rot = GetActorRotation(); // ���� ȸ�� ���� �״�� �����ϰ���

	Rot.Yaw -= 45.f; // ó���� -45�� �����ϰ� �Ѵ�. �׸��� �̰��� �Ʒ��� ����

	// �Ѿ� 3���� �����. (�׷� ��ġ�� �߿�)
	for (int i = 0; i < 3; ++i)
	{
		// ������ ��ġ�� ���ڿ��� �ٲ㼭 ������غ� ���� �ִ�.
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, Location.ToString());

		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::Undefined;

	// ACTestShield::StaticClass() : UClass ������ �����´�.
	// ��ġ�� �Ʒ�ó�� �ع����� ��ġ�� �V���� ����. 
	// ���࿡ ��� Ư���� �����θ� ȸ���ϰ� ���ְ� �ʹٸ� ....�Ʒ�ó�� �����ϸ� �ȴ�.
	// ���࿡ �Ѿ��� ȸ���Ǹ鼭 ���ư��� �ϰ� �ʹٸ� ���� ���ư��� �� �����޴� ��ó�� �ϸ� �ȴ�.
		GetWorld()->SpawnActor<AActor>(
			mAttackClass, Location + GetActorRightVector() * i * 100.f,
			Rot + FRotator(0.0, i * 45.f, 0.0), param);
	}
}
