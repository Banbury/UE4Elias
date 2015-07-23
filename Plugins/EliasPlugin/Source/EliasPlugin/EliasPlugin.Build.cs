using UnrealBuildTool;
using System.IO;

public class EliasPlugin : ModuleRules
{
    public EliasPlugin(TargetInfo Target)
    {
        PrivateIncludePaths.Add("EliasPlugin/Private");

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EditorStyle", "UnrealEd", "AssetTools" });

        PrivateDependencyModuleNames.AddRange(new string[] { "FMODStudio" });

        DynamicallyLoadedModuleNames.AddRange(new string[] { });

        LoadElias(Target);
        LoadLibsndfile(Target);
    }

    public bool LoadElias(TargetInfo Target)
    {
        bool isLibrarySupported = false;

        if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
        {
            isLibrarySupported = true;

            string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "x64" : "x86";
            string LibrariesPath = Path.Combine(ThirdPartyPath, "elias", PlatformString);

            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "elias.lib"));
        }

        if (isLibrarySupported)
        {
            // Include path
            PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "elias"));
        }

        Definitions.Add(string.Format("WITH_ELIAS_BINDING={0}", isLibrarySupported ? 1 : 0));

        return isLibrarySupported;
    }

    public bool LoadLibsndfile(TargetInfo Target)
    {
        bool isLibrarySupported = false;

        if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
        {
            isLibrarySupported = true;

            string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "x64" : "x86";
            string LibrariesPath = Path.Combine(ThirdPartyPath, "libsndfile", PlatformString);

            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "libsndfile-1.lib"));
        }

        if (isLibrarySupported)
        {
            // Include path
            PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "libsndfile"));
        }

        Definitions.Add(string.Format("WITH_LIBSNDFILE_BINDING={0}", isLibrarySupported ? 1 : 0));

        return isLibrarySupported;
    }

    private string ModulePath
    {
        get { return Path.GetDirectoryName(RulesCompiler.GetModuleFilename(this.GetType().Name)); }
    }

    private string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(ModulePath, "../../../../ThirdParty/")); }
    }
}