// Fill out your copyright notice in the Description page of Project Settings.


#include "ClearWall.h"
#include "Kismet/GameplayStatics.h"
#include "Character/MyWalkingCharacter.h"

// Sets default values
AClearWall::AClearWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WALL"));
	Material = CreateDefaultSubobject<UMaterial>(TEXT("MATERIAL"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("StaticMesh'/Game/StarterContent/Props/SM_CubeShape.SM_CubeShape'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> MM(TEXT("Material'/Game/StarterContent/Props/Materials/M_Bush.M_Bush'"));

	if (SM.Succeeded() && MM.Succeeded()) 
	{
		Mesh->SetStaticMesh(SM.Object);
		Material = MM.Object;
	}

	Mesh->SetMaterial(0, Material);
	SetRootComponent(Mesh);
}

// Called every frame
void AClearWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<AActor*> FoundEnemies;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyWalkingCharacter::StaticClass(), FoundEnemies);

	if (FoundEnemies.Num() == 0)
	{
		Destroy();
	}

}

