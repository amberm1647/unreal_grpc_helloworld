// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProject.h"
#include "Modules/ModuleManager.h"

void FMyProjectModule::StartupModule() {
	const FString dll_path = "C:\\Users\\ambermao\\repos\\unreal\\MyProject\\Source\\MyProject\\dll\\client.dll";
	dll_handle = FPlatformProcess::GetDllHandle(*dll_path);

	if (dll_handle != nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("client dll loaded successfully"));
	} 
	else
	{
		UE_LOG(LogTemp, Fatal, TEXT("client dll failed to load"));
	}
}

void FMyProjectModule::ShutdownModule() 
{
	FPlatformProcess::FreeDllHandle(dll_handle);
	dll_handle = nullptr;
}

IMPLEMENT_PRIMARY_GAME_MODULE( FMyProjectModule, MyProject, "MyProject" );
