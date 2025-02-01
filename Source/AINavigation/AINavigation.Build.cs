// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AINavigation : ModuleRules
{
	public AINavigation(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "AIModule" });
	}
}
