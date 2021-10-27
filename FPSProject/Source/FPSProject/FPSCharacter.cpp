// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// �����������������������λ��
	// ������һ�˳���������
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(FPSCameraComponent != nullptr);

	// �������������ӵ����������
	FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));

	// ������������Ը����۾��Ϸ���λ��
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));

	// ����Pawn�����������ת��
	FPSCameraComponent->bUsePawnControlRotation = true;


	// FPS��Ϸ�ᴴ����һ�˳��������������Ϊ���������ʾ�ֱۺ��������������������
	// Ϊ������Ҵ�����һ�˳����������
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	check(FPSMesh != nullptr);

	// ����������ܿ��������������
	FPSMesh->SetOnlyOwnerSee(true);

	// ��FPSMesh���ӵ�FPSCamera
	FPSMesh->SetupAttachment(FPSCameraComponent);

	// ����ĳЩ������Ӱ���Ա�ʵ��ֻ�е�����������Ӿ�Ч��
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	// ���ص����˳�ȫ�������塣���ֻ�ܿ����Լ��ĵ�һ�˳�������
	GetMesh()->SetOwnerNoSee(true);


}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// ȷ������ʹ��FPSCharacter��
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
// InputComponent �Ƕ�����δ����������ݵ���������Խ� InputComponent ���ӵ���Ҫ���������actor��
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// ��������󶨡�����Ŀ��������ӵİ���ӳ�䣬���ƶ�����������
	// �����ƶ����ܣ��Զ�����������ʵ��
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);

	// ����ת�ӽǹ��ܣ�ֱ�Ӱ󶨵������ṩ����������
	PlayerInputComponent->BindAxis("Turn", this, &AFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPSCharacter::AddControllerPitchInput);

	// ������Ծ���ܣ��ڰ���Pressed��Releasedʱ�������Զ������Ծ����
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::StopJump);

	// �������
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);

}


// ʵ��ǰ���ƶ�
void AFPSCharacter::MoveForward(float Value)
{
	// �ҳ�"ǰ��"���򣬼������ָ��ķ��򣬲���¼�������÷����ƶ�
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}


// ʵ�������ƶ�
void AFPSCharacter::MoveRight(float Value)
{
	// �ҳ�"�Ҳ�"����
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}


// ʵ����Ծ��ֱ���޸�ACharater�����bPressedJump����
void AFPSCharacter::StartJump()
{
	bPressedJump = true;
}

void AFPSCharacter::StopJump()
{
	bPressedJump = false;
}


// ʵ���������
void AFPSCharacter::Fire()
{
	// ��ͼ���䷢���
	if (ProjectileClass)
	{
		// ��ȡ������任��
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);

		// ����MuzzleOffset�����Կ��������ǰ���ɷ����
		MuzzleOffset.Set(100.0f, 0.0f, 0.0f);

		// ��MuzzleOffset��������ռ�任������ռ䡣
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);

		// ʹĿ�귽����������б��
		FRotator MuzzleRotation = CameraRotation;
		MuzzleRotation.Pitch += 10.0f;

		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			// ��ǹ��λ�����ɷ����
			AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				// ���÷�����ĳ�ʼ�켣��
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}
	}
}

