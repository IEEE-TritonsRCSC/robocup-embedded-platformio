#pragma once

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
