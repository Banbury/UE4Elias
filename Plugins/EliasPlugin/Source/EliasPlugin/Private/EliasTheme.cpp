// Fill out your copyright notice in the Description page of Project Settings.

#include "EliasPluginPCH.h"
#include "EliasTheme.h"

UEliasTheme* UEliasTheme::CreateThemeFromXml(FString path)
{
	if (!path.IsEmpty())
	{
		auto theme = NewObject<UEliasTheme>();
		theme->XmlPath = path;
		theme->LoadXml();
		return theme;

		//FString xml;
		//FFileHelper::LoadFileToString(xml, *path);
		//elias_theme_handle theme_handle;
		//char error[1024] = "";
		//elias_error err = elias_theme_create_from_xml(&theme_handle, TCHAR_TO_ANSI(*xml), error, 1024, 0);
		//if (err == elias_error_success)
		//{
		//	auto theme = NewObject<UEliasTheme>();

		//	theme->theme_handle = theme_handle;
		//	theme->XmlPath = path;
		//	elias_theme_set_prebuffer_length_in_milliseconds(theme_handle, 1000);
		//	return theme;
		//}
	}
	return NULL;
}

UEliasTheme::UEliasTheme() : Super()
{
}

void UEliasTheme::Update()
{
	FEliasPlugin::FMSYS->update();
	auto FMSTSYS = IFMODStudioModule::Get().GetStudioSystem(EFMODSystemContext::Runtime);
	if (FMSTSYS != NULL)
	{
		FMSTSYS->update();
	}
}

void UEliasTheme::BeginDestroy()
{
	if (this->theme_handle != NULL)
	{
		Stop();
		elias_theme_destroy(this->theme_handle);

		while (context.sources.Num() > 0)
		{
			delete context.sources[0];
			context.sources.RemoveAt(0, true);
		}
	}
	UObject::BeginDestroy();
}

void UEliasTheme::GetBasicInfo(int32& bpm, int32& timesig_numerator, int32& timesig_denominator, int32& bars, int32& sample_rate, int32& channels)
{
	long l_sample_rate;
	elias_theme_get_basic_info(theme_handle, &bpm, &timesig_numerator, &timesig_denominator, &bars, &l_sample_rate, &channels);
	sample_rate = l_sample_rate;
}

void UEliasTheme::Play() 
{
	unsigned int sourceCount;
	elias_theme_get_source_count(theme_handle, &sourceCount);

	if (sourceCount > 0)
	{
		FString dummy;
		FPaths::Split(XmlPath, context.base_path, dummy, dummy);
		FPaths::NormalizeDirectoryName(context.base_path);
		elias_error err = elias_theme_enumerate_sources(theme_handle, &EliasSourceEnumerationCallback, (void*)&context);
		if (err == elias_error_success)
		{
			int channels;
			long sample_rate;
			int dummy;
			elias_theme_get_basic_info(theme_handle, &dummy, &dummy, &dummy, &dummy, &sample_rate, &channels);
			unsigned long length;
			elias_theme_get_theme_length_in_milliseconds(theme_handle, &length);

			FMOD_CREATESOUNDEXINFO exinfo = {0};
			exinfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
			exinfo.length = (sample_rate * channels) * sizeof(elias_sample) * length / 1000;
			exinfo.pcmreadcallback = this->FMOD_read_callback;
			exinfo.userdata = (void*)this;
			exinfo.format = FMOD_SOUND_FORMAT_PCM16;
			exinfo.numchannels = channels;
			exinfo.defaultfrequency = sample_rate;
			exinfo.decodebuffersize = sample_rate;

			elias_theme_start(theme_handle, &EliasDataCallback, 0, -1, 1, 1, 100, 0, 0);
			FMOD_RESULT res = FEliasPlugin::FMSYS->createStream("test", FMOD_OPENUSER | FMOD_LOOP_NORMAL, &exinfo, &this->sound);
			if (res == FMOD_OK)
			{
				FEliasPlugin::FMSYS->playSound(this->sound, NULL, false, &channel);
			}
		}
	}
}

void UEliasTheme::Stop()
{
	channel->stop();
	elias_theme_stop(theme_handle);
	sound->release();
}

void UEliasTheme::SetLevel(int32 minimum_level, int32 maximum_level, int32 urgency, int32 stinger, bool immediately, bool rendezvous)
{
	if (theme_handle != NULL)
	{
		elias_theme_set_level(theme_handle, minimum_level, maximum_level, urgency, stinger, immediately, rendezvous);
	}
}

EThemeMode UEliasTheme::GetMode()
{
	if (theme_handle != NULL)
	{
		int mode;
		elias_theme_get_mode(theme_handle, &mode);
		return (EThemeMode)mode;
	}

	return EThemeMode::Objective;
}

void UEliasTheme::SetMode(EThemeMode value=EThemeMode::Objective)
{
	if (theme_handle != NULL)
	{
		elias_theme_set_mode(theme_handle, (int)value);
	}
}


void UEliasTheme::RequestChange(int32 track_count, int32 urgency, int32 stinger, bool immediately, bool rendezvous)
{
	if (theme_handle != NULL)
	{
		elias_theme_request_change(theme_handle, track_count, urgency, stinger, immediately, rendezvous);
	}
}

void UEliasTheme::Silence(int32 urgency, int32 stinger, bool immediately, bool rendezvous)
{
	if (theme_handle != NULL)
	{
		elias_theme_silence(theme_handle, urgency, stinger, immediately, rendezvous);
	}
}

void UEliasTheme::PlayStinger(int32 stinger)
{
	if (theme_handle != NULL)
	{
		elias_theme_play_stinger(theme_handle, stinger);
	}
}

void UEliasTheme::ChangeKey(int32 key, int32 immediately)
{
	if (theme_handle != NULL)
	{
		elias_theme_change_key(theme_handle, key, immediately);
	}
}

bool UEliasTheme::IsTransitioning()
{
	if (theme_handle != NULL)
	{
		int ret;
		elias_theme_is_transitioning(theme_handle, &ret);
		return ret != 0;
	}
	return false;
}

FMOD_RESULT UEliasTheme::FMOD_read_callback(FMOD_SOUND *sound, void *data, unsigned int datalen)
{
	FMOD::Sound* snd = (FMOD::Sound*)sound;
	UEliasTheme* theme;
	snd->getUserData((void**)&theme);

	size_t total_samples = datalen / sizeof(elias_sample);
	size_t result = total_samples;
	
	elias_sample* buf = (elias_sample*)data;
	if (int err = elias_theme_read_samples(theme->theme_handle, buf, &result) != elias_error_success)
	{
		return FMOD_ERR_INTERNAL;
	}

	return FMOD_OK;
}

int EliasSourceEnumerationCallback(const elias_source* source, void** source_user_data, void* user_data)
{
	if (!source->dummy && source->filename != NULL)
	{
		EliasContext* context = (EliasContext*)user_data;
		TArray<EliasSource*>* arr = (TArray<EliasSource*>*)&context->sources;
		FString path;
		path = FPaths::Combine(*context->base_path, ANSI_TO_TCHAR(source->filename));

		EliasSource* esource = new EliasSource;
		esource->path = path;
		arr->Add(esource);
		*source_user_data = (void *)esource;

		return 1;
	}

	return 1;
}

int EliasDataCallback(int action, const elias_source* source, elias_sample* buffer, size_t count, void* user_data) {
	EliasSource* sound = (EliasSource*)source->source_user_data;
	if (sound != NULL)
	{
		switch (action)
		{
		case elias_action_open:
			SF_INFO info;
			info.format = 0;
			sound->sndfile = sf_open(TCHAR_TO_ANSI(*sound->path), SFM_READ, &info);
			return 1;
		case elias_action_close:
			sf_close(sound->sndfile);
			return 1;
		case elias_action_read:
		{
			short* buf = (short*)buffer;
			sf_count_t n = sf_read_short(sound->sndfile, buf, count);
			return 1;
		}
		case elias_action_seek:
			sf_seek(sound->sndfile, count, SEEK_SET);
			return 1;
		}
	}

	return 0;
}

void UEliasTheme::Tick(float DeltaTime)
{
	Update();
}

bool UEliasTheme::IsTickable() const
{
	return true;
}

void UEliasTheme::LoadXml()
{
	FString xml;
	FFileHelper::LoadFileToString(xml, *XmlPath);
	char error[1024] = "";
	elias_error err = elias_theme_create_from_xml(&theme_handle, TCHAR_TO_ANSI(*xml), error, 1024, 0);
	if (err == elias_error_success)
	{
		elias_theme_set_prebuffer_length_in_milliseconds(theme_handle, 1000);
	}

}