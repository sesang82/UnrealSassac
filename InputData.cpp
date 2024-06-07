// Fill out your copyright notice in the Description page of Project Settings.


#include "InputData.h"

UTestInputData::UTestInputData()
{
	// �𸮾� ������ �ҷ��ö� ����Ѵ�.
	{
		/*
	ConstructorHelpers�� ������ �ҷ��� �� �ִ� ������Ʈ ���δ���°� ���� �ִ�.
	������ ���� �Լ���. ���¿��ٰ� ������ Ŭ���� �Ѵ����� ���۷��� ���縦 �ϸ�
	�ش� ������ ������ �� �ִ� ��ΰ� ����ȴ�. �װ��� �� �ؿ��ٰ� ��� ���縦 ���ָ� �ȴ�.
	*/

		static ConstructorHelpers::FObjectFinder<UInputMappingContext>
			Asset(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Test/TestInput/IMC_Test.IMC_Test'"));

		// ���������� �ε��ߴ��� �Ǵ��Ѵ�.
		if (Asset.Succeeded())
		{
			// �������� ��� �ҷ��� ������ ��������� �����Ѵ�.
			// �׼� ���� �̷� ������� �ҷ����� �ȴ�.
			/*
			�ٵ� ������ �Ȱ��� �༮�� �� �� �����ڰ� �Ź� ȣ��� �ʿ䰡 ������
			�׷��� static Ű���带 ���°Ŵ�. ����� static�� ������ {}�� �����ϸ�
			static�� �� �ڵ�� �ȿ����� ���������� �Ǳ� ������ {} �ۿ����� �װ� ������.
			*/
			mDefaultContext = Asset.Object;
		}
	}

	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			Asset(TEXT("/Script/EnhancedInput.InputAction'/Game/Test/TestInput/IA_TestMove.IA_TestMove'"));

		// ���������� �ε��ߴ��� �Ǵ��Ѵ�.
		if (Asset.Succeeded())
		{
			// �������� ��� �ҷ��� ������ ��������� �����Ѵ�.
			mMove = Asset.Object;
		}
	}

	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			Asset(TEXT("/Script/EnhancedInput.InputAction'/Game/Test/TestInput/IA_TestRotation.IA_TestRotation'"));

		// ���������� �ε��ߴ��� �Ǵ��Ѵ�.
		if (Asset.Succeeded())
		{
			// �������� ��� �ҷ��� ������ ��������� �����Ѵ�.
			mRotation = Asset.Object;
		}
	}

	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			Asset(TEXT("/Script/EnhancedInput.InputAction'/Game/Test/TestInput/IA_TestAttack.IA_TestAttack'"));

		// ���������� �ε��ߴ��� �Ǵ��Ѵ�.
		if (Asset.Succeeded())
		{
			// �������� ��� �ҷ��� ������ ��������� �����Ѵ�.
			mAttack = Asset.Object;
		}
	}

	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			Asset(TEXT("/Script/EnhancedInput.InputAction'/Game/Test/TestInput/IA_TestShield.IA_TestShield'"));

		// ���������� �ε��ߴ��� �Ǵ��Ѵ�.
		if (Asset.Succeeded())
		{
			// �������� ��� �ҷ��� ������ ��������� �����Ѵ�.
			mShield = Asset.Object;
		}
	}

	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			Asset(TEXT("/Script/EnhancedInput.InputAction'/Game/Test/TestInput/IA_TripleShot.IA_TripleShot'"));

		// ���������� �ε��ߴ��� �Ǵ��Ѵ�.
		if (Asset.Succeeded())
		{
			// �������� ��� �ҷ��� ������ ��������� �����Ѵ�.
			mTripleShot = Asset.Object;
		}
	}
}
