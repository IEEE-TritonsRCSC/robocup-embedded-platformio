#include "RobotVelocity.h"

void RobotVelocity::setAll(float val) {
    vel_u = val;
    vel_v = val;
    vel_w = val;
}

void RobotVelocity::setVelU(float val) {
    vel_u = val;
}

void RobotVelocity::setVelV(float val) {
    vel_v = val;
}

void RobotVelocity::setVelW(float val) {
    vel_w = val;
}

float RobotVelocity::getVelU() {
    return vel_u;
}
float RobotVelocity::getVelV() {
    return vel_v;
}
float RobotVelocity::getVelW() {
    return vel_w;
}

void RobotVelocity::incrVelU(float val) {
    vel_u += val;
}
void RobotVelocity::incrVelV(float val) {
    vel_v += val;
}

void RobotVelocity::multVelU(float mult) {
    vel_u *= mult;
}
void RobotVelocity::multVelV(float mult) {
    vel_v *= mult;
}