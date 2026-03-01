#pragma once

#include <Arduino.h>

#define DEBUG

#ifdef DEBUG

template <typename T>
/**
 * Prints a single value to the serial console.
 * @tparam T Value type.
 * @param value Value to print.
 */
void PRINT(const T &value)
{
    Serial.print(value);
}

template <typename T, typename... Args>
/**
 * Prints multiple values to the serial console.
 * @tparam T First value type.
 * @tparam Args Remaining value types.
 * @param first First value to print.
 * @param rest Remaining values to print.
 */
void PRINT(const T &first, const Args &...rest)
{
    Serial.print(first);
    PRINT(rest...);
}

#else

template <typename... Args>
/**
 * No-op print when DEBUG is not enabled.
 * @tparam Args Value types.
 */
void PRINT(const Args &...) {}

#endif

/**
 * Clamps an integer to the inclusive range [low, high].
 * @param value Value to clamp.
 * @param low Lower bound (inclusive).
 * @param high Upper bound (inclusive).
 * @return Clamped value.
 */
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
