// Fill out your copyright notice in the Description page of Project Settings.


#include "MySpring.h"
#include "Character/MyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMySpring::AMySpring()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	Material = CreateDefaultSubobject<UMaterial>(TEXT("MATERIAL"));
	Trigger = CreateDefaultSubobject<UCapsuleComponent>(TEXT("TRIGGER"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("StaticMesh'/Game/StarterContent/Props/SM_TableRound.SM_TableRound'"));
	if (SM.Succeeded())
	{
		Mesh->SetStaticMesh(SM.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MM(TEXT("Material'/Game/StarterContent/Props/Materials/M_TableRound.M_TableRound'"));
	if (MM.Succeeded())
	{
		Material = MM.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> SB(TEXT("SoundWave'/Game/Sounds/spring_sound.spring_sound'"));
	if (SB.Succeeded())
	{
		BounceSound = SB.Object;
	}

	Mesh->SetMaterial(0, Material);

	SetRootComponent(Mesh);
	Trigger->SetupAttachment(Mesh);

	Trigger->SetCollisionProfileName(TEXT("MyEnemy"));
	Trigger->SetCapsuleRadius(70.f);
	Trigger->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
}

void AMySpring::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentHit.AddDynamic(this, &AMySpring::OnCharacterHit);
}

void AMySpring::OnCharacterHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(OtherActor);
	if (MyCharacter) 
	{
		PlayBounceSound();
		
		FVector Direction = GetActorUpVector();
		MyCharacter->LaunchCharacter(Direction * BounceVelocity, true, true);
	}
}

void AMySpring::PlayBounceSound()
{
	UGameplayStatics::PlaySoundAtLocation(this, BounceSound, GetActorLocation());
}

