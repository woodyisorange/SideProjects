#include <Platform/X11_Platform.h>
#include <Utilities/Strings.h>

#define _POSIX_C_SOURCE 200809L
#include <X11/Xlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <time.h>

int main(int ArgumentCount, const char** Arguments)
{
    return Game_MainEntry(ArgumentCount, Arguments);
}

int64 Platform_GetTimeMicroseconds()
{
    struct timespec ClockTime;
    clock_gettime(CLOCK_MONOTONIC_RAW, &ClockTime);

    int64 TimeMicroseconds = (ClockTime.tv_sec * 1000000) + (ClockTime.tv_nsec / 1000);
    return TimeMicroseconds;
}

void Platform_Print(const utf8* Format, ...)
{
    //TODO: Proper string printing handling with util libraries
    va_list Arguments;
    va_start(Arguments, Format);
    __builtin_vprintf(Format, Arguments);
    va_end(Arguments);
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

//TODO: Detect window closing and exit
//TODO: Capture input
//TODO: Pass a backbuffer texture to draw to
void Platform_MainLoop(platform_parameters* Parameters)
{
    Display* MainDisplay = XOpenDisplay(0);
    Window RootWindow = XDefaultRootWindow(MainDisplay);

    Window MainWindow = XCreateSimpleWindow(MainDisplay, RootWindow, 0, 0, Parameters->WindowWidth, Parameters->WindowHeight, 0, 0, 0x00aade87);
    XMapWindow(MainDisplay, MainWindow);
    XFlush(MainDisplay);

    if (Parameters->TargetTicksPerSecond <= 0)
    {
        //TODO: Programming error, needs an assert
        Platform_Print("TargetTicksPerSecond must be a positive value!\n");
        return;
    }

    struct timespec ClockResolution;
    clock_getres(CLOCK_MONOTONIC_RAW, &ClockResolution);

    if (ClockResolution.tv_sec >= 1 || ClockResolution.tv_nsec > 1000)
    {
        Platform_Print("Insufficient hardware clock resolution!\n");
        return;
    }

    int64 TimeStepMicroseconds = (int64)(1000000.0f / (float)Parameters->TargetTicksPerSecond);
    int64 OldTimeMicroseconds = Platform_GetTimeMicroseconds();

    while (TRUE)
    {
        //TODO only called once?
        Game_Tick(TimeStepMicroseconds);

        int64 CurrentTimeMicroseconds = Platform_GetTimeMicroseconds();
        int64 DeltaTimeMicroseconds = CurrentTimeMicroseconds - OldTimeMicroseconds;

        // Wait until the next frame, busy waiting when we're close to the time step
        int64 SpinWaitMicroseconds = 1000;
        while (DeltaTimeMicroseconds < (TimeStepMicroseconds - SpinWaitMicroseconds))
        {
            sleep(0);
            CurrentTimeMicroseconds = Platform_GetTimeMicroseconds();
            DeltaTimeMicroseconds = CurrentTimeMicroseconds - OldTimeMicroseconds;
        }

        while (DeltaTimeMicroseconds < TimeStepMicroseconds)
        {
            CurrentTimeMicroseconds = Platform_GetTimeMicroseconds();
            DeltaTimeMicroseconds = CurrentTimeMicroseconds - OldTimeMicroseconds;
        }
    }
}

