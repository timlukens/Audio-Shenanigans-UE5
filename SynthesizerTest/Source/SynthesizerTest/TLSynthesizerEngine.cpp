#include "TLSynthesizerEngine.h"
#include "Math/UnrealMathUtility.h"

TLSynthesizerEngine::TLSynthesizerEngine() {
	//UE_LOG(LogTemp, Warning, TEXT("TLSynthesizerEngine alloc"));

	WaveTable = nullptr;
	TableSize = 8192;
}

TLSynthesizerEngine::~TLSynthesizerEngine() {
	//if(WaveTable != nullptr)
	//	free(WaveTable);
	//WaveTable = nullptr;
}

void TLSynthesizerEngine::SetFrequency(double freq) {
	Frequency = freq * InputVelocity;
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

	const int32 NumFrames = NumSamples / NumChannels;

	for (int i = 0; i < NumFrames; i++) {
		for (int32 Channel = 0; Channel < NumChannels; ++Channel) {
			OutAudio[i * 2 + Channel] = WaveTable[(int)CurrentIndex] * 0.1;	
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

	//UE_LOG(LogTemp, Warning, TEXT("SampleRate: %d"), SampleRate);
	//UE_LOG(LogTemp, Warning, TEXT("NumChannels: %d"), NumChannels);
}