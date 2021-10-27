// Copyright Epic Games, Inc. All Rights Reserved.
// 游戏模式定义游戏规则和获胜条件。
// 游戏模式还会设置一些默认类，用于某些基本游戏框架类型，
// 包括Pawn、PlayerController和HUD等。

#include "FPSProjectGameModeBase.h"

void AFPSProjectGameModeBase::StartPlay()
{
	Super::StartPlay();
	check(GEngine != nullptr)
	{
		// 在屏幕中显示5秒的调试信息，key=-1防止该消息被更新或刷新
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World! This is FPSGameMode!"));
	}
}

