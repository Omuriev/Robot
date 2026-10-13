// LifeAfter. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class RobotEditorTarget : TargetRules
{
	public RobotEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V7;

		ExtraModuleNames.AddRange( new string[] { "Robot" } );
	}
}
