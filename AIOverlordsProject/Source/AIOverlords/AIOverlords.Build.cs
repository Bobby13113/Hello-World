// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AIOverlords : ModuleRules
{
	public AIOverlords(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCH;
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"InputCore",
				"GameplayTasks",
				"AIModule",
				"GameplayAbilities"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"RenderCore",
				"Landscape"
			}
		);
		
		// Enable C++ exceptions
		bEnableExceptions = true;
	}
}