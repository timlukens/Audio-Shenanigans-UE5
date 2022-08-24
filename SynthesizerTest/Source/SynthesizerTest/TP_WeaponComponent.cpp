// Copyright Epic Games, Inc. All Rights Reserved.


#include "TP_WeaponComponent.h"
#include "SynthesizerTestCharacter.h"
#include "SynthesizerTestProjectile.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "AudioDeviceManager.h"
#include "AudioMixerDevice.h"

// Sets default values for this component's properties
UTP_WeaponComponent::UTP_WeaponComponent()
{
	// Default offset from the character location for projectiles to spawn
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);

	UE_LOG(LogTemp, Warning, TEXT("UTP_WeaponComponent constructor"));

	/*FAudioDeviceManager* audioManager = FAudioDeviceManager::Get();
	FAudioDeviceHandle handle = audioManager->GetActiveAudioDevice();
	FAudioDevice* AudioDevice = handle.GetAudioDevice();
	FMixerDevice* mix = static_cast<Audio::FMixerDevice*>(AudioDevice);
	audioManager->InitSoundClasses();*/

	//synth = NewObject<TLSynthesizer>((UObject*)GetTransientPackage(), TLSynthesizer::StaticClass());
	//synth = CreateDefaultSubobject<UTLSynthesizerComponent>(TEXT("Synth"));
	//FSoundGeneratorInitParams params = FSoundGeneratorInitParams();
	////synth->SetupAttachment(static_cast<USceneComponent>(this));
	//AActor* a = GetOwner();
	//FAttachmentTransformRules rules = FAttachmentTransformRules::KeepRelativeTransform;
	////synth->AttachToComponent(a->GetDefaultAttachComponent(), rules);
	//if (a != nullptr) {
	//	USceneComponent* comp = a->GetRootComponent();
	//	if (comp != nullptr) {
	//		synth->AttachToComponent(a->GetRootComponent(), rules);
	//		synth->Activate();
	//		synth->Start();
	//		UE_LOG(LogTemp, Warning, TEXT("Attached to root scene component"));
	//	}
	//	else {
	//		UE_LOG(LogTemp, Warning, TEXT("Could not attach to root scene component"));
	//	}
	//}
	//else {
	//	UE_LOG(LogTemp, Warning, TEXT("Could not find actor"));
	//}
}


void UTP_WeaponComponent::Fire()
{
	//FAudioDeviceManager* audioManager = FAudioDeviceManager::Get();
	//FAudioDeviceHandle handle = audioManager->GetActiveAudioDevice();
	//FAudioDevice* AudioDevice = handle.GetAudioDevice();
	////AudioDevice->StartAudioStream();
	////AudioDevice->
	//Audio::FMixerDevice* mix = static_cast<Audio::FMixerDevice*>(AudioDevice);
	//Audio::IAudioMixerPlatformInterface* ampi = mix->GetAudioMixerPlatform();
	//ampi->StopAudioStream();
	//ampi->StartAudioStream();
	//ampi->StopAudioStream();
	
	/*if (mix != nullptr) {
		Audio::IAudioMixerPlatformInterface* ampi = mix->GetAudioMixerPlatform();
		synth = new TLSynthesizer(ampi);
		ampi->StopAudioStream();
		audioManager->SetActiveDevice(synth->DeviceID);
		ampi->StartAudioStream();
		UE_LOG(LogTemp, Warning, TEXT("Is Using Audio Mixer %d"), audioManager->IsUsingAudioMixer());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Mix was null"));
	}*/
	
	//audioManager->SetActiveDevice(synth->DeviceID);
	//UE_LOG(LogTemp, Warning, TEXT("Synth DeviceID %d"), synth->DeviceID);


	//ampi->StartAudioStream();

	UE_LOG(LogTemp, Warning, TEXT("Fire"));

	if(Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}

	// Try and fire a projectile
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
			const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);
	
			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
			// Spawn the projectile at the muzzle
			World->SpawnActor<ASynthesizerTestProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}
	
	// Try and play the sound if specified
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
	}
	
	// Try and play a firing animation if specified
	if (FireAnimation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

void UTP_WeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if(Character != nullptr)
	{
		// Unregister from the OnUseItem Event
		Character->OnUseItem.RemoveDynamic(this, &UTP_WeaponComponent::Fire);
	}
}

void UTP_WeaponComponent::AttachWeapon(ASynthesizerTestCharacter* TargetCharacter)
{	
	Character = TargetCharacter;
	if(Character != nullptr)
	{
		// Attach the weapon to the First Person Character
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
		GetOwner()->AttachToComponent(Character->GetMesh1P(),AttachmentRules, FName(TEXT("GripPoint")));

		// Register so that Fire is called every time the character tries to use the item being held
		Character->OnUseItem.AddDynamic(this, &UTP_WeaponComponent::Fire);
	}
}

