#pragma once


#define KICKER_PIN 5
#define CHARGE_PIN 18
#define KICKER_CHARGING_TIME 100      // ms
#define KICKING_TIME 500              // ms
#define WAIT_BEFORE_CHARGE_AGAIN 5000 // 5 seconds

class KickerState {
    public:
    bool kicker_charged;
    bool charging_kicker;
    unsigned long start_charge_time;
    unsigned long last_kick_time;

    KickerState() : kicker_charged(false), charging_kicker(false), start_charge_time(0), last_kick_time(0) {}
    
    void initializeChargeAndKickerPins();
    void initializePinsAndChargeKicker();

    void waitToCharge();
    void waitToChargeThenStopCharging();

    void turnOffKicker();
    void turnOnKicker();
    void startCharging();
    void stopCharging();

    void chargeKicker();
    void turnOffKickerAndStartCharging();
    void turnOffAndChargeKicker();

    void turnOffAndChargeKickerAndUpdateKickerState();
    void checkAndUpdateKickerStatus();
    void startChargingAndUpdateKickerState();
    void stopChargingAndUpdateKickerState();

    bool kickerIsCharging();
    bool kickerIsFullyCharged();
    bool kickerIsReadyToChargeAgain();
    bool kickerIsKicking();


};