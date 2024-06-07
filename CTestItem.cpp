// Fill out your copyright notice in the Description page of Project Settings.


#include "CTestItem.h"
#include "CTestGameMode.h"

// Sets default values
ACTestItem::ACTestItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mBody = CreateDefaultSubobject<UBoxComponent>(TEXT("Body"));
	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	SetRootComponent(mBody);

	// 메쉬를 바디의 자식으로 삼는다. 이때의 메쉬도 충돌을 꺼줘야한다. 
	mMesh->SetupAttachment(mBody);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Test/TestMesh/Cube.Cube'"));

	if (MeshAsset.Succeeded())
		mMesh->SetStaticMesh(MeshAsset.Object);

	// 메쉬는 no 컬리젼을 해서 이 메쉬는 충돌이 안되게 아예 빼버릴 것이다.
	// 메쉬는 충돌 있으면 안좋다고 함. 그래서 박쌤은 대개 메쉬 충돌 끈다고 함
	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// 캡슐 컴포넌트의 충돌채널을 지정해준다. 
	// 아까 만든 Player 충돌을 해준다. 그럼 그 player 충돌 내용대로 캡슐컴포넌트가
	// 충돌을 진행하게 된다.
	mBody->SetCollisionProfileName(TEXT("Item"));

	// 메쉬를 더블 클릭해보면 근사치 값을 볼 수 있다. 100 * 100 * 100 
	// 이런식으로 되어있는............
	/*	
	쉐이프의 박스 크기를 50 50으로 해두면 박스 객체는 절반 길이로 구성되어있음을 알 수 있을 것이다.	
	이걸 이용해서 50씩 주면 각 길이가 1m인 박스가 하나 만들어지게 된다.	
	*/
	mBody->SetBoxExtent(FVector(50.0, 50.0, 50.0));

	// 만약에 충돌체가 메쉬를 벗어나있는 경우, 메쉬를 충돌체에 맞춘 후에 다음 메쉬들은
	// 이게 자동 적용 될 수 있도록 코드로 고정해놓는다.
	mMesh->SetRelativeLocation(FVector(0.0, -50.0, -50.0));
}

// Called when the game starts or when spawned
void ACTestItem::BeginPlay()
{
	Super::BeginPlay();
	
	// Block 일때
	//mBody->OnComponentHit

	// === mBody->OnComponentBeginOverlap 관련 함수 등록해주기 
	// Overlap 일때
	mBody->OnComponentBeginOverlap.AddDynamic(this,
		&ACTestItem::CollisionBeginOverlap);
	mBody->OnComponentEndOverlap.AddDynamic(this,
		&ACTestItem::CollisionEndOverlap);
}

// Called every frame
void ACTestItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACTestItem::CollisionBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{

	UE_LOG(Sac6, Warning, TEXT("Begin Overlap"));

	// 게임모드를 소환해서 모드에 있는 함수를 호출하여 점수를 기록하게 한다. 
	// 참고로 월드에서는 여러 개의 게임모드를 쓸 수 없다. 무조건
	// 1개의 게임모드만 쓸 수 있다. 이걸 잊지 말자. 
	ACTestGameMode* GameMode =
		GetWorld()->GetAuthGameMode<ACTestGameMode>();

	if (GameMode)
		GameMode->AddScore(10);

	// 아이템 객체가 부딪치는 즉시 사라지게 한다. 
	Destroy();
}

void ACTestItem::CollisionEndOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex)
{
	UE_LOG(Sac6, Warning, TEXT("End Overlap"));
}

