// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "FPSCharacter.generated.h"


UCLASS()
class FPSPROJECT_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// UFUNCTION 宏让引擎可以发觉这些函数，以便将它们纳入序列化和其他引擎功能中
	// 处理用于前后移动的输入
	UFUNCTION()
		void MoveForward(float Value);

	// 处理用于左右移动的输入
	UFUNCTION()
		void MoveRight(float Value);

	// 跳跃
	UFUNCTION()
		void StartJump();

	UFUNCTION()
		void StopJump();

	// 摄像机组件
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* FPSCameraComponent;

	// 第一人称网格体（手臂和武器），仅对所属玩家可见
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* FPSMesh;
};
