// Fill out your copyright notice in the Description page of Project Settings.


#include "MyRing.h"
#include "Character/MyCharacter.h"
#include "Game/ProjectGameModeBase.h"
#include "UI/MyUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystem.h"

// Sets default values
AMyRing::AMyRing()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Sparkle = CreateDefaultSubobject<UParticleSystem>(TEXT("SPARKLE"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("StaticMesh'/Game/Graphics/Prototype_Project/Meshes/Icons/SM_Coin_01_1.SM_Coin_01_1'"));
	if (SM.Succeeded())
	{
		Mesh->SetStaticMesh(SM.Object);
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> SB(TEXT("SoundWave'/Game/Sounds/coin_c_02-102844.coin_c_02-102844'"));
	if (SB.Succeeded())
	{
		RingSound = SB.Object;
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("ParticleSystem'/Game/Material/PS_Sparkle.PS_Sparkle'"));
	if (PS.Succeeded())
	{
		Sparkle = PS.Object;
	}

	//Ʈ���� �������� ����
	SetRootComponent(Mesh);
	Trigger->SetupAttachment(Mesh);

	//������Ʈ �ݸ��� ���ð� ����
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
	Trigger->SetCollisionProfileName(TEXT("MyCollectible"));

	//trigger ũ�� ����
	Trigger->SetBoxExtent(FVector(25.0f, 25.0f, 25.0f));

	Mesh->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
	Mesh->SetRelativeLocationAndRotation(FVector(0, 0, 65.f), FRotator(90, 0, 0));

	// collision ����
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));


}

// Called when the game starts or when spawned
void AMyRing::BeginPlay()
{
	Super::BeginPlay();

}


// Ring�� Character�� ������ �Ǿ����� ���� ����
void AMyRing::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AMyRing::OnCharacterOverlap);
}

void AMyRing::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweepresult)
{
	// ������ ĳ���� ����
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(OtherActor);
	if (MyCharacter) // ���� ĳ���Ϳ� ������ �Ǿ��ٸ� destroy �� UI�� ���� �� ���� ������Ʈ
	{
		UGameplayStatics::PlaySoundAtLocation(this, RingSound, GetActorLocation());
		UGameplayStatics::SpawnEmitterAtLocation(this, Sparkle, GetActorLocation());
		
		Mesh->SetVisibility(false);
		Trigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		MyCharacter->IncreaseMaxSpeed();

		FTimerHandle RespawnTimerHandle;
		GetWorldTimerManager().SetTimer(RespawnTimerHandle, FTimerDelegate::CreateLambda([&]
			{
				Mesh->SetVisibility(true);
				Trigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			}
		
		), 10.f, false);

	}

}

// Called Every frame
void AMyRing::Tick(float Deltatime)
{
	Super::Tick(Deltatime);

	FRotator NewRotation = FRotator(0, 0, 0.5f);
	FQuat QuatRotation = FQuat(NewRotation);

	AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
}

