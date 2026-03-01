#pragma once

#include "PID_Outputs.h"
#include "PID_Gains.h"
#include "stdint.h"

class PID_Data
{
private:
    float target;
    float lastNoneZeroTarget;

    float measure;
    float error;
    float lastError;
    float integral;

    float d_buf[3];
    float error_buf[3];

    float output;

    float maxOutput;
    float integralLimit;
    float deadBand;

    uint32_t thisTime;
    uint32_t lastTime;
    uint8_t dTtime;

    PID_Gains gains;
    PID_Outputs outputs;

public:
    /**
     * @brief Construct PID data with limits, target, and gains.
     * @param maxOutput Maximum allowed output magnitude.
     * @param integralLimit Maximum absolute integral term.
     * @param deadBand Error deadband threshold.
     * @param target Initial target setpoint.
     * @param gains PID gains to apply.
     */
    PID_Data(float maxOutput, float integralLimit, float deadBand, float target, PID_Gains gains);

    /**
     * @brief Set the target setpoint.
     * @param target Target setpoint.
     */
    void setTarget(float target);
    /**
     * @brief Set the last non-zero target setpoint.
     * @param lastNoneZeroTarget Last non-zero target.
     */
    void setLastNoneZeroTarget(float lastNoneZeroTarget);
    /**
     * @brief Set the current measurement.
     * @param measure Current measured value.
     */
    void setMeasure(float measure);
    /**
     * @brief Set the current error value.
     * @param error Current error.
     */
    void setError(float error);
    /**
     * @brief Set the previous error value.
     * @param lastError Previous error.
     */
    void setLastError(float lastError);
    /**
     * @brief Set the integral accumulator.
     * @param integral Integral accumulator.
     */
    void setIntegral(float integral);
    /**
     * @brief Set the derivative buffer values.
     * @param d_buf Array of 3 derivative values.
     */
    void setD_buf(float d_buf[3]);
    /**
     * @brief Set the error buffer values.
     * @param error_buf Array of 3 error values.
     */
    void setError_buf(float error_buf[3]);
    /**
     * @brief Set the current output value.
     * @param output Output value.
     */
    void setOutput(float output);
    /**
     * @brief Set the maximum output magnitude.
     * @param maxOutput Maximum output magnitude.
     */
    void setMaxOutput(float maxOutput);
    /**
     * @brief Set the integral limit.
     * @param integralLimit Maximum absolute integral term.
     */
    void setIntegralLimit(float integralLimit);
    /**
     * @brief Set the error deadband threshold.
     * @param deadBand Deadband threshold.
     */
    void setDeadBand(float deadBand);
    /**
     * @brief Set the current timestamp.
     * @param thisTime Current time tick.
     */
    void setThisTime(uint32_t thisTime);
    /**
     * @brief Set the previous timestamp.
     * @param lastTime Previous time tick.
     */
    void setLastTime(uint32_t lastTime);
    /**
     * @brief Set the delta time in ticks.
     * @param dTime Delta time in ticks.
     */
    void setDTime(uint32_t dTime);
    /**
     * @brief Set PID gains.
     * @param gains PID gains to apply.
     */
    void setGains(PID_Gains gains);
    /**
     * @brief Set PID output components.
     * @param outputs PID output components.
     */
    void setOutputs(PID_Outputs outputs);

    // getters
    /**
     * @brief Get the current target setpoint.
     * @return Target setpoint.
     */
    float getTarget() const;
    /**
     * @brief Get the last non-zero target setpoint.
     * @return Last non-zero target.
     */
    float getLastNoneZeroTarget() const;
    /**
     * @brief Get the current measurement.
     * @return Current measured value.
     */
    float getMeasure() const;
    /**
     * @brief Get the current error value.
     * @return Current error.
     */
    float getError() const;
    /**
     * @brief Get the previous error value.
     * @return Previous error.
     */
    float getLastError() const;
    /**
     * @brief Get the integral accumulator.
     * @return Integral accumulator.
     */
    float getIntegral() const;
    /**
     * @brief Get the derivative buffer values.
     * @return Pointer to derivative buffer array.
     */
    const float* getD_buf() const;
    /**
     * @brief Get the error buffer values.
     * @return Pointer to error buffer array.
     */
    const float* getError_buf() const;
    /**
     * @brief Get the current output value.
     * @return Output value.
     */
    float getOutput() const;
    /**
     * @brief Get the maximum output magnitude.
     * @return Maximum output magnitude.
     */
    float getMaxOutput() const;
    /**
     * @brief Get the integral limit.
     * @return Maximum absolute integral term.
     */
    float getIntegralLimit() const;
    /**
     * @brief Get the error deadband threshold.
     * @return Deadband threshold.
     */
    float getDeadBand() const;
    /**
     * @brief Get the current timestamp.
     * @return Current time tick.
     */
    uint32_t getThisTime() const;
    /**
     * @brief Get the previous timestamp.
     * @return Previous time tick.
     */
    uint32_t getLastTime() const;
    /**
     * @brief Get the delta time in ticks.
     * @return Delta time in ticks.
     */
    uint8_t getDTime() const;
    /**
     * @brief Get the PID gains.
     * @return PID gains reference.
     */
    const PID_Gains& getGains() const;
    /**
     * @brief Get the PID output components.
     * @return PID outputs reference.
     */
    const PID_Outputs& getOutputs() const;

    /**
     * Accumulate integral term and clamp to integral limits to prevent windup.
     */
    void preventIntegralWindup();
    /**
     * Clamp the overall output to the configured max output bounds.
     */
    void clampOutput();
    /**
     * Shift and update the error history buffer from target and measure.
     */
    void updateErrorBuf();
    /**
     * Shift and update the derivative buffer using the error history.
     */
    void updateDBuf();
    /**
     * Compute and store proportional output from current error.
     */
    void updateProportionalOutput();
    /**
     * Compute and store integral output from current integral accumulator.
     */
    void updateIntegralOutput();
    /**
     * Compute and store derivative output from current error delta.
     */
    void updateDerivativeOutput();
    /**
     * Compute and store the sum of P, I, and D outputs as the current output.
     */
    void updateOutputSum();
    /**
     * Compute and store proportional output using error delta.
     */
    void updateProportionalOutputFromErrorDelta();
    /**
     * Compute and store integral output using current error.
     */
    void updateIntegralOutputFromError();
    /**
     * Compute and store derivative output using the derivative buffer.
     */
    void updateDerivativeOutputFromDBuf();
    /**
     * Add the sum of output components to the current output accumulator.
     */
    void addOutputSum();
    /**
     * Update error from target and current measurement.
     */
    void updateErrorFromTargetAndMeasure();
    /**
     * Store current error as last error.
     */
    void updateLastError();
    /**
     * Run the direct PID update (P/I/D from current error).
     */
    void runDirectPidStep();
    /**
     * Run the incremental PID update (error buffer, d buffer, incremental sum).
     */
    void runIncrementalPidStep();
    /**
     * Run one PID update step and return the computed output.
     * @param measure Current measured value.
     * @return Computed PID output.
     */
    float pidCalculate(float measure);
};
