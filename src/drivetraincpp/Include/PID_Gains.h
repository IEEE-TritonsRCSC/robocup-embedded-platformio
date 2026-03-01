#pragma once


class PID_Gains
{
private:
    float kp, ki, kd;

public:
    /**
     * @brief Construct PID gains with explicit values.
     * @param kp Proportional gain.
     * @param ki Integral gain.
     * @param kd Derivative gain.
     */
    PID_Gains(float kp, float ki, float kd) : kp(kp), ki(ki), kd(kd) {}
    /**
     * @brief Construct PID gains from an array.
     * @param gains_array Array of gains in the order {kp, ki, kd}.
     */
    PID_Gains(float *gains_array);
    /**
     * @brief Construct PID gains with default values.
     */
    PID_Gains();

    /**
     * @brief Set the proportional gain.
     * @param p Proportional gain.
     */
    void setP(float p);
    /**
     * @brief Set the integral gain.
     * @param i Integral gain.
     */
    void setI(float i);
    /**
     * @brief Set the derivative gain.
     * @param d Derivative gain.
     */
    void setD(float d);

    /**
     * @brief Get the proportional gain.
     * @return Proportional gain.
     */
    float getP();
    /**
     * @brief Get the integral gain.
     * @return Integral gain.
     */
    float getI();
    /**
     * @brief Get the derivative gain.
     * @return Derivative gain.
     */
    float getD();
};
