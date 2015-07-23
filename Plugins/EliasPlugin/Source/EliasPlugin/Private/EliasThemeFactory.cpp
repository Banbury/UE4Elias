// Fill out your copyright notice in the Description page of Project Settings.

#include "EliasPluginPCH.h"
#include "EliasTheme.h"
#include "EliasThemeFactory.h"

#define LOCTEXT_NAMESPACE "EliasTheme"

UEliasThemeFactory::UEliasThemeFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UEliasTheme::StaticClass();
}

UObject* UEliasThemeFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	UEliasTheme* NewObjectAsset = NewObject<UEliasTheme>(InParent, Name, Flags | RF_Transactional);
	return NewObjectAsset;
}

#undef LOCTEXT_NAMESPACE