#include "stm32f4xx_hal.h"

extern "C" void NMI_Handler(void) {
  while (1) {}
}

extern "C" void HardFault_Handler(void) {
  while (1) {}
}

extern "C" void MemManage_Handler(void) {
  while (1) {}
}

extern "C" void BusFault_Handler(void) {
  while (1) {}
}

extern "C" void UsageFault_Handler(void) {
  while (1) {}
}

extern "C" void SVC_Handler(void) {}

extern "C" void DebugMon_Handler(void) {}

extern "C" void PendSV_Handler(void) {}

extern "C" void SysTick_Handler(void) {
  HAL_IncTick();
}

