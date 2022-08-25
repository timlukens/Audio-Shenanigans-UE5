// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SynthComponent.h"
#include "../TLSynthesizerEngine.h"
#include "TLSynthesizerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SYNTHESIZERTEST_API UTLSynthesizerComponent : public USynthComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTLSynthesizerComponent(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Frequency = 440;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		double VelocityMultiplier = 0.001;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		double RandomMin = 1.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		double RandomMax = 1.0;

	UFUNCTION(BlueprintCallable)
		void Trigger();

	virtual ISoundGeneratorPtr CreateSoundGenerator(const FSoundGeneratorInitParams& InParams) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	ISoundGeneratorPtr TLSynthEngine;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
