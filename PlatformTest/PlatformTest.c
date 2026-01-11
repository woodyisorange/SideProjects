#include <Platform/X11_Platform.h>
#include <Utilities/Strings.h>

int32 Game_MainEntry(int32 ArgumentCount, const utf8** Arguments)
{
    platform_parameters PlatformParameters;
    PlatformParameters.WindowWidth = 800;
    PlatformParameters.WindowHeight = 600;
    PlatformParameters.TargetTicksPerSecond = 60;

    Platform_ProcessCommonArguments(ArgumentCount, Arguments, &PlatformParameters);

    Platform_MainLoop(&PlatformParameters);

    return 0;
}

void Game_Tick(int64 DeltaTimeMicroseconds)
{
    Platform_Print("Tick: %ld us\n", DeltaTimeMicroseconds);
}

#include <Platform/X11_Platform.c>
