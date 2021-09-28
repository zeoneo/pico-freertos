#include "FreeRTOS.h"
#include "task.h"

void vApplicationMallocFailedHook(void)
{
    // taskDISABLE_INTERRUPTS();
    // TU_ASSERT(false, );
}

void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
    (void)pxTask;
    (void)pcTaskName;

    // taskDISABLE_INTERRUPTS();
    // TU_ASSERT(false, );
}