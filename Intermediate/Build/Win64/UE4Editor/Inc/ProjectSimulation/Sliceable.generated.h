// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef PROJECTSIMULATION_Sliceable_generated_h
#error "Sliceable.generated.h already included, missing '#pragma once' in Sliceable.h"
#endif
#define PROJECTSIMULATION_Sliceable_generated_h

#define ProjectSimulation_Source_ProjectSimulation_Sliceable_h_13_SPARSE_DATA
#define ProjectSimulation_Source_ProjectSimulation_Sliceable_h_13_RPC_WRAPPERS
#define ProjectSimulation_Source_ProjectSimulation_Sliceable_h_13_RPC_WRAPPERS_NO_PURE_DECLS
#define ProjectSimulation_Source_ProjectSimulation_Sliceable_h_13_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesASliceable(); \
	friend struct Z_Construct_UClass_ASliceable_Statics; \
public: \
	DECLARE_CLASS(ASliceable, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/ProjectSimulation"), NO_API) \
	DECLARE_SERIALIZER(ASliceable)


#define ProjectSimulation_Source_ProjectSimulation_Sliceable_h_13_INCLASS \
private: \
	static void StaticRegisterNativesASliceable(); \
	friend struct Z_Construct_UClass_ASliceable_Statics; \
public: \
	DECLARE_CLASS(ASliceable, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/ProjectSimulation"), NO_API) \
	DECLARE_SERIALIZER(ASliceable)


#define ProjectSimulation_Source_ProjectSimulation_Sliceable_h_13_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ASliceable(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ASliceable) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASliceable); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASliceable); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ASliceable(ASliceable&&); \
	NO_API ASliceable(const ASliceable&); \
public:


#define ProjectSimulation_Source_ProjectSimulation_Sliceable_h_13_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ASliceable(ASliceable&&); \
	NO_API ASliceable(const ASliceable&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASliceable); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASliceable); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ASliceable)


#define ProjectSimulation_Source_ProjectSimulation_Sliceable_h_13_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__mesh() { return STRUCT_OFFSET(ASliceable, mesh); } \
	FORCEINLINE static uint32 __PPO__pm() { return STRUCT_OFFSET(ASliceable, pm); }


#define ProjectSimulation_Source_ProjectSimulation_Sliceable_h_10_PROLOG
#define ProjectSimulation_Source_ProjectSimulation_Sliceable_h_13_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ProjectSimulation_Source_ProjectSimulation_Sliceable_h_13_PRIVATE_PROPERTY_OFFSET \
	ProjectSimulation_Source_ProjectSimulation_Sliceable_h_13_SPARSE_DATA \
	ProjectSimulation_Source_ProjectSimulation_Sliceable_h_13_RPC_WRAPPERS \
	ProjectSimulation_Source_ProjectSimulation_Sliceable_h_13_INCLASS \
	ProjectSimulation_Source_ProjectSimulation_Sliceable_h_13_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define ProjectSimulation_Source_ProjectSimulation_Sliceable_h_13_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ProjectSimulation_Source_ProjectSimulation_Sliceable_h_13_PRIVATE_PROPERTY_OFFSET \
	ProjectSimulation_Source_ProjectSimulation_Sliceable_h_13_SPARSE_DATA \
	ProjectSimulation_Source_ProjectSimulation_Sliceable_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	ProjectSimulation_Source_ProjectSimulation_Sliceable_h_13_INCLASS_NO_PURE_DECLS \
	ProjectSimulation_Source_ProjectSimulation_Sliceable_h_13_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> PROJECTSIMULATION_API UClass* StaticClass<class ASliceable>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID ProjectSimulation_Source_ProjectSimulation_Sliceable_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
