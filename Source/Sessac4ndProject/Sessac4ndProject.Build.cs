// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Sessac4ndProject : ModuleRules
{
	public Sessac4ndProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
