// Fill out your copyright notice in the Description page of Project Settings.

#include "EliasPluginPCH.h"
#include "EliasTheme.h"
#include "AssetTypeActions_EliasTheme.h"

UClass* FAssetTypeActions_EliasTheme::GetSupportedClass() const
{
	return UEliasTheme::StaticClass();
}

