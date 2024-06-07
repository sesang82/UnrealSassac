// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "CTestItem.generated.h"

UCLASS()
class SAC6_API ACTestItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACTestItem();

protected:
	// ��������Ʈ ������ ���� ���� �ݵ�� UFUNCTION()�� ������Ѵ�.
	// ���࿡ �׳� �̰� ���� C++�Լ��� ����� �������Ʈ���� ����� �� ����.	
	// �� �Լ��� �ɼ��� �ο����� �� �ִ� ����̶�� �����ϸ� �ȴ�.	
	// �̰� �ο��ϰ� CALL �������Ʈ �̷��� �ϸ� �������Ʈ���� �ش� �Լ��� ȣ�Ⱑ���ϰ� �� �� �ִ�.	
	/*	
	(( UFUNCTION()�� �ٿ��� �� �ִ� �͵�))	
	https://dev.epicgames.com/documentation/ko-kr/unreal-engine/ufunctions-in-unreal-engine?application_version=5.3
	*/

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* mBody;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* mMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// ========= Begin Overlap �Լ� ���� 
	UFUNCTION()

	// �ش� �Լ��� ���ڴ� DECLARE_DYNAMIC_MULTICAST_SPARSE_CELEGATE �Լ��� ���ڸ� �״�� �ܾ�´�.
	// ���� ���⼭ 6�� �Լ����� ���. �̷������� �ش� �Լ��� ���� ���� �״�� �ܾ�ͼ� 
	// end overlap �� ȣ���� �Լ��� ������� �� �ִ�. 
	void CollisionBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void CollisionEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
};
