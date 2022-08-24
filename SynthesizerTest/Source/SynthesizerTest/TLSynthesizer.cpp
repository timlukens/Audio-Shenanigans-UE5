//#include "TLSynthesizer.h"
//#include "TLSynthesizerEngine.h"
//
//TLSynthesizer::TLSynthesizer(const FObjectInitializer& ObjInitializer)
//	: Super(ObjInitializer) {
//	UE_LOG(LogTemp, Warning, TEXT("TLSynthesizer alloc"));
//
//}
//
//TLSynthesizer::~TLSynthesizer() {
//
//}
//
//ISoundGeneratorPtr TLSynthesizer::CreateSoundGenerator(const FSoundGeneratorInitParams& InParams) {
//	TLSynthEngine = ISoundGeneratorPtr(new TLSynthesizerEngine());
//
//	if (TLSynthesizerEngine* TLS = static_cast<TLSynthesizerEngine*>(TLSynthEngine.Get()))
//	{
//		TLS->Init(InParams.SampleRate);
//	}
//
//	return TLSynthEngine;
//}
//
///** Callback to generate a new audio stream buffer. */
////bool TLSynthesizer::OnProcessAudioStream(FAlignedFloatBuffer& OutputBuffer) {
////	UE_LOG(LogTemp, Warning, TEXT("OnProcessAudioStream"));
////	return true;
////}
////
/////** Called when audio render thread stream is shutting down. Last function called. Allows cleanup on render thread. */
////void TLSynthesizer::OnAudioStreamShutdown() {
////
////}
