// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tickable.h"
#include <sndfile.h>
#include "EliasTheme.generated.h"

struct EliasSource
{
	FString path;
	SNDFILE* sndfile;
};

struct EliasContext
{
	FString base_path;
	TArray<EliasSource*> sources;
};

UENUM(BlueprintType)
enum class EThemeMode : uint8
{
	Objective = 1, Exploration = 2
};

/**
 * 
 */
UCLASS(Blueprintable)
class ELIASPLUGIN_API UEliasTheme : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(UEliasTheme, STATGROUP_Tickables);
	}

public:
	elias_theme_handle theme_handle;

	UEliasTheme();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString XmlPath;

	UFUNCTION(BlueprintCallable, Category = "Elias")
	static UEliasTheme* CreateThemeFromXml(FString path);

	void BeginDestroy() override;

	void Update();

	UFUNCTION(BlueprintCallable, Category = "Elias")
	void Play();

	UFUNCTION(BlueprintCallable, Category = "Elias")
	void Stop();

	UFUNCTION(BlueprintCallable, Category = "Elias")
	void SetLevel(int32 minimum_level, int32 maximum_level, int32 urgency, int32 stinger, bool immediately, bool rendezvous);

	UFUNCTION(BlueprintCallable, Category = "Elias")
	void RequestChange(int32 track_count, int32 urgency, int32 stinger, bool immediately, bool rendezvous);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Elias")
	void GetBasicInfo(int32& bpm, int32& timesig_numerator, int32& timesig_denominator, int32& bars, int32& sample_rate, int32& channels);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Elias")
	EThemeMode GetMode();

	UFUNCTION(BlueprintCallable, Category = "Elias")
	void SetMode(EThemeMode value);

	UFUNCTION(BlueprintCallable, Category = "Elias")
	void Silence(int32 urgency, int32 stinger, bool immediately, bool rendezvous);

	UFUNCTION(BlueprintCallable, Category = "Elias")
	void PlayStinger(int32 stinger);

	UFUNCTION(BlueprintCallable, Category = "Elias")
	void ChangeKey(int32 key, int32 immediately);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Elias")
	bool IsTransitioning();

	void LoadXml();

private:
	EliasContext context;
	FMOD::Sound* sound;
	FMOD::Channel* channel;

	static FMOD_RESULT F_CALLBACK FMOD_read_callback(FMOD_SOUND *sound, void *data, unsigned int datalen);

};

int EliasDataCallback(int action, const elias_source* source, elias_sample* buffer, size_t count, void* user_data);
int EliasSourceEnumerationCallback(const elias_source* source, void** source_user_data, void* user_data);
