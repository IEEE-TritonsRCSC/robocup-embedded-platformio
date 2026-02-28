#pragma once

#include <Arduino.h>

#define DEBUG

#ifdef DEBUG

template <typename T>
void PRINT(const T &value)
{
    Serial.print(value);
}

template <typename T, typename... Args>
void PRINT(const T &first, const Args &...rest)
{
    Serial.print(first);
    PRINT(rest...);
}

#else

template <typename... Args>
void PRINT(const Args &...) {}

#endif

static inline int clamp_int(int value, int low, int high)
{
    if (value < low)
    {
        return low;
    }
    if (value > high)
    {
        return high;
    }
    return value;
}
