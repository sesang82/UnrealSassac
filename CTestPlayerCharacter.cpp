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

	// === 컴포넌트 생성한다.
	mArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	mRotation = CreateDefaultSubobject<USceneComponent>(TEXT("Rotation"));

	//씬 컴포넌트가 아니라서 루트 컴포넌트를 해줄 필요 없음.(씬 컴포넌트만 계층 구조를
	// 자동으로 가져서 지금까지 rottcomponent로 지정해주는 번거로움을 지녔던 것)
	//  하지만 그러기에 이 녀석은 어떤 컴포넌트를 업데이트할 녀석인지는 지정해줘야한다. 
	mRotMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotMovement"));

	// rotation 컴포넌트를 업데이트할 녀석으로 지정해줌
	mRotation->SetupAttachment(RootComponent);

	mRotMovement->SetUpdatedComponent(mRotation);

	mArm->SetupAttachment(RootComponent); // arm을 최상위 root컴포넌트로 잡아준다.


	mCamera->SetupAttachment(mArm); // 카메라의 부모로 arm을 잡아준다.

	// 우리가 에디터에 불러온 스켈레톤 메쉬를 불러온다. 이 참조 메쉬는 에디터에서 스켈레톤 메쉬 파일에
	// 오른쪽 마우스 누르면 레퍼런스 참조 기능이 있다. 그걸 누르면 됨.
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGideon/Characters/Heroes/Gideon/Skins/Tough/Meshes/Gideon_Tough.Gideon_Tough'"));

	if (MeshAsset.Succeeded())
	{
		// 메쉬에다가 스켈레톤 에셋 메쉬를 지정해준다.

		GetMesh()->SetSkeletalMeshAsset(MeshAsset.Object);
	}

	// 캐릭터에 있는 캡슐 컴포넌트의 캡슐 절반 높이를 지정해준다. (수치는 에디터에서 해준거 그대로)
	GetCapsuleComponent()->SetCapsuleHalfHeight(94.f);


	// 또 메쉬가 바닥에 안붙어서 우리가 메쉬의 위치 회전값도 바꿔줬으므로 이부분도 명시해준다.
	// 이렇게 해두면 다음번에 이 메쉬를 불러오면 이렇게 지정한 값 그대로 불러와진다. 
	GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, -94.0));
	GetMesh()->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	mArm->SetRelativeLocation(FVector(0.0, 0.0, 70.0));
	mArm->SetRelativeRotation(FRotator(-10.0, 0.0, 0.0));
	mArm->TargetArmLength = 500.f;

	// 이 컨트롤러는 캐릭터에 매칭되게 회전 기능을 켜준다고 생각하면 된다.
	bUseControllerRotationYaw = true;

	// 위 아래로 흔들어도 고정이 되는 현상이 있어서 false해줌.
	mArm->bInheritPitch = false;

	mArm->bEnableCameraLag = true;

	// FClassFinder를 이용하여 클래스 정보를 읽어오고자 하면
	// 경로의 뒤에 반드시 _C 를 붙여주어야 한다.
	static ConstructorHelpers::FClassFinder<AActor>
		AttackClass(TEXT("/Script/Engine.Blueprint'/Game/Test/TestBlueprint/BP_TestActor.BP_TestActor_C'"));

	if (AttackClass.Succeeded())
		mAttackClass = AttackClass.Class;

	// 메쉬는 no 컬리젼을 해서 이 메쉬는 충돌이 안되게 아예 빼버릴 것이다.
	// 메쉬는 충돌 있으면 안좋다고 함. 그래서 박쌤은 대개 메쉬 충돌 끈다고 함
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// 캡슐 컴포넌트의 충돌채널을 지정해준다. 
	// 아까 만든 Player 충돌을 해준다. 그럼 그 player 충돌 내용대로 캡슐컴포넌트가
	// 충돌을 진행하게 된다. 
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
}

// Called when the game starts or when spawned
void ACTestPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// 현재 캐릭터에 빙의되어 있는 컨트롤러가 PlayerController가
	// 맞는지 확인하고 맞다면 EnhancedInputSubsystem 을 얻어오게
	// 한다.

	// 이 Cast는 언리얼에서 다이나믹 캐스팅처럼 구현한 함수다.
	// 자체적으로 UObject 타입으로 형변환할 수 있게끔 해놨다. 만약에 잘못된 형변환을 할시 nullptr 반환
	APlayerController* PlayerController = 
		Cast<APlayerController>(GetController());

	if (PlayerController)
	{
		// 이걸 이용하여 플레이어 컨트롤러를 꺼내올 수 있다.
		UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		// 클래스 디폴트 오브젝트를 얻어온다.
		const UTestInputData* InputData = GetDefault< UTestInputData>();

		// 미리 컨텍스트를 여러 개 만들어놓고 쓸 수 있다.
		// 컨텍스트 => 그러니까 IMC_Test 파일 말하는거. 즉, InputData의 CDO(클래스디폴트오브젝트)를
		// 갖고올 것이다. uobject를 상속받는 언리얼 오브젝트 클래스들은 이 타입으로 CDO를 자동으로
		// 만들어놓는다. 우리는 이 CDO를 이용해서 이 에셋들을 가져다 쓰기만 하면 된다.
		Subsystem->AddMappingContext(InputData->mDefaultContext,
			0);
	}
}

// Called every frame
void ACTestPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 쉴드 쿨타임 체크
	// 사용 불가능 상태일 때 시간 계산
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
	// 인풋 컴포넌트를 이용하여 호출할 녀석을 지정해준다. 
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputCom =
		Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputCom)
	{
		// 클래스 디폴트 오브젝트를 얻어온다.
		const UTestInputData* InputData = GetDefault< UTestInputData>();

		// 이렇게 해서 호출할 함수 지정 가능
		// ==== 키의 입력에 따른 함수포인터 동작 서술한다. (에셋별로)
		// move 키 에셋

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

	// x방향 입력할 때 해당 벡터 호출
	AddMovementInput(GetActorRightVector(), Axis.X);
}

void ACTestPlayerCharacter::RotationAction(
	const FInputActionValue& Value)
{
	FVector	Axis = Value.Get<FVector>();

	AddControllerYawInput(Axis.X);
	
	// GetWorld() => 월드 물체를 바로 갖고오는 함수. 들어가보면 actor를 지원해주고 있는데 구현부를 보면
	// 레벨을 얻어오고 그 레벨을 자신의 월드로 지정해주고 있다. 때문에 생성자에서는 사용 못함
	// 암튼 이걸 통해서 델타타임을 갖고 올 수 있다. 

	// 블루프린터에 써준 것처럼 스프링 arm의 y값을 델타타임을 곱하여 회전되게끔 해준다. 
	mArm->AddRelativeRotation(FRotator(
		Axis.Y * 90.0 * GetWorld()->GetDeltaSeconds(),
		0.0, 0.0));

	// AddOnScreenDebugMessage : 뷰포트에 원하는 문자열을
	// 출력해주는 함수이다.
	// 이렇게 해두면 입력으로 들어온 float 값 각각을 아래 문자열인 x와 y에 출력해준다.
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
	// 사용 불가능 상태일 경우 처리 없이 반환한다.
	if (!mShieldEnable)
		return;

	// 쉴드 재사용을 위해 true였던 값을 false로 초기화
	mShieldEnable = false;

	// 시간 계산을 시작해야 하기 때문에 0으로 초기화
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

		// ACTestShield::StaticClass() : UClass 정보를 꺼내온다.
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
	// 그냥 만들어둔 클래스인 테스트 엑터를 가져다 쓸거임 	?
	// 플레이어의 방향벡터를 이용하여 총알 3개의 위치를 지정해준다. 
	FVector	Location = GetActorLocation() +
		GetActorForwardVector() * 100.f +
		GetActorRightVector() * -100.f;

	FRotator	Rot = GetActorRotation(); // 원본 회전 정보 그대로 유지하게함

	Rot.Yaw -= 45.f; // 처음엔 -45로 시작하게 한다. 그리고 이것을 아래에 적용

	// 총알 3개를 만든다. (그럼 위치가 중요)
	for (int i = 0; i < 3; ++i)
	{
		// 벡터의 위치를 문자열로 바꿔서 디버깅해볼 수도 있다.
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, Location.ToString());

		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::Undefined;

	// ACTestShield::StaticClass() : UClass 정보를 꺼내온다.
	// 위치를 아래처럼 해버리면 위치가 괯낞게 나옴. 
	// 만약에 어느 특정한 각도로만 회전하게 해주고 싶다면 ....아래처럼 적용하면 된다.
	// 만약에 총알이 회전되면서 돌아가게 하고 싶다면 쉴드 돌아가는 걸 적용햇던 것처럼 하면 된다.
		GetWorld()->SpawnActor<AActor>(
			mAttackClass, Location + GetActorRightVector() * i * 100.f,
			Rot + FRotator(0.0, i * 45.f, 0.0), param);
	}
}
