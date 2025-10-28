#pragma once 

#include "bsp_can.h"
#include "controller.h"
#include "motor_def.h"

#define VISION_USE_VCP  // 使用虚拟串口发送视觉数据
// #define VISION_USE_UART // 使用串口发送视觉数据

#define ONE_BOARD // 单板
/* 机器人类型定义,可设参数为Robot_Type_e枚举里面参数  */
#define ROBOT_ID INFANTRY_ROBOT_3

#define RC_TO_YAW_ANGLE 0.002f    // 遥控器转yaw增量阈值
#define RC_TO_PITCH_ANGLE 0.001f  // 遥控器转pitch增量阈值

// #define _IS_IMU_ROLL    // 是否使用IMU的roll角作为pitch角(由于不常修改，所有作为宏)

// 电机方向
typedef enum
{
    MOTOR_LF = 0,
    MOTOR_RF,
    MOTOR_LB,
    MOTOR_RB,
    MOTOR_UP_LF,
    MOTOR_UP_RF,
    MOTOR_UP_LB,
    MOTOR_UP_RB
} Motor_Turn_e;

// 机器人底盘类型
typedef enum
{
    MECANUM_WHEEL = 0,
    OMNI_WHEEL,
    STEER_WHEEL
} Wheel_Type_e;

// 底盘轮组参数
typedef struct
{
    float center_gimbal_offset_x;
    float center_gimbal_offset_y;

    float wheel_base;
    float track_width;
    float radius_wheel;
    
    float reduction_ratio_wheel;
} Wheel_Measure_s;

typedef struct
{
    Wheel_Type_e wheel_type;
    Wheel_Measure_s wheel_measure;

    Motor_Init_Config_s chassis_motor_config;
    PID_Init_Config_s chassis_follow_gimbal_PID;

    uint8_t chassis_motor_id[8];    
} Chassis_Config_s;

// // 机器人云台类型
// typedef enum
// {
//     SINGLE_GIMBAL = 0,
//     MINI_GIMBAL,
//     DUAL_GIMBAL,
// } Gimbal_Type_e;

// // 云台归中参数
// typedef struct
// {
//     float mini_yaw_offset;
//     float yaw_offset;
//     float pitch_max_angle, pitch_min_angle;
// } Gimbal_Measure_s;

// typedef struct 
// {
//     Gimbal_Type_e gimbal_type;
//     Gimbal_Measure_s gimbal_offset;
//     Motor_Init_Config_s yaw_motor_config;
//     Motor_Init_Config_s mini_yaw_motor_config;
//     Motor_Init_Config_s pitch_motor_config;
// } Gimbal_Config_s;

// // 机器人发射类型
// typedef enum
// {
//     DUAL_SHOOT = 0,
//     THREE_SHOOT,
//     FOUR_SHOOT,
// } Shoot_Type_e;

// typedef struct 
// {
//     Shoot_Type_e shoot_type;
//     Motor_Init_Config_s friction_motor_config;
//     Motor_Init_Config_s loader_motor_config;

//     uint8_t friction_motor_id[4];    
//     Motor_Reverse_Flag_e friction_motor_reverse_flag[4];
// } Shoot_Config_s;


// 机器人参数结构体
typedef struct
{
    Chassis_Config_s chassis_param;
    // Gimbal_Config_s gimbal_param;
    // Shoot_Config_s shoot_param;
} Robot_Config_s;

// 机器人类型
typedef enum
{
    HERO_ROBOT = 1,
    ENGINEER_ROBOT,
    INFANTRY_ROBOT_3,
    INFANTRY_ROBOT_4,
    INFANTRY_ROBOT_5,
    AERIAL_ROBOT,
    SENTINEL_ROBOT,
    DART_ROBOT,
} Robot_Type_e;