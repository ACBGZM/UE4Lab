// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "FPSProjectile.generated.h"

UCLASS()
class FPSPROJECT_API AFPSProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 碰撞组件，用Sphere组件定义
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		USphereComponent* CollisionComponent;

	// 定义发射物运动组件，UE4有现成的
	UPROPERTY(VisibleAnywhere, Category = Movement)
		UProjectileMovementComponent* ProjectileMovementComponent;

	// 定义初始化射击方向上发射物速度的函数
	void FireInDirection(const FVector& ShootDirection);

	// 发射物网格体
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		UStaticMeshComponent* ProjectileMeshComponent;

	// 发射物材质
	UPROPERTY(VisibleDefaultsOnly, Category = Movement)
		UMaterialInstanceDynamic* ProjectileMaterialInstance;



};
