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
 * Prints a stop command message.
 */
void printStoppingMessage();
/**
 * Prints a turn command message.
 * @param angular_speed Turn angular speed.
 */
void printTurningMessage(float angular_speed);
/**
 * Prints a dash command message.
 * @param power Dash power.
 * @param dir Dash direction.
 */
void printDashingMessage(float power, float dir);
/**
 * Prints a short kick command message.
 * @param power Kick power.
 */
void printShortKickingMessage(float power);
/**
 * Prints a kick command message.
 */
void printKickingMessage();
/**
 * Prints a kicker fired message.
 */
void printKickerFiredMessage();
/**
 * Prints a catch command message.
 */
void printCatchingMessage();
