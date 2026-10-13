// LifeAfter. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class RobotTarget : TargetRules
{
	public RobotTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V7;

		ExtraModuleNames.AddRange( new string[] { "Robot" } );
	}
}
