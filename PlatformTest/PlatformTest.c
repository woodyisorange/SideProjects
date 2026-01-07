#include <Platform/X11_Platform.h>

void Game_MainEntry(int ArgumentCount, const char** Arguments)
{
    platform_parameters PlatformParameters;
    PlatformParameters.WindowWidth = 800;
    PlatformParameters.WindowHeight = 600;

    Platform_ProcessCommonArguments(ArgumentCount, Arguments, &PlatformParameters);

    Platform_MainLoop(&PlatformParameters);
}

void Game_Tick()
{
}

#define X11_PLATFORM_IMPLEMENTATION
#include <Platform/X11_Platform.h>
