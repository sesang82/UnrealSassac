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
	// 델리게이트 변수를 만들 때는 반드시 UFUNCTION()을 써줘야한다.
	// 만약에 그냥 이거 없이 C++함수를 만들면 블루프린트에서 써먹을 수 없다.	
	// 즉 함수에 옵션을 부여해줄 수 있는 기능이라고 생각하면 된다.	
	// 이걸 부여하고 CALL 블루프린트 이런걸 하면 블루프린트에서 해당 함수를 호출가능하게 할 수 있다.	
	/*	
	(( UFUNCTION()에 붙여쓸 수 있는 것들))	
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
	// ========= Begin Overlap 함수 형태 
	UFUNCTION()

	// 해당 함수의 인자는 DECLARE_DYNAMIC_MULTICAST_SPARSE_CELEGATE 함수의 인자를 그대로 긁어온다.
	// 쌤은 여기서 6개 함수꺼로 사용. 이런식으로 해당 함수에 가서 인자 그대로 긁어와서 
	// end overlap 때 호출할 함수도 만들어줄 수 있다. 
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
