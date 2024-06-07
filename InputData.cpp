// Fill out your copyright notice in the Description page of Project Settings.


#include "InputData.h"

UTestInputData::UTestInputData()
{
	// 언리얼 에셋을 불러올때 사용한다.
	{
		/*
	ConstructorHelpers에 에셋을 불러올 수 있는 오브젝트 파인더라는게 같이 있다.
	생성자 전용 함수다. 에셋에다가 오른쪽 클릭을 한다음에 레퍼런스 복사를 하면
	해당 에셋을 참조할 수 있는 경로가 복사된다. 그것을 저 밑에다가 경로 복사를 해주면 된다.
	*/

		static ConstructorHelpers::FObjectFinder<UInputMappingContext>
			Asset(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Test/TestInput/IMC_Test.IMC_Test'"));

		// 정상적으로 로딩했는지 판단한다.
		if (Asset.Succeeded())
		{
			// 성공했을 경우 불러온 에셋을 멤버변수에 지정한다.
			// 액션 또한 이런 방법으로 불러오면 된다.
			/*
			근데 어차피 똑같은 녀석을 쓸 때 생성자가 매번 호출될 필요가 있을까
			그럴때 static 키워드를 쓰는거다. 참고로 static을 쓰더라도 {}을 지정하면
			static은 그 코드블럭 안에서의 지역변수가 되기 때문에 {} 밖에서는 그걸 못쓴다.
			*/
			mDefaultContext = Asset.Object;
		}
	}

	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			Asset(TEXT("/Script/EnhancedInput.InputAction'/Game/Test/TestInput/IA_TestMove.IA_TestMove'"));

		// 정상적으로 로딩했는지 판단한다.
		if (Asset.Succeeded())
		{
			// 성공했을 경우 불러온 에셋을 멤버변수에 지정한다.
			mMove = Asset.Object;
		}
	}

	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			Asset(TEXT("/Script/EnhancedInput.InputAction'/Game/Test/TestInput/IA_TestRotation.IA_TestRotation'"));

		// 정상적으로 로딩했는지 판단한다.
		if (Asset.Succeeded())
		{
			// 성공했을 경우 불러온 에셋을 멤버변수에 지정한다.
			mRotation = Asset.Object;
		}
	}

	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			Asset(TEXT("/Script/EnhancedInput.InputAction'/Game/Test/TestInput/IA_TestAttack.IA_TestAttack'"));

		// 정상적으로 로딩했는지 판단한다.
		if (Asset.Succeeded())
		{
			// 성공했을 경우 불러온 에셋을 멤버변수에 지정한다.
			mAttack = Asset.Object;
		}
	}

	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			Asset(TEXT("/Script/EnhancedInput.InputAction'/Game/Test/TestInput/IA_TestShield.IA_TestShield'"));

		// 정상적으로 로딩했는지 판단한다.
		if (Asset.Succeeded())
		{
			// 성공했을 경우 불러온 에셋을 멤버변수에 지정한다.
			mShield = Asset.Object;
		}
	}

	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			Asset(TEXT("/Script/EnhancedInput.InputAction'/Game/Test/TestInput/IA_TripleShot.IA_TripleShot'"));

		// 정상적으로 로딩했는지 판단한다.
		if (Asset.Succeeded())
		{
			// 성공했을 경우 불러온 에셋을 멤버변수에 지정한다.
			mTripleShot = Asset.Object;
		}
	}
}
