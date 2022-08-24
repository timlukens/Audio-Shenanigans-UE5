// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SynthesizerTest : ModuleRules
{
	public SynthesizerTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "AudioMixer", "AudioMixerCore" });
	}
}
