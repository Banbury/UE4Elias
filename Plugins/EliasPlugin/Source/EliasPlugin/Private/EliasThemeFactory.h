// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Factories/Factory.h"
#include "UnrealEd.h"
#include "EliasThemeFactory.generated.h"

/**
 * 
 */
UCLASS()
class ELIASPLUGIN_API UEliasThemeFactory : public UFactory
{
	GENERATED_BODY()

	UEliasThemeFactory(const FObjectInitializer& ObjectInitializer);
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
