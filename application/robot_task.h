#pragma once

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

#include "motor_task.h"

osThreadId_t motorTaskHandle;

const osThreadAttr_t motorTask_attributes = {
    .name = "moterTask",
    .stack_size = 128 * 4,
    .priority = (osPriority_t) osPriorityNormal,
};

void StartMOTORTASK(void *argument);

/**
 * @brief 初始化机器人任务,所有持续运行的任务都在这里初始化
 *
 */
void OSTaskInit()
{

    motorTaskHandle = osThreadNew(StartMOTORTASK, NULL, &motorTask_attributes);

}


__attribute__((noreturn)) void StartMOTORTASK(void *argument)
{
    static float motor_dt;
    static float motor_start;

    for (;;)
    {
        motor_start = DWT_GetTimeline_ms();
        MotorControlTask();
        motor_dt = DWT_GetTimeline_ms() - motor_start;
        if (motor_dt > 1)
            ;
        osDelay(1);
    }
}