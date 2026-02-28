#include "stm32f4xx_hal.h"

extern "C" HAL_StatusTypeDef HAL_InitTick(uint32_t /*TickPriority*/) {
  // Stub timebase init for CMake build. Implement TIM-based tick if needed.
  return HAL_OK;
}

extern "C" void HAL_SuspendTick(void) {
  // Stub
}

extern "C" void HAL_ResumeTick(void) {
  // Stub
}

