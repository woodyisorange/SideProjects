#pragma once

#include <Platform/X11_Types.h>

// Includes null terminator
int64 Util_StringLengthBytes(const utf8* String)
{
    if (String == NULL)
    {
        return 0;
    }

    //TODO: Go wide
    const utf8* Tail = String;
    while ((*Tail) != '\0')
    {
        ++Tail;
    }

    int64 Length = (Tail - String) + 1;
    return Length;
}

int32 Util_StringCompare(const utf8* StringA, const utf8* StringB)
{
    if (!StringA && !StringB)
    {
        return 0;
    }

    if (!StringA)
    {
        return 1;
    }

    if (!StringB)
    {
        return -1;
    }

    // TODO: Go wide
    while (TRUE)
    {
        int32 Delta = (*StringA) - (*StringB);

        if (Delta != 0)
        {
            return Delta;
        }

        if (!(*StringA))
        {
            return 0;
        }

        ++StringA;
        ++StringB;
    }
}

bool8 Util_IsNumeral(utf8 Character)
{
    return (Character >= '0' && Character <= '9');
}

bool8 Util_ParseInt32(const utf8* String, int32* Result)
{
    bool8 IsNegative = (*String) == '-';
    if (IsNegative || ((*String) == '+'))
    {
        ++String;
    }

    if (!Util_IsNumeral(*String))
    {
        return FALSE;
    }

    *Result = (*String) - '0';
    ++String;

    while (Util_IsNumeral(*String))
    {
        (*Result) *= 10;
        (*Result) += (*String) - '0';
        ++String;
    }

    if (IsNegative)
    {
        (*Result) = -(*Result);
    }

    return TRUE;
}

