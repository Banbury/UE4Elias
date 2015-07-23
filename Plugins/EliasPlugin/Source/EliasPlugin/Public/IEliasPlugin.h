#pragma once

#include "ModuleManager.h"

class IEliasPlugin : public IModuleInterface
{
public:
	static inline IEliasPlugin& Get()
	{
		return FModuleManager::LoadModuleChecked< IEliasPlugin >("EliasPlugin");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("EliasPlugin");
	}
};