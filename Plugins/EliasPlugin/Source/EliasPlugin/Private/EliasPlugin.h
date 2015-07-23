#pragma once

//#include "EliasPlugin.generated.h"

#include "IEliasPlugin.h"
#include "Engine.h"
#include "EditorStyle.h"
#include "UnrealEd.h"
#include "fmod_studio.hpp"
#include "FMODStudioModule.h"

class FEliasPlugin : public IEliasPlugin
{
	void StartupModule();
	void ShutdownModule();

public:
	static FMOD::System* FMSYS;
};