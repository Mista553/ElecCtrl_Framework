#pragma once

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

#include "robot.h"

#include "motor_task.h"
#include "ins_task.h"


osThreadId_t motorTaskHandle;
osThreadId_t insTaskHandle;
osThreadId_t robotTaskHandle;

const osThreadAttr_t motorTask_attributes = {
    .name = "moterTask",
    .stack_size = 128 * 4,
    .priority = (osPriority_t) osPriorityNormal,
};

const osThreadAttr_t insTask_attributes = {
    .name = "insTask",
    .stack_size = 128 * 4,
    .priority = (osPriority_t) osPriorityNormal,
};

const osThreadAttr_t robotTask_attributes = {
    .name = "robotTask",
    .stack_size = 128 * 4,
    .priority = (osPriority_t) osPriorityNormal,
};


void StartMOTORTASK(void *argument);
void StartINSTASK(void *argument);
void StartROBOTTASK(void *argument);

/**
 * @brief 初始化机器人任务,所有持续运行的任务都在这里初始化
 *
 */
void OSTaskInit()
{

    motorTaskHandle = osThreadNew(StartMOTORTASK, NULL, &motorTask_attributes);
    insTaskHandle = osThreadNew(StartINSTASK, NULL, &insTask_attributes);
    robotTaskHandle = osThreadNew(StartROBOTTASK, NULL, &robotTask_attributes);

}

__attribute__((noreturn)) void StartROBOTTASK(void *argument)
{
    // static float robot_dt;
    // static float robot_start;
    // 200Hz-500Hz,若有额外的控制任务如平衡步兵可能需要提升至1kHz
    for (;;)
    {
        // robot_start = DWT_GetTimeline_ms();
        RobotTask();
        // robot_dt = DWT_GetTimeline_ms() - robot_start;
        // if (robot_dt > 5)
        //     LOGERROR("[freeRTOS] ROBOT core Task is being DELAY! dt = [%f]", &robot_dt);
        osDelay(5);
    }
}

__attribute__((noreturn)) void StartMOTORTASK(void *argument)
{
    // static float motor_dt;
    // static float motor_start;

    for (;;)
    {
        // motor_start = DWT_GetTimeline_ms();
        MotorControlTask();
        // motor_dt = DWT_GetTimeline_ms() - motor_start;
        // if (motor_dt > 1)
        //     ;
        osDelay(1);
    }
}

__attribute__((noreturn)) void StartINSTASK(void *argument)
{
    // static float ins_start;
    // static float ins_dt;
    INS_Init(); // 确保BMI088被正确初始化.
    for (;;)
    {
        // 1kHz
        // ins_start = DWT_GetTimeline_ms();
        INS_Task();
        // ins_dt = DWT_GetTimeline_ms() - ins_start;
        // if (ins_dt > 1)
        //     LOGERROR("[freeRTOS] INS Task is being DELAY! dt = [%f]", &ins_dt);
        // VisionSend(); // 解算完成后发送视觉数据,但是当前的实现不太优雅,后续若添加硬件触发需要重新考虑结构的组织
        osDelay(1);
    }
}