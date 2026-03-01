#pragma once
class RobotVelocity {
private:
    float vel_u;
    float vel_v;
    float vel_w;

public:
    /**
     * Initializes all velocity components to zero.
     */
    RobotVelocity() : vel_u(0.0f), vel_v(0.0f), vel_w(0.0f) {}

    /**
     * Sets all velocity components to the same value.
     * @param val Value to assign to u, v, and w.
     */
    void setAll(float val);
    /**
     * Sets the u (x) velocity component.
     * @param val Value to assign to u.
     */
    void setVelU(float val);
    /**
     * Sets the v (y) velocity component.
     * @param val Value to assign to v.
     */
    void setVelV(float val);
    /**
     * Sets the w (angular) velocity component.
     * @param val Value to assign to w.
     */
    void setVelW(float val);

    /**
     * Gets the u (x) velocity component.
     * @return Current u component.
     */
    float getVelU();
    /**
     * Gets the v (y) velocity component.
     * @return Current v component.
     */
    float getVelV();
    /**
     * Gets the w (angular) velocity component.
     * @return Current w component.
     */
    float getVelW();

    /**
     * Increments the u (x) velocity component.
     * @param val Amount to add to u.
     */
    void incrVelU(float val);
    /**
     * Increments the v (y) velocity component.
     * @param val Amount to add to v.
     */
    void incrVelV(float val);

    /**
     * Multiplies the u (x) velocity component by a factor.
     * @param mult Multiplicative factor.
     */
    void multVelU(float mult);
    /**
     * Multiplies the v (y) velocity component by a factor.
     * @param mult Multiplicative factor.
     */
    void multVelV(float mult);
};
