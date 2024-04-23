// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AuraGameMain : ModuleRules
{
	public AuraGameMain(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput", "GameplayAbilities" });

        PrivateDependencyModuleNames.AddRange(new string[] {"GameplayTags", "GameplayTasks","NavigationSystem","Niagara","AIModule" });
    }
}
