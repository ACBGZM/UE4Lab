// Copyright Epic Games, Inc. All Rights Reserved.
// ��Ϸģʽ������Ϸ����ͻ�ʤ������
// ��Ϸģʽ��������һЩĬ���࣬����ĳЩ������Ϸ������ͣ�
// ����Pawn��PlayerController��HUD�ȡ�

#include "FPSProjectGameModeBase.h"

void AFPSProjectGameModeBase::StartPlay()
{
	Super::StartPlay();
	check(GEngine != nullptr)
	{
		// ����Ļ����ʾ5��ĵ�����Ϣ��key=-1��ֹ����Ϣ�����»�ˢ��
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World! This is FPSGameMode!"));
	}
}

