// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AssetTypeActions_Base.h"
#include "Editor/UnrealEd/Classes/Settings/EditorLoadingSavingSettings.h"

/**
 * 
 */
class ELIASPLUGIN_API FAssetTypeActions_EliasTheme : public FAssetTypeActions_Base
{
public:
	// IAssetTypeActions Implementation
	virtual FText GetName() const override { return FText::FromString("Elias Theme"); }
	virtual FColor GetTypeColor() const override { return FColor(12, 173, 12); }
	virtual UClass* GetSupportedClass() const override;
	virtual uint32 GetCategories() override { return EAssetTypeCategories::Misc; }

};
