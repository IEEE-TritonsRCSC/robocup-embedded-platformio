#pragma once


class PID_Outputs
{
private:
    float pout, iout, dout;

public:
    /**
     * @brief Construct PID output components with explicit values.
     * @param pout Proportional output term.
     * @param iout Integral output term.
     * @param dout Derivative output term.
     */
    PID_Outputs(float pout, float iout, float dout) : pout(pout), iout(iout), dout(dout) {}
    /**
     * @brief Construct PID outputs with default values.
     */
    PID_Outputs();

    /**
     * @brief Set the proportional output term.
     * @param p Proportional output term.
     */
    void setPout(float p);
    /**
     * @brief Set the integral output term.
     * @param i Integral output term.
     */
    void setIout(float i);
    /**
     * @brief Set the derivative output term.
     * @param d Derivative output term.
     */
    void setDout(float d);

    /**
     * @brief Get the proportional output term.
     * @return Proportional output term.
     */
    float getPout();
    /**
     * @brief Get the integral output term.
     * @return Integral output term.
     */
    float getIout();
    /**
     * @brief Get the derivative output term.
     * @return Derivative output term.
     */
    float getDout();

    /**
     * @brief Get the sum of all output terms.
     * @return Sum of proportional, integral, and derivative terms.
     */
    float getOutputSum();
};
