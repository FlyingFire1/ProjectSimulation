// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ProjectSimulation/DamageType_Melee.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDamageType_Melee() {}
// Cross Module References
	PROJECTSIMULATION_API UClass* Z_Construct_UClass_UDamageType_Melee_NoRegister();
	PROJECTSIMULATION_API UClass* Z_Construct_UClass_UDamageType_Melee();
	ENGINE_API UClass* Z_Construct_UClass_UDamageType();
	UPackage* Z_Construct_UPackage__Script_ProjectSimulation();
// End Cross Module References
	void UDamageType_Melee::StaticRegisterNativesUDamageType_Melee()
	{
	}
	UClass* Z_Construct_UClass_UDamageType_Melee_NoRegister()
	{
		return UDamageType_Melee::StaticClass();
	}
	struct Z_Construct_UClass_UDamageType_Melee_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UDamageType_Melee_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UDamageType,
		(UObject* (*)())Z_Construct_UPackage__Script_ProjectSimulation,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UDamageType_Melee_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "DamageType_Melee.h" },
		{ "ModuleRelativePath", "DamageType_Melee.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UDamageType_Melee_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDamageType_Melee>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UDamageType_Melee_Statics::ClassParams = {
		&UDamageType_Melee::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x001100A0u,
		METADATA_PARAMS(Z_Construct_UClass_UDamageType_Melee_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UDamageType_Melee_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UDamageType_Melee()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UDamageType_Melee_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UDamageType_Melee, 3142861923);
	template<> PROJECTSIMULATION_API UClass* StaticClass<UDamageType_Melee>()
	{
		return UDamageType_Melee::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UDamageType_Melee(Z_Construct_UClass_UDamageType_Melee, &UDamageType_Melee::StaticClass, TEXT("/Script/ProjectSimulation"), TEXT("UDamageType_Melee"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UDamageType_Melee);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
