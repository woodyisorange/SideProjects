#pragma once

#include <Platform/X11_Types.h>

int32 Util_StringCompare(const char* StringA, const char* StringB)
{
    return __builtin_strcmp(StringA, StringB);
}

void Util_ParseInt32(const char* String, int32* Result)
{
    __builtin_sscanf(String, "%d", Result);
}

