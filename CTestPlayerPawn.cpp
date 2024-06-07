// Fill out your copyright notice in the Description page of Project Settings.


#include "CTestPlayerPawn.h"

// Sets default values
ACTestPlayerPawn::ACTestPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*
	생성자에서만 쓸 수 있음(생성자 전용 함수) :
	CreateDefaultSubobject 템플릿 함수다.
	언리얼의 U오브젝트를 상속받은 클래스의 객체를 생성해주는 함수다.
	<>에다가 staticMeshComponet를 만들고 싶다면
	<> 안에다가 타입 이름을 넣어주면 된다.

	보통 데이터 저장하는 그런 간단한 정보를 하는 애들 구조체의 이름 앞에 t를 붙인다고 했었다.

	FName은 이름을 붙여줄 ?? 사용하는 타입이다.
	언리얼 엔진은 유니코드 문자열을 사용한다. 2바이트 wide char를 사용한다.
	만약에 내가 이름을 붙여주고 싶다면 TEXT("") 매크로를 사용한다.
	이렇게 하면 유니코드 문자열로 만들어준다.

	해당 함수는 <>에 지정한 타입의 주소를 반환해준다.
	그런데 생성한다고 Actor에 포함되는게 아니다.
	그냥 생성만 했을 뿐이다.


*/
	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	// 메쉬를 해당 오브젝트 컴포넌트들 중의 뿌리로 지정한다.
	SetRootComponent(mMesh);

	// Camera의 부모 Component로 Mesh를 지정한다.
	mCamera->SetupAttachment(mMesh);

	// ======= 카메라 좌표 (상대좌표, 절대좌표)
	// 어디가 피치,야,롤인지 궁금하면 그냥 움직여서 알아보기
	mCamera->SetRelativeLocation(FVector(-240.0, 0.0, 90.0));
	mCamera->SetRelativeRotation(FRotator(-20.0, 0.0, 0.0));

	// true로 해두면 언리얼 에디터에서만 얘가 어디에 있는지를 표시해준다.
	// 전처리기 이용해서 에디터에서만 보여줄지 아닐지도 더 명시해주면 좋긴 하다.
	// 아래 매크로는 Character 클래스 안에 있음.	
	// 만약에 아래 옵션을 뒤늦게 추가하면 그 이후에 만들어진 객체가 어디에 있는지만 보이고
	// 그전에 만들어진 얘는 안보임. 생성자는 객체가 생성될 ?? 호출되기 때문.
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

