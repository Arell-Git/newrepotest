/*!
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* @file EnduroSat_Mock.c
* @brief Dummy implementations of EnduroSat functions
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* @author            Elijah B.
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include "MCU_Init.h"
#include "stm32f4xx.h"

__WEAK void AntUHF_Init(void) { return; }

__WEAK void AntUHF_Handler(void) { return; }

__WEAK uint32_t S_BAND_TRNSM_GetBaudrate(void) { return 0; }

__WEAK uint32_t X_BAND_TRNSM_GetBaudrate(void) { return 0; }

__WEAK void TaskMonitor_Init(void) { return; }

__WEAK void TaskMonitor_IamAlive(int task) { return; }

__WEAK void TaskMonitor_TaskInitialized(int task) { return; }

/* Always return 1 to signal that all tasks are initialized and ready */
uint8_t TaskMonitor_CheckTasksInit(void) { return 1; }

typedef enum{
    TASK_MONITOR_SW_RESET,
    TASK_MONITOR_WD_RESET,
    TASK_MONITOR_RESET_NUMBER
}TASK_MONITOR_resetEnum;

/* This function needs a legitimate implementation because it is invoked
 * in the fault handlers defined by EnduroSat in the precompiled
 * stm32f4xx_it file, and potentially with either argument.
 * The implementation of this function was deduced by looking at the disassembly
 * of the original EnduroSat version.
 */
__WEAK void TaskMonitor_ImmediatReset(TASK_MONITOR_resetEnum ResetType)
{
	switch (ResetType)
	{
	case TASK_MONITOR_SW_RESET:
		HAL_NVIC_SystemReset();
	case TASK_MONITOR_WD_RESET:
		HAL_WWDG_Refresh(&hwwdg);
	case TASK_MONITOR_RESET_NUMBER:
		return;
	}
}

