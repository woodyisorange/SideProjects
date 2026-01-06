#include <Platform/X11_Platform.h>

void Game_MainEntry(int ArgumentCount, const char** Arguments)
{
    platform_parameters PlatformParameters;
    PlatformParameters.WindowWidth = 800;
    PlatformParameters.WindowHeight = 600;

    for (int Index = 0; Index < ArgumentCount; ++Index)
    {
        if (__builtin_strcmp(Arguments[Index], "-width") == 0 && (Index+1) < ArgumentCount)
        {
            __builtin_sscanf(Arguments[Index+1], "%d", &PlatformParameters.WindowWidth);
        }
        else if (__builtin_strcmp(Arguments[Index], "-height") == 0 && (Index+1) < ArgumentCount)
        {
            __builtin_sscanf(Arguments[Index+1], "%d", &PlatformParameters.WindowHeight);
        }
    }

    Platform_MainLoop(&PlatformParameters);
}

void Game_Tick()
{
}

#define X11_PLATFORM_IMPLEMENTATION
#include <Platform/X11_Platform.h>
