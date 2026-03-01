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

    /**
     * Initializes kicker state flags and timers.
     */
    KickerState() : kicker_charged(false), charging_kicker(false), start_charge_time(0), last_kick_time(0) {}
    
    /**
     * Configures GPIO pins for the charge circuit and kicker output.
     */
    void initializeChargeAndKickerPins();
    /**
     * Initializes pins and begins charging the kicker.
     */
    void initializePinsAndChargeKicker();

    /**
     * Waits for the charging interval to elapse.
     */
    void waitToCharge();
    /**
     * Waits for the charging interval and stops charging afterwards.
     */
    void waitToChargeThenStopCharging();

    /**
     * Turns off the kicker output.
     */
    void turnOffKicker();
    /**
     * Starts charging the kicker.
     */
    void turnOnKicker();
    void startCharging();
    /**
     * Stops charging the kicker.
     */
    void stopCharging();

    /**
     * Starts a kicker charge cycle.
     */
    void chargeKicker();
    /**
     * Turns off the kicker and starts charging.
     */
    void turnOffKickerAndStartCharging();
    /**
     * Turns off the kicker and initiates charging.
     */
    void turnOffAndChargeKicker();

    /**
     * Turns off the kicker, starts charging, and updates internal state.
     */
    void turnOffAndChargeKickerAndUpdateKickerState();
    /**
     * Checks timers and updates kicker status flags.
     */
    void checkAndUpdateKickerStatus();
    /**
     * Starts charging and updates internal state.
     */
    void startChargingAndUpdateKickerState();
    /**
     * Stops charging and updates internal state.
     */
    void stopChargingAndUpdateKickerState();

    /**
     * Checks whether the kicker is currently charging.
     * @return True if charging, otherwise false.
     */
    bool kickerIsCharging();
    /**
     * Checks whether the kicker is fully charged.
     * @return True if fully charged, otherwise false.
     */
    bool kickerIsFullyCharged();
    /**
     * Checks whether the kicker is ready to charge again.
     * @return True if ready to charge again, otherwise false.
     */
    bool kickerIsReadyToChargeAgain();
    /**
     * Checks whether the kicker is currently kicking.
     * @return True if kicking, otherwise false.
     */
    bool kickerIsKicking();


};
