#include "printers.h"

void printStoppingMessage() {
    PRINT("Stopping | ");
}

void printTurningMessage(float angular_speed) {
    PRINT("Turning at ", angular_speed, " rad/s | ");
}

void printDashingMessage(float power, float dir) {
    PRINT("Dashing with ", power, " power in ", dir, " radians | ");
}

void printShortKickingMessage(float power) {
    PRINT("Short Kicking the ball with ", power, " power | ");
}

void printKickingMessage() {
    PRINT("Kicking the ball | ");
}

void printKickerFiredMessage() {
    PRINT(" Kicker fired! | ");
}

void printCatchingMessage() {
    PRINT("Catching the ball | ");
}