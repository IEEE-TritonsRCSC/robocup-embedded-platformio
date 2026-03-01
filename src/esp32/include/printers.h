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

void printStoppingMessage();
void printTurningMessage(float angular_speed);
void printDashingMessage(float power, float dir);
void printShortKickingMessage(float power);
void printKickingMessage();
void printKickerFiredMessage();
void printCatchingMessage();