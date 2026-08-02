#include "FreeRTOS.h"
#include "task.h"

volatile int task1_counter = 0;
volatile int task2_counter = 0;

// Task 1: Increments a counter every 10 ticks
void Task1(void *pvParameters) {
    while(1) {
        task1_counter++;
        vTaskDelay(pdMS_TO_TICKS(10)); 
    }
}

// Task 2: Increments a counter every 20 ticks
void Task2(void *pvParameters) {
    while(1) {
        task2_counter++;
        vTaskDelay(pdMS_TO_TICKS(20)); 
    }
}

void main(void) {
    // Create the tasks
    xTaskCreate(Task1, "Task1", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(Task2, "Task2", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    // Give control to FreeRTOS
    vTaskStartScheduler();

    // The code should never reach here unless there is insufficient RAM
    while(1);
}

void Reset_Handler(void) {
    main();
}

// A catch-all for any unexpected hardware faults
void Default_Handler(void) {
    while(1);
}

// FreeRTOS Handlers (Mapped in FreeRTOSConfig.h)
extern void SVC_Handler(void);
extern void PendSV_Handler(void);
extern void SysTick_Handler(void);

// The Full Cortex-M3 Vector Table
__attribute__((section(".isr_vector")))
void (*const vector_table[])(void) = {
    (void (*)(void))0x20010000, // 0: Top of Stack
    Reset_Handler,              // 1: Reset Handler
    Default_Handler,            // 2: NMI
    Default_Handler,            // 3: Hard Fault
    Default_Handler,            // 4: MemManage
    Default_Handler,            // 5: BusFault
    Default_Handler,            // 6: UsageFault
    0, 0, 0, 0,                 // 7-10: Reserved
    SVC_Handler,                // 11: SVCall (FreeRTOS API calls)
    Default_Handler,            // 12: Debug Monitor
    0,                          // 13: Reserved
    PendSV_Handler,             // 14: PendSV (FreeRTOS Context Switch)
    SysTick_Handler             // 15: SysTick (FreeRTOS Timebase)
};