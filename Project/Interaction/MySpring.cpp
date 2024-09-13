// Fill out your copyright notice in the Description page of Project Settings.


#include "MySpring.h"
#include "Character/MyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMySpring::AMySpring()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Spring = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SPRING"));
	Mat = CreateDefaultSubobject<UMaterial>(TEXT("MATERIAL"));
	Trigger = CreateDefaultSubobject<UCapsuleComponent>(TEXT("TRIGGER"));
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	Crosshair = CreateDefaultSubobject<UWidgetComponent>(TEXT("CROSSHAIR"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("StaticMesh'/Game/StarterContent/Props/SM_TableRound.SM_TableRound'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> MM(TEXT("Material'/Game/StarterContent/Props/Materials/M_TableRound.M_TableRound'"));

	if (SM.Succeeded() && MM.Succeeded())
	{
		Spring->SetStaticMesh(SM.Object);
		Spring->SetMaterial(0, MM.Object);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> UW(TEXT("WidgetBlueprint'/Game/UI/BP_Crosshair.BP_Crosshair_C'"));
	if (UW.Succeeded())
	{
		Crosshair->SetWidgetClass(UW.Class);
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> SB(TEXT("SoundWave'/Game/Sounds/spring_sound.spring_sound'"));
	if (SB.Succeeded())
	{
		BounceSound = SB.Object;
	}

	SetRootComponent(Spring);
	Trigger->SetupAttachment(Spring);
	Crosshair->SetupAttachment(Spring);
	Box->SetupAttachment(Spring);

	Trigger->SetCollisionProfileName(TEXT("MyEnemy"));
	Trigger->SetCapsuleRadius(70.f);
	Trigger->SetRelativeLocation(FVector(0.f, 0.f, 50.f));

	Box->SetRelativeLocation(FVector(0.f, 0.f, 250.f));
	Box->SetBoxExtent(FVector(10.f, 10.f, 10.f));

	Crosshair->SetWidgetSpace(EWidgetSpace::Screen);
	Crosshair->SetVisibility(false);
}

// Called when the game starts or when spawned
void AMySpring::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMySpring::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMySpring::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentHit.AddDynamic(this, &AMySpring::OnCharacterHit);
}

void AMySpring::OnCharacterHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	// 반응할 캐릭터 지정
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(OtherActor);
	if (MyCharacter) 
	{
		UGameplayStatics::PlaySoundAtLocation(this, BounceSound, GetActorLocation());

		FVector Direction = Box->GetComponentLocation() - Spring->GetComponentLocation();

		MyCharacter->LaunchCharacter(Direction * 6.f, true, true);
	}

}

