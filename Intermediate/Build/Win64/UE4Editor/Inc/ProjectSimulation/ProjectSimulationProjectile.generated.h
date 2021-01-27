// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UPrimitiveComponent;
class AActor;
struct FVector;
struct FHitResult;
#ifdef PROJECTSIMULATION_ProjectSimulationProjectile_generated_h
#error "ProjectSimulationProjectile.generated.h already included, missing '#pragma once' in ProjectSimulationProjectile.h"
#endif
#define PROJECTSIMULATION_ProjectSimulationProjectile_generated_h

#define ProjectSimulation_Source_ProjectSimulation_ProjectSimulationProjectile_h_12_SPARSE_DATA
#define ProjectSimulation_Source_ProjectSimulation_ProjectSimulationProjectile_h_12_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execOnHit);


#define ProjectSimulation_Source_ProjectSimulation_ProjectSimulationProjectile_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnHit);


#define ProjectSimulation_Source_ProjectSimulation_ProjectSimulationProjectile_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAProjectSimulationProjectile(); \
	friend struct Z_Construct_UClass_AProjectSimulationProjectile_Statics; \
public: \
	DECLARE_CLASS(AProjectSimulationProjectile, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/ProjectSimulation"), NO_API) \
	DECLARE_SERIALIZER(AProjectSimulationProjectile) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define ProjectSimulation_Source_ProjectSimulation_ProjectSimulationProjectile_h_12_INCLASS \
private: \
	static void StaticRegisterNativesAProjectSimulationProjectile(); \
	friend struct Z_Construct_UClass_AProjectSimulationProjectile_Statics; \
public: \
	DECLARE_CLASS(AProjectSimulationProjectile, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/ProjectSimulation"), NO_API) \
	DECLARE_SERIALIZER(AProjectSimulationProjectile) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define ProjectSimulation_Source_ProjectSimulation_ProjectSimulationProjectile_h_12_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AProjectSimulationProjectile(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AProjectSimulationProjectile) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AProjectSimulationProjectile); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AProjectSimulationProjectile); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AProjectSimulationProjectile(AProjectSimulationProjectile&&); \
	NO_API AProjectSimulationProjectile(const AProjectSimulationProjectile&); \
public:


#define ProjectSimulation_Source_ProjectSimulation_ProjectSimulationProjectile_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AProjectSimulationProjectile(AProjectSimulationProjectile&&); \
	NO_API AProjectSimulationProjectile(const AProjectSimulationProjectile&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AProjectSimulationProjectile); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AProjectSimulationProjectile); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AProjectSimulationProjectile)


#define ProjectSimulation_Source_ProjectSimulation_ProjectSimulationProjectile_h_12_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__CollisionComp() { return STRUCT_OFFSET(AProjectSimulationProjectile, CollisionComp); } \
	FORCEINLINE static uint32 __PPO__ProjectileMovement() { return STRUCT_OFFSET(AProjectSimulationProjectile, ProjectileMovement); }


#define ProjectSimulation_Source_ProjectSimulation_ProjectSimulationProjectile_h_9_PROLOG
#define ProjectSimulation_Source_ProjectSimulation_ProjectSimulationProjectile_h_12_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ProjectSimulation_Source_ProjectSimulation_ProjectSimulationProjectile_h_12_PRIVATE_PROPERTY_OFFSET \
	ProjectSimulation_Source_ProjectSimulation_ProjectSimulationProjectile_h_12_SPARSE_DATA \
	ProjectSimulation_Source_ProjectSimulation_ProjectSimulationProjectile_h_12_RPC_WRAPPERS \
	ProjectSimulation_Source_ProjectSimulation_ProjectSimulationProjectile_h_12_INCLASS \
	ProjectSimulation_Source_ProjectSimulation_ProjectSimulationProjectile_h_12_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define ProjectSimulation_Source_ProjectSimulation_ProjectSimulationProjectile_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ProjectSimulation_Source_ProjectSimulation_ProjectSimulationProjectile_h_12_PRIVATE_PROPERTY_OFFSET \
	ProjectSimulation_Source_ProjectSimulation_ProjectSimulationProjectile_h_12_SPARSE_DATA \
	ProjectSimulation_Source_ProjectSimulation_ProjectSimulationProjectile_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	ProjectSimulation_Source_ProjectSimulation_ProjectSimulationProjectile_h_12_INCLASS_NO_PURE_DECLS \
	ProjectSimulation_Source_ProjectSimulation_ProjectSimulationProjectile_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> PROJECTSIMULATION_API UClass* StaticClass<class AProjectSimulationProjectile>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID ProjectSimulation_Source_ProjectSimulation_ProjectSimulationProjectile_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
