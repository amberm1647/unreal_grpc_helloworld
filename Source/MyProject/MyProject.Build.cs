// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using System;
using UnrealBuildTool;

public class MyProject : ModuleRules
{
	public MyProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput",});

		// PrivateDependencyModuleNames.AddRange(new string[] {  });

        PublicIncludePaths.Add("C:\\src\\vcpkg\\installed\\x64-windows\\include");

        string LibrariesPath = "C:\\src\\vcpkg\\installed\\x64-windows\\lib";
        DirectoryInfo d = new DirectoryInfo(LibrariesPath);
        FileInfo[] Files = d.GetFiles("*.lib");
        foreach (FileInfo file in Files)
        {
            Console.WriteLine("adding " + file.Name);
            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, file.Name));
            RuntimeDependencies.Add(Path.Combine(ModuleDirectory, "..", "..", "Binaries", "Win64", file.Name), Path.Combine(LibrariesPath, file.Name));
        }

        string DllsPath = "C:\\src\\vcpkg\\installed\\x64-windows\\bin";
        DirectoryInfo d2 = new DirectoryInfo(DllsPath);
        FileInfo[] Files2 = d2.GetFiles("*.dll");
        foreach (FileInfo file in Files2)
        {
            Console.WriteLine("adding " + file.Name);
            RuntimeDependencies.Add(Path.Combine(ModuleDirectory, "..", "..", "Binaries", "Win64", file.Name), Path.Combine(DllsPath, file.Name));
        }

        PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "dll", "client.lib"));
        RuntimeDependencies.Add(Path.Combine(ModuleDirectory, "dll", "client.dll"));
        PublicDelayLoadDLLs.Add("client.dll");

        //PublicDefinitions.Add("PROTOBUF_ENABLE_DEBUG_LOGGING_MAY_LEAK_PII=0");
        //PublicDefinitions.Add("PROTOBUF_BUILTIN_ATOMIC=0");
        //PublicDefinitions.Add("GOOGLE_PROTOBUF_NO_RTTI=1");


        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
