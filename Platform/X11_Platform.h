#pragma once

#include <Platform/X11_Types.h>

// Platform layer expects application to define this.
int32 Game_MainEntry(int32 ArgumentCount, const utf8** Arguments);
void Game_Tick(int64 DeltaMicroseconds);

typedef struct
{
    int32 WindowWidth;
    int32 WindowHeight;
    int32 TargetTicksPerSecond;
} platform_parameters;

void Platform_ProcessCommonArguments(int32 ArgumentCount, const utf8** Arguments, platform_parameters* Parameters);

void Platform_MainLoop(platform_parameters* Parameters);

void Platform_Print(const utf8* Format, ...);

