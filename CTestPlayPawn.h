// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// 엔진에서 지원하는 코드는 내가 만든 거랑 순환참조 문제가 발생할 일이 없으니 걱정 ㄴ
// 언리얼의 기본 기능(EngineMinimal로 바꿔서 쓰면 카메라까지 포함된 채로 들어오게됨) 
// 아니면 공용 헤더파일을 하나 파서 거기다가 #include를 모아두고 써도 됨.
#include "EngineMinimal.h" 
#include "GameFramework/Pawn.h"
#include "CTestPlayPawn.generated.h" // 절대 지우지 말기 


	/*
	* GENERATED_BODY
	언리얼에서 필요한 코드를 자동으로 추가해주는 매크로다.
	때문에 절대로 지우면 안됨.
	*/


UCLASS()
class SAC6_API ACTestPlayPawn : public APawn
{

	GENERATED_BODY()


public:
	// Sets default values for this pawn's properties
	ACTestPlayPawn();

protected:
	/*
	* UPROPERTY:
	* 컴포넌트에 대해서만 쓸 수 있는 기능이다.
	언리얼 오브젝트 클래스에서 사용할 수 있는 기능이다(언리얼 에디터에서 수정가능하게 해주는 것)
	클래스의 멤버 변수마다 사용 가능하다. 써도 그만 안써도 그만인 기능
	에디터와 연결되는 등의 특수한 옵션 설정을 해줄 때 사용한다.
	이걸 안하면 에디터 창의 디테일에 들어가도 아무것도 바꿔줄 수 없음.
	C++에서만 제어할 수 있기 때문. (네이티브 컴포넌트는 C++에서 Fproperty로 선언시 편집 가능합니다 => C++에서만 사용 가능하다는 뜻)
	https://dev.epicgames.com/documentation/ko-kr/unreal-engine/unreal-engine-uproperties?application_version=5.3
	*/

	UPROPERTY(visibleanywhere);

	//TObjectPtr<UStaticMeshComponent> mMesh1;
	UStaticMeshComponent* mMesh; // 일반 포인터 

	UPROPERTY(visibleanywhere);

	// 카메라가 지정되지 않았다고 뜬다는건 컴포넌트를 인지못하고 있다는 것.
	// 이를 위해서는 '헤더파일'을 추가해야한다. 왜냐하면 카메라 컴포넌트가 어디에 있는지를 알아야하기때문
	/*
	구글에다가 ucameracomponent라고 쳐보면됨.
	
	*/
	UCameraComponent* mCamera; 



protected:
	/*
	플레이어가 시작될 때 호출된다. 에디터에서는 플레이 버튼을 누르면 플레이어가 시작됐다고 생각한다.
	플레이어 시작 시 객체마다 최초 1회만 호출 
	게임 시작 전에 액터에 메쉬나 이런게 다 준비가 된 후에 호출된다. 

	비긴이 존재하는 이유?
	객체를 생성해야 일단 게임에 나올 것이다.
	그때 생성자가 무조건 호출될 것이다. 근데 우리가 게임을 만들기 위해서 여러 개 배치하다보면 무거울 거다.
	그 다음에 플레이를 누른다?? 프로그래머들 입장에선 내가 플레이 시작할 때 뭔가 바뀐 걸 반영하고 싶어~
	그래서 비긴 함수에 그런걸 써놓으면 플레이 눌렀을 떄 최초 1회 호출된다.

	혹은 On컨트럭션??? 라는게 있다. 에디터 내용에 변화가 있으면 실시간으로 변화된 정보를 감지할 수 있는 초기화코드다.
	begin대신 쓸 수 있다고 함. 변화될때만 최초 1회만 실행되는거라고 함.

	*/
	virtual void BeginPlay() override;

public:	
	/*
	매프레임마다 호출된다. 무한루프를 돌고 있는 while문 안에서 동작됨
	마치 빙고 게임을 만들었을 떄와 똑같다. 
	매 프레임이란 말은 loop를 한번 돌 때를 말한다.
	60프레임 이런 얘기 들어봤을 거다. 게임이 만약에 144 프레임이라면
	1초동안 이 loop가 144번 돈다는 얘기다. 근데 여기에는 델타타임이란게 들어온다.

	이 개념은 매우 중요함. 
	
	델타타임 : 한프레임이 동작할 떄 흐른 시간을 의미
	*/
	virtual void Tick(float DeltaTime) override;


	/*
	Input컴포넌트라는 애가 있다. 입력과 관계된 녀석이다. 언리얼 엔진은 멀티플랫폼을 지원한다.
	근데 플랫폼마다 입력장치가 다르다. (콘솔 : 컨트롤러, pc : 마우스)
	함수 포인터를 여기서 써먹는다. 얘가 이동하는 키다? 하면 이동시킬 녀석의 주소를 Input컴포넌트에 넣어둔다.
	이동키를 누른다? 그럼 함수 포인터에 넣어놨던 해당 이동키에 대한 함수 주소로 가서 호출되는거다.

	Uobject의 함수 주소를 등록시켜줄 수 있다. (언리얼 오브젝트를 상속받아서 만든 클래스의 멤버를 등록해주게끔 만들어져있음)
	<< 키에 따른 호출될 함수를 등록하는 함수>>
	*/
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
