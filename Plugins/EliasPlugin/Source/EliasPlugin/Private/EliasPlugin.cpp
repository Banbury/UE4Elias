#include "EliasPluginPCH.h"
#include "AssetRegistryModule.h"
#include "AssetToolsModule.h"
#include "AssetTypeActions_EliasTheme.h"

IMPLEMENT_MODULE(FEliasPlugin, EliasPlugin)

DEFINE_LOG_CATEGORY(LogElias);

FMOD::System* FEliasPlugin::FMSYS;

void FEliasPlugin::StartupModule()
{
	UE_LOG(LogElias, Log, TEXT("Elias Plugin Startup"));
	IAssetTools& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	AssetToolsModule.RegisterAssetTypeActions(MakeShareable(new FAssetTypeActions_EliasTheme));

	FMOD::System_Create(&FMSYS);
	FMSYS->init(1000, FMOD_INIT_NORMAL, 0);
}

void FEliasPlugin::ShutdownModule()
{
	UE_LOG(LogElias, Log, TEXT("Elias Plugin Shutdown"));

	if (FMSYS != NULL)
	{
		FMSYS->close();
		FMSYS->release();
	}
}
