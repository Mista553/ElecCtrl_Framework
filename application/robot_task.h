#pragma once

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

osThreadId_t motorTaskHandle;

const osThreadAttr_t motorTask_attributes = {
    .name = "moterTask",
    .stack_size = 128 * 4,
    .priority = (osPriority_t) osPriorityNormal,
};

const osThreadAttr_t imuTask_attributes = {
    .name = "imuTask",
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

__attribute__((noreturn)) void StartINSTASK(void const *argument)
{
    static float ins_start;
    static float ins_dt;
    INS_Init(); // 确保BMI088被正确初始化.
    // LOGINFO("[freeRTOS] INS Task Start");
    for (;;)
    {
        // 1kHz
        ins_start = DWT_GetTimeline_ms();
        INS_Task();
        ins_dt = DWT_GetTimeline_ms() - ins_start;
        // if (ins_dt > 1)
            // LOGERROR("[freeRTOS] INS Task is being DELAY! dt = [%f]", &ins_dt);
        // VisionSend(); // 解算完成后发送视觉数据,但是当前的实现不太优雅,后续若添加硬件触发需要重新考虑结构的组织
        osDelay(1);
    }
}


__attribute__((noreturn)) void StartMOTORTASK(void *argument)
{
    static float motor_dt;
    static float motor_start;

    for (;;)
    {
        motor_start = DWT_GetTimeline_ms();
        // MotorControlTask();
        motor_dt = DWT_GetTimeline_ms() - motor_start;
        // if (motor_dt > 1)
        //     ;
        osDelay(1);
    }
}