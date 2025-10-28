/**
 * @file robot_def.h
 * @author NeoZeng neozng1@hnu.edu.cn
 * @author Even
 * @version 0.1
 * @date 2022-12-02
 *
 * @copyright Copyright (c) HNU YueLu EC 2022 all rights reserved
 *
 */
#pragma once // 可以用#pragma once代替#ifndef ROBOT_DEF_H(header guard)
#ifndef ROBOT_DEF_H
#define ROBOT_DEF_H

#include "ins_task.h"
<<<<<<< HEAD
#include "master_process.h"
#include "stdint.h"

/* 开发板类型定义,烧录时注意不要弄错对应功能;修改定义后需要重新编译,只能存在一个定义! */
#define ONE_BOARD // 单板控制整车
// #define CHASSIS_BOARD //底盘板
// #define GIMBAL_BOARD  //云台板

#define VISION_USE_VCP  // 使用虚拟串口发送视觉数据
// #define VISION_USE_UART // 使用串口发送视觉数据

/* 机器人重要参数定义,注意根据不同机器人进行修改,浮点数需要以.0或f结尾,无符号以u结尾 */
// 云台参数
#define YAW_CHASSIS_ALIGN_ECD 2711  // 云台和底盘对齐指向相同方向时的电机编码器值,若对云台有机械改动需要修改
#define YAW_ECD_GREATER_THAN_4096 0 // ALIGN_ECD值是否大于4096,是为1,否为0;用于计算云台偏转角度
#define PITCH_HORIZON_ECD 3412      // 云台处于水平位置时编码器值,若对云台有机械改动需要修改
#define PITCH_MAX_ANGLE 0           // 云台竖直方向最大角度 (注意反馈如果是陀螺仪，则填写陀螺仪的角度)
#define PITCH_MIN_ANGLE 0           // 云台竖直方向最小角度 (注意反馈如果是陀螺仪，则填写陀螺仪的角度)
// 发射参数
#define ONE_BULLET_DELTA_ANGLE 36    // 发射一发弹丸拨盘转动的距离,由机械设计图纸给出
#define REDUCTION_RATIO_LOADER 36.0f // 2006拨盘电机的减速比,英雄需要修改为3508的19.0f
#define NUM_PER_CIRCLE 10            // 拨盘一圈的装载量
// 机器人底盘修改的参数,单位为mm(毫米)
#define WHEEL_BASE 378.58              // 纵向轴距(前进后退方向)
#define TRACK_WIDTH 360.88             // 横向轮距(左右平移方向)
#define CENTER_GIMBAL_OFFSET_X 0    // 云台旋转中心距底盘几何中心的距离,前后方向,云台位于正中心时默认设为0
#define CENTER_GIMBAL_OFFSET_Y 0    // 云台旋转中心距底盘几何中心的距离,左右方向,云台位于正中心时默认设为0
#define RADIUS_WHEEL 76             // 轮子半径
#define REDUCTION_RATIO_WHEEL 19.0f // 电机减速比,因为编码器量测的是转子的速度而不是输出轴的速度故需进行转换

#define GYRO2GIMBAL_DIR_YAW 1   // 陀螺仪数据相较于云台的yaw的方向,1为相同,-1为相反
#define GYRO2GIMBAL_DIR_PITCH 1 // 陀螺仪数据相较于云台的pitch的方向,1为相同,-1为相反
#define GYRO2GIMBAL_DIR_ROLL 1  // 陀螺仪数据相较于云台的roll的方向,1为相同,-1为相反

// 检查是否出现主控板定义冲突,只允许一个开发板定义存在,否则编译会自动报错
#if (defined(ONE_BOARD) && defined(CHASSIS_BOARD)) || \
    (defined(ONE_BOARD) && defined(GIMBAL_BOARD)) ||  \
    (defined(CHASSIS_BOARD) && defined(GIMBAL_BOARD))
#error Conflict board definition! You can only define one board type.
#endif
=======
// #include "master_process.h"
#include "stdint.h"

#include "config.h"

// /* 开发板类型定义,无人机和飞镖使用云台板,其他兵种使用单板(待加入平衡) */
// #if (!defined(DART_ROBOT) && !defined(AERIAL_ROBOT))
//     #define ONE_BOARD 
// #endif
// // #define CHASSIS_BOARD //底盘板
// #if (defined(DART_ROBOT) || defined(AERIAL_ROBOT))
//     #define GIMBAL_BOARD  
// #endif

// // 检查是否存在该机器人ID,不存在则编译会自动报错
// #if (!defined(INFANTRY_ROBOT) && !defined(SENTINEL_ROBOT)) && \
//     (!defined(HERO_ROBOT) && !defined(ENGINEER_ROBOT)) && \
//     (!defined(AERIAL_ROBOT) && !defined(DART_ROBOT))
// #error None Robot ID definition! You can only define ID from 0 to 5.
// #endif

// // 检查是否出现底盘类型冲突,只允许一个底盘类型定义存在,否则编译会自动报错
// #if (defined(MECANUM_WHEEL) && defined(OMIN_WHEEL)) || \
//     (defined(MECANUM_WHEEL) && defined(STEER_WHEEL)) ||  \
//     (defined(OMIN_WHEEL) && defined(STEER_WHEEL))
// #error Conflict chassis wheel definition! You can only define one chassis type.
// #endif
>>>>>>> 7efda366d82622581d8242e2fe220b83f2f9c878

#pragma pack(1) // 压缩结构体,取消字节对齐,下面的数据都可能被传输
/* -------------------------基本控制模式和数据类型定义-------------------------*/
/**
 * @brief 这些枚举类型和结构体会作为CMD控制数据和各应用的反馈数据的一部分
 *
 */
// 机器人状态
typedef enum
{
    ROBOT_STOP = 0,
    ROBOT_READY,
} Robot_Status_e;

// 应用状态
typedef enum
{
    APP_OFFLINE = 0,
    APP_ONLINE,
    APP_ERROR,
} App_Status_e;

// 底盘模式设置
/**
 * @brief 后续考虑修改为云台跟随底盘,而不是让底盘去追云台,云台的惯量比底盘小.
 *
 */
typedef enum
{
    CHASSIS_ZERO_FORCE = 0,    // 电流零输入
    CHASSIS_ROTATE,            // 小陀螺模式
    CHASSIS_NO_FOLLOW,         // 不跟随，允许全向平移
    CHASSIS_FOLLOW_GIMBAL_YAW, // 跟随模式，底盘叠加角度环控制
} chassis_mode_e;
<<<<<<< HEAD

// 云台模式设置
typedef enum
{
    GIMBAL_ZERO_FORCE = 0, // 电流零输入
    GIMBAL_FREE_MODE,      // 云台自由运动模式,即与底盘分离(底盘此时应为NO_FOLLOW)反馈值为电机total_angle;似乎可以改为全部用IMU数据?
    GIMBAL_GYRO_MODE,      // 云台陀螺仪反馈模式,反馈值为陀螺仪pitch,total_yaw_angle,底盘可以为小陀螺和跟随模式
} gimbal_mode_e;
=======
// 底盘电机状态
typedef enum
{
    CHASSIS_MOTOR_OFFLINE = 0,    
    CHASSIS_MOTOR_ONLINE,
} chassis_motor_state_e;
// 底盘电机离线类型
typedef enum
{
    NONE_CHASSIS_TYPE = 0,    
    LF_MOTOR,
    RF_MOTOR,
    LB_MOTOR,
    RB_MOTOR,
} chassis_offline_type_e;

//云台模式设置
typedef enum
{
    GIMBAL_ZERO_FORCE = 0, // 电流零输入
    GIMBAL_GYRO_MODE,      // 云台陀螺仪反馈模式,反馈值为陀螺仪pitch,total_yaw_angle,底盘可以为小陀螺和跟随模式
} gimbal_mode_e;
// 云台电机状态
typedef enum
{
    GIMBAL_MOTOR_OFFLINE = 0,
    GIMBAL_MOTOR_ONLINE,
} gimbal_motor_state_e;
>>>>>>> 7efda366d82622581d8242e2fe220b83f2f9c878

// 发射模式设置
typedef enum
{
<<<<<<< HEAD
    SHOOT_OFF = 0,
=======
    SHOOT_ZERO_FORCE = 0,
    SHOOT_OFF,
>>>>>>> 7efda366d82622581d8242e2fe220b83f2f9c878
    SHOOT_ON,
} shoot_mode_e;
typedef enum
{
    FRICTION_OFF = 0, // 摩擦轮关闭
    FRICTION_ON,      // 摩擦轮开启
} friction_mode_e;

typedef enum
{
    LID_OPEN = 0, // 弹舱盖打开
    LID_CLOSE,    // 弹舱盖关闭
} lid_mode_e;

typedef enum
{
    LOAD_STOP = 0,  // 停止发射
    LOAD_REVERSE,   // 反转
    LOAD_1_BULLET,  // 单发
    LOAD_3_BULLET,  // 三发
    LOAD_BURSTFIRE, // 连发
} loader_mode_e;

<<<<<<< HEAD
=======

>>>>>>> 7efda366d82622581d8242e2fe220b83f2f9c878
// 功率限制,从裁判系统获取,是否有必要保留?
typedef struct
{ // 功率控制
    float chassis_power_mx;
} Chassis_Power_Data_s;

<<<<<<< HEAD
=======

>>>>>>> 7efda366d82622581d8242e2fe220b83f2f9c878
/* ----------------CMD应用发布的控制数据,应当由gimbal/chassis/shoot订阅---------------- */
/**
 * @brief 对于双板情况,遥控器和pc在云台,裁判系统在底盘
 *
 */
// cmd发布的底盘控制数据,由chassis订阅
typedef struct
{
    // 控制部分
    float vx;           // 前进方向速度
    float vy;           // 横移方向速度
    float wz;           // 旋转速度
    float offset_angle; // 底盘和归中位置的夹角
<<<<<<< HEAD
=======
    float power_limit;  // 功率限制
>>>>>>> 7efda366d82622581d8242e2fe220b83f2f9c878
    chassis_mode_e chassis_mode;
    int chassis_speed_buff;
    // UI部分
    //  ...

} Chassis_Ctrl_Cmd_s;

<<<<<<< HEAD
// cmd发布的云台控制数据,由gimbal订阅
typedef struct
{ // 云台角度控制
    float yaw;
    float pitch;
    float chassis_rotate_wz;

    gimbal_mode_e gimbal_mode;
} Gimbal_Ctrl_Cmd_s;

// cmd发布的发射控制数据,由shoot订阅
typedef struct
{
    shoot_mode_e shoot_mode;
    loader_mode_e load_mode;
    lid_mode_e lid_mode;
    friction_mode_e friction_mode;
    Bullet_Speed_e bullet_speed; // 弹速枚举
    uint8_t rest_heat;
    float shoot_rate; // 连续发射的射频,unit per s,发/秒
} Shoot_Ctrl_Cmd_s;
=======
// // cmd发布的云台控制数据,由gimbal订阅
// typedef struct
// { // 云台角度控制
//     float mini_yaw;
//     float yaw;
//     float pitch;
//     float chassis_rotate_wz;

//     gimbal_mode_e gimbal_mode;
// } Gimbal_Ctrl_Cmd_s;

// // cmd发布的发射控制数据,由shoot订阅
// typedef struct
// {
//     shoot_mode_e shoot_mode;
//     loader_mode_e load_mode;
//     lid_mode_e lid_mode;
//     friction_mode_e friction_mode;
//     Bullet_Speed_e bullet_speed; // 弹速枚举
//     uint8_t rest_heat;
//     float shoot_rate; // 连续发射的射频,unit per s,发/秒
// } Shoot_Ctrl_Cmd_s;
>>>>>>> 7efda366d82622581d8242e2fe220b83f2f9c878

/* ----------------gimbal/shoot/chassis发布的反馈数据----------------*/
/**
 * @brief 由cmd订阅,其他应用也可以根据需要获取.
 *
 */

typedef struct
{
#if defined(CHASSIS_BOARD) || defined(GIMBAL_BOARD) // 非单板的时候底盘还将imu数据回传(若有必要)
    // attitude_t chassis_imu_data;
#endif
<<<<<<< HEAD
    // 后续增加底盘的真实速度
    // float real_vx;
    // float real_vy;
    // float real_wz;

    uint8_t rest_heat;           // 剩余枪口热量
    Bullet_Speed_e bullet_speed; // 弹速限制
    Enemy_Color_e enemy_color;   // 0 for blue, 1 for red

} Chassis_Upload_Data_s;


typedef struct
{
    attitude_t gimbal_imu_data;
    uint16_t yaw_motor_single_round_angle;
} Gimbal_Upload_Data_s;

typedef struct
{
    // code to go here
    // ...
} Shoot_Upload_Data_s;

#pragma pack() // 开启字节对齐,结束前面的#pragma pack(1)

=======
    // 后底盘的真实速度
    float real_vx;
    float real_vy;
    float real_wz;
    // 底盘电机离线数量
    uint8_t motor_offline_count;       
    // 底盘电机状态
    chassis_motor_state_e motor_state;
   
} Chassis_Upload_Data_s;


// typedef struct
// {
//     attitude_t gimbal_imu_data;
//     uint16_t yaw_motor_single_round_angle;

//     uint8_t motor_offline_count;                // 云台电机离线数量
//     gimbal_motor_state_e motor_state;           // 云台电机状态
// } Gimbal_Upload_Data_s;

// typedef struct
// {
//     // code to go here
//     // ...
  
// } Shoot_Upload_Data_s;

#pragma pack() // 开启字节对齐,结束前面的#pragma pack(1)

Robot_Config_s *RobotConfigInit(uint8_t id);
Chassis_Config_s *ChassisConfigFeed(void);
// Gimbal_Config_s *GimbalConfigFeed(void);
// Shoot_Config_s *ShootConfigFeed(void);
 
>>>>>>> 7efda366d82622581d8242e2fe220b83f2f9c878
#endif // !ROBOT_DEF_H