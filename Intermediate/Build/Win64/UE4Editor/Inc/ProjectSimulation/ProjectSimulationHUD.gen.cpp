// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ProjectSimulation/ProjectSimulationHUD.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeProjectSimulationHUD() {}
// Cross Module References
	PROJECTSIMULATION_API UClass* Z_Construct_UClass_AProjectSimulationHUD_NoRegister();
	PROJECTSIMULATION_API UClass* Z_Construct_UClass_AProjectSimulationHUD();
	ENGINE_API UClass* Z_Construct_UClass_AHUD();
	UPackage* Z_Construct_UPackage__Script_ProjectSimulation();
// End Cross Module References
	void AProjectSimulationHUD::StaticRegisterNativesAProjectSimulationHUD()
	{
	}
	UClass* Z_Construct_UClass_AProjectSimulationHUD_NoRegister()
	{
		return AProjectSimulationHUD::StaticClass();
	}
	struct Z_Construct_UClass_AProjectSimulationHUD_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AProjectSimulationHUD_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AHUD,
		(UObject* (*)())Z_Construct_UPackage__Script_ProjectSimulation,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProjectSimulationHUD_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Rendering Actor Input Replication" },
		{ "IncludePath", "ProjectSimulationHUD.h" },
		{ "ModuleRelativePath", "ProjectSimulationHUD.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AProjectSimulationHUD_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AProjectSimulationHUD>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AProjectSimulationHUD_Statics::ClassParams = {
		&AProjectSimulationHUD::StaticClass,
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
		0x008002ACu,
		METADATA_PARAMS(Z_Construct_UClass_AProjectSimulationHUD_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AProjectSimulationHUD_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AProjectSimulationHUD()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AProjectSimulationHUD_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AProjectSimulationHUD, 4226906577);
	template<> PROJECTSIMULATION_API UClass* StaticClass<AProjectSimulationHUD>()
	{
		return AProjectSimulationHUD::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AProjectSimulationHUD(Z_Construct_UClass_AProjectSimulationHUD, &AProjectSimulationHUD::StaticClass, TEXT("/Script/ProjectSimulation"), TEXT("AProjectSimulationHUD"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AProjectSimulationHUD);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
