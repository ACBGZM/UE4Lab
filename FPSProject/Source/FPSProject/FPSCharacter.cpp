// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// 创建摄像机组件，调整摄像机位置
	// 创建第一人称摄像机组件
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(FPSCameraComponent != nullptr);

	// 将摄像机组件附加到胶囊体组件
	FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));

	// 将摄像机置于略高于眼睛上方的位置
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));

	// 启用Pawn控制摄像机旋转。
	FPSCameraComponent->bUsePawnControlRotation = true;


	// FPS游戏会创建第一人称网格体组件，仅为所属玩家显示手臂和武器，附加在摄像机上
	// 为所属玩家创建第一人称网格体组件
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	check(FPSMesh != nullptr);

	// 仅所属玩家能看到此网格体组件
	FPSMesh->SetOnlyOwnerSee(true);

	// 将FPSMesh附加到FPSCamera
	FPSMesh->SetupAttachment(FPSCameraComponent);

	// 禁用某些环境阴影，以便实现只有单个网格体的视觉效果
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	// 隐藏第三人称全身网格体。玩家只能看到自己的第一人称网格体
	GetMesh()->SetOwnerNoSee(true);


}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// 确保正在使用FPSCharacter类
	check(GEngine != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCharacter."));

	}

}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
// InputComponent 是定义如何处理输入数据的组件。可以将 InputComponent 附加到想要接收输入的actor。
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 设置输入绑定。把项目设置中添加的按键映射，跟移动函数绑定起来
	// 对于移动功能，自定义两个函数实现
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);

	// 对于转视角功能，直接绑定到引擎提供的两个函数
	PlayerInputComponent->BindAxis("Turn", this, &AFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPSCharacter::AddControllerPitchInput);

	// 对于跳跃功能，在案件Pressed和Released时，调用自定义的跳跃操作
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::StopJump);
}


// 实现前后移动
void AFPSCharacter::MoveForward(float Value)
{
	// 找出"前方"方向，即摄像机指向的方向，并记录玩家想向该方向移动
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}


// 实现左右移动
void AFPSCharacter::MoveRight(float Value)
{
	// 找出"右侧"方向
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}


// 实现跳跃，直接修改ACharater基类的bPressedJump变量
void AFPSCharacter::StartJump()
{
	bPressedJump = true;
}

void AFPSCharacter::StopJump()
{
	bPressedJump = false;
}

