// Fill out your copyright notice in the Description page of Project Settings.

#include "EliasPluginPCH.h"
#include "EliasTrack.h"

UEliasTrack* UEliasTrack::CreateAudioLoopTrack()
{
	elias_track_handle handle;
	elias_track_create_audio_loop_track(&handle);
	auto track = NewObject<UEliasTrack>();
	track->track_handle = handle;
	return track;
}

UEliasTrack::UEliasTrack()
{

}

void UEliasTrack::BeginDestroy()
{
	if (this->track_handle != NULL)
	{
		elias_track_destroy(this->track_handle);
	}
	Super::BeginDestroy();
}