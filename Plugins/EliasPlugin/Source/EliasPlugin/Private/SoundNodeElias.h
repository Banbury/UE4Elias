// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Sound/SoundNode.h"
#include "EliasTheme.h"
#include "SoundNodeElias.generated.h"

/**
 * 
 */
UCLASS()
class ELIASPLUGIN_API USoundNodeElias : public USoundNode
{
	GENERATED_BODY()

	virtual int32 GetMaxChildNodes() const override;
	virtual float GetDuration() override;
	virtual void ParseNodes(FAudioDevice* AudioDevice, const UPTRINT NodeWaveInstanceHash, FActiveSound& ActiveSound, const FSoundParseParameters& ParseParams, TArray<FWaveInstance*>& WaveInstances) override;
#if WITH_EDITOR
	virtual FString GetTitle() const override;
#endif
	
private:
	UEliasTheme* theme;
};
