#include "TLSynthesizerEngine.h"
#include "Math/UnrealMathUtility.h"

TLSynthesizerEngine::TLSynthesizerEngine() {
	//UE_LOG(LogTemp, Warning, TEXT("TLSynthesizerEngine alloc"));

	WaveTable = nullptr;
	TableSize = 8192;

	GainEnvelope = new Audio::FADEnvelope();
	Delay = new Audio::FDelay();
}

void TLSynthesizerEngine::Trigger() {
	GainEnvelope->Attack();
}

TLSynthesizerEngine::~TLSynthesizerEngine() {
	//if(WaveTable != nullptr)
	//	free(WaveTable);
	//WaveTable = nullptr;
}

void TLSynthesizerEngine::SetFrequency(double freq) {
	Frequency = freq * InputVelocity;
	if (Frequency < 20) Frequency = 20;
	StepSize = Frequency * NumChannels * (float)TableSize / (float)SampleRate;
}

void TLSynthesizerEngine::CreateWaveTable(int32 NumSamples) {
	TableSize = NumSamples;
	WaveTable = (float*)calloc(NumSamples, sizeof(float));
	for (int i = 0; i < NumSamples; i++) {
		for(int harmonic = 1; harmonic < 14; harmonic += 2)
			WaveTable[i] += (1.0 / (double)harmonic) * sin(PI * 2 * ((float)i / NumSamples) * (double)harmonic);
	}

	StepSize = Frequency * NumChannels * (float)NumSamples / (float)SampleRate;
	//UE_LOG(LogTemp, Warning, TEXT("StepSize: %f"), StepSize);
	CurrentIndex = 0.f;

	//UE_LOG(LogTemp, Warning, TEXT("Creating WaveTable"));
}

int32 TLSynthesizerEngine::OnGenerateAudio(float* OutAudio, int32 NumSamples) {
	//UE_LOG(LogTemp, Warning, TEXT("NumSamples: %d"), NumSamples);

	if (Frequency < 20) return NumSamples;

	const int32 NumFrames = NumSamples / NumChannels;

	for (int i = 0; i < NumFrames; i++) {
		float gainEnv = 0;
		GainEnvelope->GetNextEnvelopeOut(gainEnv);
		for (int32 Channel = 0; Channel < NumChannels; ++Channel) {
			OutAudio[i * 2 + Channel] = WaveTable[(int)CurrentIndex] * 0.1 * gainEnv;
			OutAudio[i * 2 + Channel] += Delay->ProcessAudioSample(OutAudio[i * 2 + Channel] + (FeedbackSamples[Channel] * 0.92));
			FeedbackSamples[Channel] = OutAudio[i * 2 + Channel];
		}

		CurrentIndex += StepSize;
		while (CurrentIndex >= TableSize) CurrentIndex -= TableSize;
		
	}
	//UE_LOG(LogTemp, Warning, TEXT("%f"), OutAudio[0]);
	return NumSamples;
}

void TLSynthesizerEngine::Init(int32 InSampleRate, int numChannels, float freq) {
	SampleRate = InSampleRate;
	NumChannels = numChannels;
	Frequency = freq;
	OriginalFrequency = freq;
	CreateWaveTable(TableSize);

	GainEnvelope->Init(SampleRate);
	GainEnvelope->SetAttackTimeSeconds(0.01);
	GainEnvelope->SetDecayTimeSeconds(0.2);
	GainEnvelope->Attack();

	Delay->Init(SampleRate);
	Delay->SetDelayMsec(200);

	FeedbackSamples.Empty();
	FeedbackSamples.AddZeroed(numChannels);

	//UE_LOG(LogTemp, Warning, TEXT("SampleRate: %d"), SampleRate);
	//UE_LOG(LogTemp, Warning, TEXT("NumChannels: %d"), NumChannels);
}