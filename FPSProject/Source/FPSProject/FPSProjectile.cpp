// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProjectile.h"

// Sets default values
AFPSProjectile::AFPSProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 创建根组件
	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}

	// 创建球体碰撞组件
	if (!CollisionComponent)
	{
		// 用球体进行碰撞展示
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		
		// 将球体的碰撞配置文件名称设置为"Projectile"。
		CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));

		// 组件击中某物时调用的事件。
		CollisionComponent->OnComponentHit.AddDynamic(this, &AFPSProjectile::OnHit);

		CollisionComponent->InitSphereRadius(15.0f);
		
		// 将碰撞组件设置为根组件，模拟器将驱动此组件
		RootComponent = CollisionComponent;
	}

	// 创建发射物运动驱动组件
	if (!ProjectileMovementComponent)
	{
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		// 更新CollisionComponent，也就是根组件的位置
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed = 3000.0f;
		ProjectileMovementComponent->MaxSpeed = 3000.0f;
		// 这个Projectile的旋转将在每一帧更新，以匹配它的速度方向
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		// 设置反弹
		ProjectileMovementComponent->bShouldBounce = true;
		// 反弹系数
		ProjectileMovementComponent->Bounciness = 0.3f;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	}

	// 设置发射物网格体
	if (!ProjectileMeshComponent)
	{
		ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("/Game/Assets/Sphere/Sphere.Sphere"));
		if (Mesh.Succeeded())
		{
			ProjectileMeshComponent->SetStaticMesh(Mesh.Object);
		}
	}

	// 设置发射物材质，把网格体组件附加到RootComponent
	static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("/Game/Assets/Sphere/SphereMaterial.SphereMaterial"));
	if (Material.Succeeded())
	{
		ProjectileMaterialInstance = UMaterialInstanceDynamic::Create(Material.Object, ProjectileMeshComponent);
	}
	ProjectileMeshComponent->SetMaterial(0, ProjectileMaterialInstance);
	ProjectileMeshComponent->SetRelativeScale3D(FVector(0.09f, 0.09f, 0.09f));
	ProjectileMeshComponent->SetupAttachment(RootComponent);

	// 设置生命周期
	InitialLifeSpan = 3.0f;


}

// Called when the game starts or when spawned
void AFPSProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// 设置发射物初速度的函数，使用输入的方向，速度由ProjectileMovementComponent定义
void AFPSProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}



// 响应碰撞函数
void AFPSProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		// 给碰到的物体施加一个力
		OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
	}
	// 子弹自身销毁
	Destroy();
}