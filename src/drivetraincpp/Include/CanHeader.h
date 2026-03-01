#pragma once

#ifdef __cplusplus
extern "C" {
#endif
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_can.h"
#ifdef __cplusplus
}
#endif
#include <stdint.h>

class CanHeader {
    private:

    CAN_TxHeaderTypeDef TxHeader;

    public:
    /**
     * @brief Construct a CAN header wrapper and configure header fields.
     * @param TxHeader Base header to copy into the wrapper.
     * @param DLC Data length code.
     * @param IDE Identifier type (standard/extended).
     * @param RTR Remote transmission request setting.
     * @param StdId Standard identifier to use.
     * @param TransmitGlobalTime Enable or disable global time transmission.
     */
    CanHeader(CAN_TxHeaderTypeDef TxHeader, uint32_t DLC, uint32_t IDE, uint32_t RTR, uint32_t StdId, FunctionalState TransmitGlobalTime);

    /**
     * @brief Get a pointer to the internal CAN Tx header.
     * @return Pointer to the internal header instance.
     */
    CAN_TxHeaderTypeDef* getTxHeaderPointer();
};
