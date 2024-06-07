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

	// �޽��� �ٵ��� �ڽ����� ��´�. �̶��� �޽��� �浹�� ������Ѵ�. 
	mMesh->SetupAttachment(mBody);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Test/TestMesh/Cube.Cube'"));

	if (MeshAsset.Succeeded())
		mMesh->SetStaticMesh(MeshAsset.Object);

	// �޽��� no �ø����� �ؼ� �� �޽��� �浹�� �ȵǰ� �ƿ� ������ ���̴�.
	// �޽��� �浹 ������ �����ٰ� ��. �׷��� �ڽ��� �밳 �޽� �浹 ���ٰ� ��
	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// ĸ�� ������Ʈ�� �浹ä���� �������ش�. 
	// �Ʊ� ���� Player �浹�� ���ش�. �׷� �� player �浹 ������ ĸ��������Ʈ��
	// �浹�� �����ϰ� �ȴ�.
	mBody->SetCollisionProfileName(TEXT("Item"));

	// �޽��� ���� Ŭ���غ��� �ٻ�ġ ���� �� �� �ִ�. 100 * 100 * 100 
	// �̷������� �Ǿ��ִ�............
	/*	
	�������� �ڽ� ũ�⸦ 50 50���� �صθ� �ڽ� ��ü�� ���� ���̷� �����Ǿ������� �� �� ���� ���̴�.	
	�̰� �̿��ؼ� 50�� �ָ� �� ���̰� 1m�� �ڽ��� �ϳ� ��������� �ȴ�.	
	*/
	mBody->SetBoxExtent(FVector(50.0, 50.0, 50.0));

	// ���࿡ �浹ü�� �޽��� ����ִ� ���, �޽��� �浹ü�� ���� �Ŀ� ���� �޽�����
	// �̰� �ڵ� ���� �� �� �ֵ��� �ڵ�� �����س��´�.
	mMesh->SetRelativeLocation(FVector(0.0, -50.0, -50.0));
}

// Called when the game starts or when spawned
void ACTestItem::BeginPlay()
{
	Super::BeginPlay();
	
	// Block �϶�
	//mBody->OnComponentHit

	// === mBody->OnComponentBeginOverlap ���� �Լ� ������ֱ� 
	// Overlap �϶�
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

	// ���Ӹ�带 ��ȯ�ؼ� ��忡 �ִ� �Լ��� ȣ���Ͽ� ������ ����ϰ� �Ѵ�. 
	// ����� ���忡���� ���� ���� ���Ӹ�带 �� �� ����. ������
	// 1���� ���Ӹ�常 �� �� �ִ�. �̰� ���� ����. 
	ACTestGameMode* GameMode =
		GetWorld()->GetAuthGameMode<ACTestGameMode>();

	if (GameMode)
		GameMode->AddScore(10);

	// ������ ��ü�� �ε�ġ�� ��� ������� �Ѵ�. 
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

