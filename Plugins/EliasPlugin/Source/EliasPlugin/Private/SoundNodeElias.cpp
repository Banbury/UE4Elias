// Fill out your copyright notice in the Description page of Project Settings.

#include "EliasPluginPCH.h"
#include "SoundNodeElias.h"

int32 USoundNodeElias::GetMaxChildNodes() const
{
	return 0;
}

float USoundNodeElias::GetDuration()
{
	return INDEFINITELY_LOOPING_DURATION;
}

void USoundNodeElias::ParseNodes(FAudioDevice* AudioDevice, const UPTRINT NodeWaveInstanceHash, FActiveSound& ActiveSound, const FSoundParseParameters& ParseParams, TArray<FWaveInstance*>& WaveInstances)
{
	if (this->theme == NULL)
	{
		this->theme = UEliasTheme::CreateThemeFromXml(TEXT("z:\\Unreal Projects\\Assets\\elias\\objective\\objective.epro"));
		this->theme->Play();
	}
	if (this->theme != NULL) 
	{
//		this->theme->Parse(AudioDevice, NodeWaveInstanceHash, ActiveSound, ParseParams, WaveInstances);
	}
}

#if WITH_EDITOR

FString USoundNodeElias::GetTitle() const
{
	return TEXT("Elias Source");
}
#endif