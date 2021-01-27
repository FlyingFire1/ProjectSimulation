// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ProjectSimulation/ProjectSimulationGameMode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeProjectSimulationGameMode() {}
// Cross Module References
	PROJECTSIMULATION_API UClass* Z_Construct_UClass_AProjectSimulationGameMode_NoRegister();
	PROJECTSIMULATION_API UClass* Z_Construct_UClass_AProjectSimulationGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_ProjectSimulation();
// End Cross Module References
	void AProjectSimulationGameMode::StaticRegisterNativesAProjectSimulationGameMode()
	{
	}
	UClass* Z_Construct_UClass_AProjectSimulationGameMode_NoRegister()
	{
		return AProjectSimulationGameMode::StaticClass();
	}
	struct Z_Construct_UClass_AProjectSimulationGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AProjectSimulationGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_ProjectSimulation,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProjectSimulationGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "ProjectSimulationGameMode.h" },
		{ "ModuleRelativePath", "ProjectSimulationGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AProjectSimulationGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AProjectSimulationGameMode>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AProjectSimulationGameMode_Statics::ClassParams = {
		&AProjectSimulationGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008802ACu,
		METADATA_PARAMS(Z_Construct_UClass_AProjectSimulationGameMode_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AProjectSimulationGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AProjectSimulationGameMode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AProjectSimulationGameMode_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AProjectSimulationGameMode, 766817548);
	template<> PROJECTSIMULATION_API UClass* StaticClass<AProjectSimulationGameMode>()
	{
		return AProjectSimulationGameMode::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AProjectSimulationGameMode(Z_Construct_UClass_AProjectSimulationGameMode, &AProjectSimulationGameMode::StaticClass, TEXT("/Script/ProjectSimulation"), TEXT("AProjectSimulationGameMode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AProjectSimulationGameMode);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
