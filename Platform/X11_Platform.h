#ifndef X11_PLATFORM_GUARD
#define X11_PLATFORM_GUARD

typedef struct
{
    int WindowWidth;
    int WindowHeight;
} platform_parameters;

void Platform_MainLoop(platform_parameters* Parameters);

#endif // X11_PLATFORM_GUARD

#ifdef X11_PLATFORM_IMPLEMENTATION

#include <X11/Xlib.h>
#include <unistd.h>

int main(int ArgumentCount, const char** Arguments)
{
    Game_MainEntry(ArgumentCount, Arguments);
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
        sleep(0);
    }
}

#endif // X11_PLATFORM_IMPLEMENT

