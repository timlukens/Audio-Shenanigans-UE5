// Fill out your copyright notice in the Description page of Project Settings.


#include "TLSynthesizerComponent.h"
#include "AudioMixerDevice.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UTLSynthesizerComponent::UTLSynthesizerComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	PrimaryComponentTick.bCanEverTick = true;
	//UE_LOG(LogTemp, Warning, TEXT("UTLSynthesizerComponent alloc"));
}

void UTLSynthesizerComponent::Trigger() {
	if (TLSynthEngine != nullptr) {
		if (TLSynthesizerEngine* TLS = static_cast<TLSynthesizerEngine*>(TLSynthEngine.Get()))
			TLS->Trigger();
	}
}

ISoundGeneratorPtr UTLSynthesizerComponent::CreateSoundGenerator(const FSoundGeneratorInitParams& InParams) {
	TLSynthEngine = ISoundGeneratorPtr(new TLSynthesizerEngine());

	if (TLSynthesizerEngine* TLS = static_cast<TLSynthesizerEngine*>(TLSynthEngine.Get()))
	{
		FAudioDeviceManager* audioManager = FAudioDeviceManager::Get();
		FAudioDeviceHandle handle = audioManager->GetActiveAudioDevice();
		FAudioDevice* AudioDevice = handle.GetAudioDevice();
		Audio::FMixerDevice* mixer = static_cast<Audio::FMixerDevice*>(AudioDevice);

		TLS->Init(AudioDevice->SampleRate, mixer->GetDeviceOutputChannels(), Frequency);
	}

	return TLSynthEngine;
}


// Called when the game starts
void UTLSynthesizerComponent::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("UTLSynthesizerComponent BeginPlay"));
	this->Start();
}


// Called every frame
void UTLSynthesizerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	AActor* a = GetAttachmentRootActor();
	if (a != nullptr) {
		if(TLSynthesizerEngine* e = static_cast<TLSynthesizerEngine*>(TLSynthEngine.Get())) {
			double vel = a->GetVelocity().Length() * VelocityMultiplier * FMath::RandRange(RandomMin, RandomMax);
			e->SetFrequency(e->OriginalFrequency * vel);
		}
	}
}

