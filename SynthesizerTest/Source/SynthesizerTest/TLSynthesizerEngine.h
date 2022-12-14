#pragma once

#include "CoreMinimal.h"
#include "Components/SynthComponent.h"
#include "DSP/Envelope.h"
#include "DSP/Delay.h"


class TLSynthesizerEngine
	: public ISoundGenerator
{
public:
	TLSynthesizerEngine();
	~TLSynthesizerEngine();

	virtual int32 OnGenerateAudio(float* OutAudio, int32 NumSamples) override;
	void Init(int32 InSampleRate, int numChannels, float freq);
	void SetFrequency(double freq);

	double InputVelocity = 1;
	double OriginalFrequency;

	Audio::FADEnvelope* GainEnvelope;
	Audio::FDelay* Delay;

	void Trigger();

private:
	TArray<float> FeedbackSamples;

	void CreateWaveTable(int32 NumSamples);
	float* WaveTable;
	int TableSize;
	float CurrentIndex;
	float StepSize;
	int32 SampleRate;
	int NumChannels;
	float Frequency;
};

