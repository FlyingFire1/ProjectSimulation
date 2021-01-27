// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef PROJECTSIMULATION_ProjectSimulationCharacter_generated_h
#error "ProjectSimulationCharacter.generated.h already included, missing '#pragma once' in ProjectSimulationCharacter.h"
#endif
#define PROJECTSIMULATION_ProjectSimulationCharacter_generated_h

#define ProjectSimulation_Source_ProjectSimulation_ProjectSimulationCharacter_h_14_SPARSE_DATA
#define ProjectSimulation_Source_ProjectSimulation_ProjectSimulationCharacter_h_14_RPC_WRAPPERS
#define ProjectSimulation_Source_ProjectSimulation_ProjectSimulationCharacter_h_14_RPC_WRAPPERS_NO_PURE_DECLS
#define ProjectSimulation_Source_ProjectSimulation_ProjectSimulationCharacter_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAProjectSimulationCharacter(); \
	friend struct Z_Construct_UClass_AProjectSimulationCharacter_Statics; \
public: \
	DECLARE_CLASS(AProjectSimulationCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/ProjectSimulation"), NO_API) \
	DECLARE_SERIALIZER(AProjectSimulationCharacter)


#define ProjectSimulation_Source_ProjectSimulation_ProjectSimulationCharacter_h_14_INCLASS \
private: \
	static void StaticRegisterNativesAProjectSimulationCharacter(); \
	friend struct Z_Construct_UClass_AProjectSimulationCharacter_Statics; \
public: \
	DECLARE_CLASS(AProjectSimulationCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/ProjectSimulation"), NO_API) \
	DECLARE_SERIALIZER(AProjectSimulationCharacter)


#define ProjectSimulation_Source_ProjectSimulation_ProjectSimulationCharacter_h_14_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AProjectSimulationCharacter(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AProjectSimulationCharacter) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AProjectSimulationCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AProjectSimulationCharacter); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AProjectSimulationCharacter(AProjectSimulationCharacter&&); \
	NO_API AProjectSimulationCharacter(const AProjectSimulationCharacter&); \
public:


#define ProjectSimulation_Source_ProjectSimulation_ProjectSimulationCharacter_h_14_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AProjectSimulationCharacter(AProjectSimulationCharacter&&); \
	NO_API AProjectSimulationCharacter(const AProjectSimulationCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AProjectSimulationCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AProjectSimulationCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AProjectSimulationCharacter)


#define ProjectSimulation_Source_ProjectSimulation_ProjectSimulationCharacter_h_14_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__Mesh1P() { return STRUCT_OFFSET(AProjectSimulationCharacter, Mesh1P); } \
	FORCEINLINE static uint32 __PPO__FP_Gun() { return STRUCT_OFFSET(AProjectSimulationCharacter, FP_Gun); } \
	FORCEINLINE static uint32 __PPO__FP_MuzzleLocation() { return STRUCT_OFFSET(AProjectSimulationCharacter, FP_MuzzleLocation); } \
	FORCEINLINE static uint32 __PPO__VR_Gun() { return STRUCT_OFFSET(AProjectSimulationCharacter, VR_Gun); } \
	FORCEINLINE static uint32 __PPO__VR_MuzzleLocation() { return STRUCT_OFFSET(AProjectSimulationCharacter, VR_MuzzleLocation); } \
	FORCEINLINE static uint32 __PPO__FirstPersonCameraComponent() { return STRUCT_OFFSET(AProjectSimulationCharacter, FirstPersonCameraComponent); } \
	FORCEINLINE static uint32 __PPO__R_MotionController() { return STRUCT_OFFSET(AProjectSimulationCharacter, R_MotionController); } \
	FORCEINLINE static uint32 __PPO__L_MotionController() { return STRUCT_OFFSET(AProjectSimulationCharacter, L_MotionController); } \
	FORCEINLINE static uint32 __PPO__MeleeBox() { return STRUCT_OFFSET(AProjectSimulationCharacter, MeleeBox); } \
	FORCEINLINE static uint32 __PPO__MeleeCombat() { return STRUCT_OFFSET(AProjectSimulationCharacter, MeleeCombat); }


#define ProjectSimulation_Source_ProjectSimulation_ProjectSimulationCharacter_h_11_PROLOG
#define ProjectSimulation_Source_ProjectSimulation_ProjectSimulationCharacter_h_14_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ProjectSimulation_Source_ProjectSimulation_ProjectSimulationCharacter_h_14_PRIVATE_PROPERTY_OFFSET \
	ProjectSimulation_Source_ProjectSimulation_ProjectSimulationCharacter_h_14_SPARSE_DATA \
	ProjectSimulation_Source_ProjectSimulation_ProjectSimulationCharacter_h_14_RPC_WRAPPERS \
	ProjectSimulation_Source_ProjectSimulation_ProjectSimulationCharacter_h_14_INCLASS \
	ProjectSimulation_Source_ProjectSimulation_ProjectSimulationCharacter_h_14_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define ProjectSimulation_Source_ProjectSimulation_ProjectSimulationCharacter_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ProjectSimulation_Source_ProjectSimulation_ProjectSimulationCharacter_h_14_PRIVATE_PROPERTY_OFFSET \
	ProjectSimulation_Source_ProjectSimulation_ProjectSimulationCharacter_h_14_SPARSE_DATA \
	ProjectSimulation_Source_ProjectSimulation_ProjectSimulationCharacter_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	ProjectSimulation_Source_ProjectSimulation_ProjectSimulationCharacter_h_14_INCLASS_NO_PURE_DECLS \
	ProjectSimulation_Source_ProjectSimulation_ProjectSimulationCharacter_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> PROJECTSIMULATION_API UClass* StaticClass<class AProjectSimulationCharacter>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID ProjectSimulation_Source_ProjectSimulation_ProjectSimulationCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
