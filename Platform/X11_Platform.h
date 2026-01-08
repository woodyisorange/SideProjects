#ifndef X11_PLATFORM_GUARD
#define X11_PLATFORM_GUARD

#include <Platform/X11_Types.h>

typedef struct
{
    int32 WindowWidth;
    int32 WindowHeight;
} platform_parameters;

void Platform_ProcessCommonArguments(int32 ArgumentCount, const utf8** Arguments, platform_parameters* Parameters);

void Platform_MainLoop(platform_parameters* Parameters);

void Platform_Sleep(int32 Microseconds);

#endif // X11_PLATFORM_GUARD

#ifdef X11_PLATFORM_IMPLEMENTATION

#include <Utilities/Strings.h>

#define _POSIX_C_SOURCE 199309L
#include <X11/Xlib.h>
#include <unistd.h>
#include <time.h>

int main(int ArgumentCount, const char** Arguments)
{
    Game_MainEntry(ArgumentCount, Arguments);
}

void Platform_ProcessCommonArguments(int32 ArgumentCount, const utf8** Arguments, platform_parameters* Parameters)
{
    for (int32 Index = 0; Index < ArgumentCount; ++Index)
    {
        if (Util_StringCompare(Arguments[Index], "-width") == 0 && (Index+1) < ArgumentCount)
        {
            Util_ParseInt32(Arguments[Index+1], &Parameters->WindowWidth);
        }
        else if (__builtin_strcmp(Arguments[Index], "-height") == 0 && (Index+1) < ArgumentCount)
        {
            Util_ParseInt32(Arguments[Index+1], &Parameters->WindowHeight);
        }
    }
}

void Platform_MainLoop(platform_parameters* Parameters)
{
    Display* MainDisplay = XOpenDisplay(0);
    Window RootWindow = XDefaultRootWindow(MainDisplay);

    Window MainWindow = XCreateSimpleWindow(MainDisplay, RootWindow, 0, 0, Parameters->WindowWidth, Parameters->WindowHeight, 0, 0, 0x00aade87);
    XMapWindow(MainDisplay, MainWindow);
    XFlush(MainDisplay);

    while (1)
    {
        Game_Tick();
        Platform_Sleep(0);
    }
}

void Platform_Sleep(int32 Microseconds)
{
    struct timespec TimeSpec;
    TimeSpec.tv_nsec = Microseconds * 1000;

    //TODO: Properly handle remainder, maybe use clock_nanosleep()?
    nanosleep(&TimeSpec, NULL);
}

#endif // X11_PLATFORM_IMPLEMENTATION

