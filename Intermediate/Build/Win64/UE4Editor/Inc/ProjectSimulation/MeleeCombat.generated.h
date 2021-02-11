// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UPrimitiveComponent;
class UBoxComponent;
class AActor;
struct FHitResult;
#ifdef PROJECTSIMULATION_MeleeCombat_generated_h
#error "MeleeCombat.generated.h already included, missing '#pragma once' in MeleeCombat.h"
#endif
#define PROJECTSIMULATION_MeleeCombat_generated_h

#define ProjectSimulation_Source_ProjectSimulation_MeleeCombat_h_16_SPARSE_DATA
#define ProjectSimulation_Source_ProjectSimulation_MeleeCombat_h_16_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execFadeObject); \
	DECLARE_FUNCTION(execSetBox); \
	DECLARE_FUNCTION(execAttack); \
	DECLARE_FUNCTION(execOnOverlapEnd); \
	DECLARE_FUNCTION(execOnOverlapBegin);


#define ProjectSimulation_Source_ProjectSimulation_MeleeCombat_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execFadeObject); \
	DECLARE_FUNCTION(execSetBox); \
	DECLARE_FUNCTION(execAttack); \
	DECLARE_FUNCTION(execOnOverlapEnd); \
	DECLARE_FUNCTION(execOnOverlapBegin);


#define ProjectSimulation_Source_ProjectSimulation_MeleeCombat_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUMeleeCombat(); \
	friend struct Z_Construct_UClass_UMeleeCombat_Statics; \
public: \
	DECLARE_CLASS(UMeleeCombat, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/ProjectSimulation"), NO_API) \
	DECLARE_SERIALIZER(UMeleeCombat)


#define ProjectSimulation_Source_ProjectSimulation_MeleeCombat_h_16_INCLASS \
private: \
	static void StaticRegisterNativesUMeleeCombat(); \
	friend struct Z_Construct_UClass_UMeleeCombat_Statics; \
public: \
	DECLARE_CLASS(UMeleeCombat, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/ProjectSimulation"), NO_API) \
	DECLARE_SERIALIZER(UMeleeCombat)


#define ProjectSimulation_Source_ProjectSimulation_MeleeCombat_h_16_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UMeleeCombat(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UMeleeCombat) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UMeleeCombat); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UMeleeCombat); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UMeleeCombat(UMeleeCombat&&); \
	NO_API UMeleeCombat(const UMeleeCombat&); \
public:


#define ProjectSimulation_Source_ProjectSimulation_MeleeCombat_h_16_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UMeleeCombat(UMeleeCombat&&); \
	NO_API UMeleeCombat(const UMeleeCombat&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UMeleeCombat); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UMeleeCombat); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UMeleeCombat)


#define ProjectSimulation_Source_ProjectSimulation_MeleeCombat_h_16_PRIVATE_PROPERTY_OFFSET
#define ProjectSimulation_Source_ProjectSimulation_MeleeCombat_h_13_PROLOG
#define ProjectSimulation_Source_ProjectSimulation_MeleeCombat_h_16_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ProjectSimulation_Source_ProjectSimulation_MeleeCombat_h_16_PRIVATE_PROPERTY_OFFSET \
	ProjectSimulation_Source_ProjectSimulation_MeleeCombat_h_16_SPARSE_DATA \
	ProjectSimulation_Source_ProjectSimulation_MeleeCombat_h_16_RPC_WRAPPERS \
	ProjectSimulation_Source_ProjectSimulation_MeleeCombat_h_16_INCLASS \
	ProjectSimulation_Source_ProjectSimulation_MeleeCombat_h_16_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define ProjectSimulation_Source_ProjectSimulation_MeleeCombat_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ProjectSimulation_Source_ProjectSimulation_MeleeCombat_h_16_PRIVATE_PROPERTY_OFFSET \
	ProjectSimulation_Source_ProjectSimulation_MeleeCombat_h_16_SPARSE_DATA \
	ProjectSimulation_Source_ProjectSimulation_MeleeCombat_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	ProjectSimulation_Source_ProjectSimulation_MeleeCombat_h_16_INCLASS_NO_PURE_DECLS \
	ProjectSimulation_Source_ProjectSimulation_MeleeCombat_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> PROJECTSIMULATION_API UClass* StaticClass<class UMeleeCombat>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID ProjectSimulation_Source_ProjectSimulation_MeleeCombat_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
