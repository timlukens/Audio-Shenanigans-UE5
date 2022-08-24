//#pragma once
//
//#include "CoreMinimal.h"
//#include "AudioMixer.h"
//#include "Components/SynthComponent.h"
//#include "TLSynthesizer.generated.h"
//
////using namespace Audio;
//
//UCLASS();
//class SYNTHESIZERTEST_API TLSynthesizer :
//    public USynthComponent
//{
//    GENERATED_BODY();
//public:
//    TLSynthesizer(const FObjectInitializer& ObjInitializer);
//    virtual ~TLSynthesizer();
// 
//    /** Callback to generate a new audio stream buffer. */
//    //bool OnProcessAudioStream(FAlignedFloatBuffer& OutputBuffer);
//
//    /** Called when audio render thread stream is shutting down. Last function called. Allows cleanup on render thread. */
//    //void OnAudioStreamShutdown();
//
//    virtual ISoundGeneratorPtr CreateSoundGenerator(const FSoundGeneratorInitParams& InParams) override;
//
//protected:
//    IAudioDeviceModule* AudioInterface;
//    FAudioDevice* AudioDevice;
//    ISoundGeneratorPtr TLSynthEngine;
//
//};
//
