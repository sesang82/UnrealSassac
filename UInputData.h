// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UInputData.generated.h"

// EnhancedInput라는 모듈을 추가하면 쓸 수 있다.
// 비주얼 스튜디오에서 인식 못하는 것 뿐이니 빨간 줄 떠도 걱정 x 컴파일만 해놓자.
#include "InputAction.h"
#include "InputMappingContext.h"

/**
 * 
 */
UCLASS()
class SAC6_API UTestInputData : public UObject
{
	GENERATED_BODY()


public:
	UTestInputData();

public:
	UInputMaapingContext* m
	
};
