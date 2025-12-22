// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TheGauntlet_2 : ModuleRules
{
	public TheGauntlet_2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"TheGauntlet_2",
			"TheGauntlet_2/Variant_Platforming",
			"TheGauntlet_2/Variant_Platforming/Animation",
			"TheGauntlet_2/Variant_Combat",
			"TheGauntlet_2/Variant_Combat/AI",
			"TheGauntlet_2/Variant_Combat/Animation",
			"TheGauntlet_2/Variant_Combat/Gameplay",
			"TheGauntlet_2/Variant_Combat/Interfaces",
			"TheGauntlet_2/Variant_Combat/UI",
			"TheGauntlet_2/Variant_SideScrolling",
			"TheGauntlet_2/Variant_SideScrolling/AI",
			"TheGauntlet_2/Variant_SideScrolling/Gameplay",
			"TheGauntlet_2/Variant_SideScrolling/Interfaces",
			"TheGauntlet_2/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
