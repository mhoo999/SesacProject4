// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Sessac4ndProject : ModuleRules
{
	public Sessac4ndProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(new string[]{"Sessac4ndProject"});
		
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "NavigationSystem", "AIModule", "Cascade", "OnlineSubsystem", "OnlineSubsystemSteam" });
	}
}
