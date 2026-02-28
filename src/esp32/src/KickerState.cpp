#include "KickerState.h"
#include <Arduino.h>

void KickerState::initializeChargeAndKickerPins()
{
    pinMode(CHARGE_PIN, OUTPUT);
    pinMode(KICKER_PIN, OUTPUT);
}

void KickerState::turnOffKickerAndStartCharging() {
    turnOffKicker();
    startCharging();
}

void KickerState::waitToCharge() {
    delay(KICKER_CHARGING_TIME);
}

void KickerState::waitToChargeThenStopCharging() {
    waitToCharge();
    stopCharging();
}

void KickerState::turnOffAndChargeKicker() {
    turnOffKickerAndStartCharging();
    waitToChargeThenStopCharging();
}

void KickerState::turnOffAndChargeKickerAndUpdateKickerState() {
    turnOffAndChargeKicker();
    kicker_charged = true;
}

void KickerState::chargeKicker()
{
    turnOffAndChargeKickerAndUpdateKickerState();
}

void KickerState::initializePinsAndChargeKicker()
{
    initializeChargeAndKickerPins();
    chargeKicker();
}

void KickerState::turnOffKicker()
{
    digitalWrite(KICKER_PIN, LOW); // turn OFF kicker
}

void KickerState::startCharging()
{
    digitalWrite(CHARGE_PIN, HIGH);
}

void KickerState::stopCharging()
{
    digitalWrite(CHARGE_PIN, LOW);
}

bool KickerState::kickerIsCharging() {
    return charging_kicker;
}

bool KickerState::kickerIsFullyCharged() {
    unsigned long time_elasped = millis() - this->start_charge_time;
    return time_elasped >= KICKER_CHARGING_TIME;
}

bool KickerState::kickerIsReadyToChargeAgain() {
    unsigned long time_elasped = millis() - this->start_charge_time;
    return time_elasped >= WAIT_BEFORE_CHARGE_AGAIN;
}

bool KickerState::kickerIsKicking() {
    unsigned long time_elasped = millis() - this->start_charge_time;
    return time_elasped >= KICKING_TIME;
}

void KickerState::stopChargingAndUpdateKickerState() {
    stopCharging();
    this->charging_kicker = false;
    this->kicker_charged = true;
}

void KickerState::startChargingAndUpdateKickerState() {
    startCharging();
    this->charging_kicker = true;
    this->start_charge_time = millis();
}

void KickerState::checkAndUpdateKickerStatus() {
    if (kickerIsCharging() && kickerIsFullyCharged()) {
        stopChargingAndUpdateKickerState();
    } else if (kickerIsReadyToChargeAgain()) {
        startChargingAndUpdateKickerState();
    } else if (kickerIsKicking()) {
        turnOffKicker();
    }
}
