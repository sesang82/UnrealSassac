// Fill out your copyright notice in the Description page of Project Settings.


#include "UInputData.h"

UTestInputData::UTestInputData()
{
	/*
	ConstructorHelpers�� ������ �ҷ��� �� �ִ� ������Ʈ ���δ���°� ���� �ִ�.
	������ ���� �Լ���. ���¿��ٰ� ������ Ŭ���� �Ѵ����� ���۷��� ���縦 �ϸ�
	�ش� ������ ������ �� �ִ� ��ΰ� ����ȴ�. �װ��� �� �ؿ��ٰ� ��� ���縦 ���ָ� �ȴ�.
	*/
	ConstructorHelpers::FObjectFinder<UInputMappingContext>
		Asset(TEXT(""));

	// ���������� �ε��ߴ���
	if (Asset.Succed())
	{
		// �������� ��� �ҷ��� ������ ��������� �����Ѵ�.
		// �׼� ���� �̷� ������� �ҷ����� �ȴ�.
		/*
		�ٵ� ������ �Ȱ��� �༮�� �� �� �����ڰ� �Ź� ȣ��� �ʿ䰡 ������
		�׷��� static Ű���带 ���°Ŵ�. ����� static�� ������ {}�� �����ϸ�
		static�� �� �ڵ�� �ȿ����� ���������� �Ǳ� ������ {} �ۿ����� �װ� ������. 
		*/
		Asset = Asset.Object;
	}
}
