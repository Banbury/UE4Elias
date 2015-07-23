// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define _MSC_VER

#include "Object.h"
#include <elias.h>
#include "EliasTrack.generated.h"

/**
 * 
 */
UCLASS()
class ELIASPLUGIN_API UEliasTrack : public UObject
{
	GENERATED_BODY()

public:
	elias_track_handle track_handle;

	UFUNCTION(BlueprintCallable, Category = "Elias")
	static UEliasTrack* CreateAudioLoopTrack();
	
	UEliasTrack();

	void BeginDestroy();
};
