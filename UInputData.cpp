// Fill out your copyright notice in the Description page of Project Settings.


#include "UInputData.h"

UTestInputData::UTestInputData()
{
	/*
	ConstructorHelpers에 에셋을 불러올 수 있는 오브젝트 파인더라는게 같이 있다.
	생성자 전용 함수다. 에셋에다가 오른쪽 클릭을 한다음에 레퍼런스 복사를 하면
	해당 에셋을 참조할 수 있는 경로가 복사된다. 그것을 저 밑에다가 경로 복사를 해주면 된다.
	*/
	ConstructorHelpers::FObjectFinder<UInputMappingContext>
		Asset(TEXT(""));

	// 정상적으로 로딩했는지
	if (Asset.Succed())
	{
		// 성공했을 경우 불러온 에셋을 멤버변수에 지정한다.
		// 액션 또한 이런 방법으로 불러오면 된다.
		/*
		근데 어차피 똑같은 녀석을 쓸 때 생성자가 매번 호출될 필요가 있을까
		그럴때 static 키워드를 쓰는거다. 참고로 static을 쓰더라도 {}을 지정하면
		static은 그 코드블럭 안에서의 지역변수가 되기 때문에 {} 밖에서는 그걸 못쓴다. 
		*/
		Asset = Asset.Object;
	}
}
