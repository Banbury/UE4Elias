# UE4Elias
[ELIAS](https://www.eliassoftware.com/) is a software and library to create and play adaptive game music.
UE4Elias is a plugin for Unreal Engine 4, that plays music created in ELIAS Composer's Studio.

*I'm not affiliated with Elias Software. Don't expect Elias Software to support this plugin.*

## Prerequisites
- [Unreal Engine 4.8+](https://www.unrealengine.com/)
- [Elias SDK](https://www.eliassoftware.com/dload/#) - To compile the plugin for the UE4 editor the 64bit version is needed. At the time of writing the 64bit SDK is not publicly available. Ask Elias Software for it.
- [FMOD Studio for Unreal Engine 4](http://www.fmod.org/download/)
- [Visual Studio 2013](https://www.visualstudio.com/en-us/downloads/download-visual-studio-vs.aspx) - Newer versions might work, too.

## Installation
- Clone the Github repository somewhere on your harddisk
- Unzip the FMOD Studio plugin into the `Plugin` folder
- In the folder `ThirdParty` create a folder `elias`
- From the Elias SDK copy `elias.h` to the `elias` folder
- In the `elias` folder create two folder `x64` and `x86`
- Copy the 32bit version of `elias.lib` and `elias.dll` to the `x86` folder
- Copy the 64bit version of `elias.lib` and `elias.dll` to the `x64` folder
- Right click `EliasTest.uproject` and click on `Generate Visual Studio project files`

## Usage
Open the Visual Studio solution in Visual Studio 2013 and compile it. 
You can now open the EliasTest project in Unreal Engine 4.

To use this plugin you will need a project created in ELIAS Composer's Studio. 
You can download samples from the Elias website.

All functions of the plugin can be used with Blueprints. Currently there are over a dozen Blueprint functions defined
for playing Elias projects and controlling the playback. These functions are patterned after the functions in the Elias SDK.
Please look there for documentation on how to use these function.

For basic use only three nodes are needed.

- Create Theme from Xml - has a path parameter, that has to point to the Elias project file; returns
an Elias Theme object
- Play - Plays an Elias Theme object
- Set Level - this node controls what part of the Elias Theme is played
