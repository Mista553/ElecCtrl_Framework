/**
 * @file chassis.c
 * @author Zero 1433026627@qq.com
 * @brief 底盘应用,负责接收robot_cmd的控制命令并根据命令进行运动学解算,得到输出
 *        注意底盘采取右手系,对于平面视图,底盘纵向运动的正前方为x正方向;横向运动的右侧为y正方向
 *
 * @version 0.1
 * @date 2024-11-18
 *
 * @copyright Copyright (c) 2022 Team JiaoLong-SJTU
 *
 */

#include "balance_chassis.h"
#include "robot_def.h"
#include "dji_motor.h"
// #include "super_cap.h"
// #include "power_manager.h"   
#include "message_center.h"
#include "user_lib.h"

#include "general_def.h"
#include "bsp_dwt.h"
#include "arm_math.h"

static Chassis_Config_s *chassis_config;

/* 底盘应用包含的模块和信息存储,底盘是单例模式,因此不需要为底盘建立单独的结构体 */
#ifdef CHASSIS_BOARD // 如果是底盘板,使用板载IMU获取底盘转动角速度
#include "can_comm.h"
#include "ins_task.h"
static CANCommInstance *chasiss_can_comm; // 双板通信CAN comm
attitude_t *Chassis_IMU_data;
#endif // CHASSIS_BOARD
#ifdef ONE_BOARD
static Publisher_t *chassis_pub;                    // 用于发布底盘的数据
static Subscriber_t *chassis_sub;                   // 用于订阅底盘的控制命令
#endif                                              // !ONE_BOARD
static Chassis_Ctrl_Cmd_s chassis_cmd_recv;         // 底盘接收到的控制命令
static Chassis_Upload_Data_s chassis_feedback_data; // 底盘回传的反馈数据

// static SuperCapInstance *cap;                                       // 超级电容
static DJIMotorInstance *motor_lf, *motor_rf, *motor_lb, *motor_rb; // left right forward back
// static PowerManagerInstance *power_manager;                         // 功率管理

/* 私有变量用于底盘旋转的机械参数常量 */
static float lf_center, rf_center, lb_center, rb_center; // 左右前后轮子中心
static float rpm_2_wheel_vector;
/* 用于自旋变速策略的时间变量 */
// static float t;

/* 私有函数计算的中介变量,设为静态避免参数传递的开销 */
static float chassis_vx, chassis_vy;                 // 将云台系的速度投影到底盘
static float vt_lf, vt_rf, vt_lb, vt_rb;             // 底盘速度解算后的输出
static float rl_vt_lf, rl_vt_rf, rl_vt_lb, rl_vt_rb; // 底盘真实速度 m/s

#ifndef GIMBAL_BOARD
void BalanceChassisInit()
{
    static float half_wheel_base, half_track_width, perimeter_wheel;    // 半轴距,半轮距,轮子周长
    static float center_gimbal_offset_x, center_gimbal_offset_y;        // 中心云台偏移量
    static float reduction_ratio_wheel;                                 // 轮子减速比

    chassis_config = ChassisConfigFeed();

    half_wheel_base = (chassis_config->wheel_measure.wheel_base / 2.0f);
    half_track_width = (chassis_config->wheel_measure.track_width / 2.0f);
    perimeter_wheel = (chassis_config->wheel_measure.radius_wheel * 2 * PI);
    center_gimbal_offset_x = chassis_config->wheel_measure.center_gimbal_offset_x;
    center_gimbal_offset_y = chassis_config->wheel_measure.center_gimbal_offset_y;
    reduction_ratio_wheel = chassis_config->wheel_measure.reduction_ratio_wheel;

    lf_center = ((half_track_width + center_gimbal_offset_x + half_wheel_base - center_gimbal_offset_y) * DEGREE_2_RAD);
    rf_center = ((half_track_width - center_gimbal_offset_x + half_wheel_base - center_gimbal_offset_y) * DEGREE_2_RAD);
    lb_center = ((half_track_width + center_gimbal_offset_x + half_wheel_base + center_gimbal_offset_y) * DEGREE_2_RAD);
    rb_center = ((half_track_width - center_gimbal_offset_x + half_wheel_base + center_gimbal_offset_y) * DEGREE_2_RAD);
    rpm_2_wheel_vector = (ANGLE_2_RPM_PER_MIN * (perimeter_wheel * MM_2_M) / (reduction_ratio_wheel * MIN_2_SEC));

    // 四个轮子的参数一样,改tx_id和反转标志位即可
    chassis_config->chassis_motor_config.can_init_config.tx_id = chassis_config->chassis_motor_id[MOTOR_LF];
    chassis_config->chassis_motor_config.controller_setting_init_config.motor_reverse_flag = MOTOR_DIRECTION_REVERSE;
    motor_lf = DJIMotorInit(&chassis_config->chassis_motor_config);     

    chassis_config->chassis_motor_config.can_init_config.tx_id = chassis_config->chassis_motor_id[MOTOR_RF];
    chassis_config->chassis_motor_config.controller_setting_init_config.motor_reverse_flag = MOTOR_DIRECTION_REVERSE;
    motor_rf = DJIMotorInit(&chassis_config->chassis_motor_config);

    chassis_config->chassis_motor_config.can_init_config.tx_id = chassis_config->chassis_motor_id[MOTOR_LB]; 
    chassis_config->chassis_motor_config.controller_setting_init_config.motor_reverse_flag = MOTOR_DIRECTION_REVERSE;
    motor_lb = DJIMotorInit(&chassis_config->chassis_motor_config);

    chassis_config->chassis_motor_config.can_init_config.tx_id = chassis_config->chassis_motor_id[MOTOR_RB];     
    chassis_config->chassis_motor_config.controller_setting_init_config.motor_reverse_flag = MOTOR_DIRECTION_REVERSE;
    motor_rb = DJIMotorInit(&chassis_config->chassis_motor_config);

    // SuperCap_Init_Config_s cap_conf = {
    //     .can_config = {
    //         .can_handle = &hcan2,
    //         .tx_id = 0x302, // 超级电容默认接收id
    //         .rx_id = 0x301, // 超级电容默认发送id,注意tx和rx在其他人看来是反的
    //     }};
    // cap = SuperCapInit(&cap_conf); // 超级电容初始化

    // PowerManager_Init_Config_s power_manager_conf = {
    //     .k1 = 0.013,    // 越大功率限制权重越大  
    //     .k2 = 5.23,     // 5.23
    //     .k3 = 0.82,     // 0.82
    //     };
    // power_manager = PowerControlInit(&power_manager_conf); // 功率管理初始化 

    chassis_sub = SubRegister("chassis_cmd", sizeof(Chassis_Ctrl_Cmd_s));
    chassis_pub = PubRegister("chassis_feed", sizeof(Chassis_Upload_Data_s));
}

/**
 * @brief 计算每个轮毂电机的输出,正运动学解算
 *        用宏进行预替换减小开销,运动解算具体过程参考教程
 */
static void ChassisCalculate()
{
    switch (chassis_config->wheel_type)
    {
    case MECANUM_WHEEL:
        // 麦轮解算逆运动学模型
        vt_lf = -chassis_vx - chassis_vy - chassis_cmd_recv.wz * lf_center;
        vt_rf = -chassis_vx + chassis_vy - chassis_cmd_recv.wz * rf_center;
        vt_lb = chassis_vx - chassis_vy - chassis_cmd_recv.wz * lb_center;
        vt_rb = chassis_vx + chassis_vy - chassis_cmd_recv.wz * rb_center;
        break;
    case OMNI_WHEEL:
        // 全向轮解算逆运动学模型
        vt_lf = -sqrtf(2) / 2.0f * chassis_vx - sqrtf(2) / 2.0f * chassis_vy - chassis_cmd_recv.wz * lf_center;
        vt_rf = -sqrtf(2) / 2.0f * chassis_vx + sqrtf(2) / 2.0f * chassis_vy - chassis_cmd_recv.wz * rf_center;
        vt_lb = sqrtf(2) / 2.0f * chassis_vx + sqrtf(2) / 2.0f * chassis_vy - chassis_cmd_recv.wz * lb_center;
        vt_rb = sqrtf(2) / 2.0f * chassis_vx - sqrtf(2) / 2.0f * chassis_vy - chassis_cmd_recv.wz * rb_center;
        break;
    default:
        break;
    }
}

#define RPM_2_VECTOR (ANGLE_2_RPM_PER_MIN * RPM_2_WHEEL_VECTOR)
/**
 * @brief 根据每个轮子的速度反馈,计算底盘的实际运动速度,逆运动解算
 *        对于双板的情况,考虑增加来自底盘板IMU的数据
 *
 */
static void EstimateSpeed()
{
    // // 根据电机速度和陀螺仪的角速度进行解算,还可以利用加速度计判断是否打滑(如果有)
    // //正运动学模型
    // rl_vt_lf = motor_lf->measure.speed_aps * RPM_2_VECTOR;
    // rl_vt_rf = -motor_rf->measure.speed_aps * RPM_2_VECTOR;
    // rl_vt_lb = motor_lb->measure.speed_aps * RPM_2_VECTOR;
    // rl_vt_rb = -motor_rb->measure.speed_aps * RPM_2_VECTOR;

    // //底盘向前为正方向,向左为正方向,单位m/s
    // chassis_feedback_data.real_vx = (rl_vt_lb + rl_vt_rb) / 2.0f;
    // chassis_feedback_data.real_vy = (rl_vt_lb - rl_vt_lf) / 2.0f;

    // //底盘逆时针旋转为正方向,单位rad/s
    // chassis_feedback_data.real_wz = (rl_vt_rf - rl_vt_lb) / (2.0f * (HALF_WHEEL_BASE * MM_2_M + HALF_TRACK_WIDTH * MM_2_M));
}
/* 机器人底盘控制核心任务 */
void BalanceChassisTask()
{
    // 后续增加没收到消息的处理(双板的情况)
    // 获取新的控制信息
    SubGetMessage(chassis_sub, &chassis_cmd_recv);

    if (chassis_cmd_recv.chassis_mode == CHASSIS_ZERO_FORCE)
    { // 如果出现重要模块离线或遥控器设置为急停,让电机停止
        DJIMotorStop(motor_lf);
        DJIMotorStop(motor_rf);
        DJIMotorStop(motor_lb);
        DJIMotorStop(motor_rb);
    }
    else
    { // 正常工作
        DJIMotorEnable(motor_lf);
        DJIMotorEnable(motor_rf);
        DJIMotorEnable(motor_lb);
        DJIMotorEnable(motor_rb);
    }
    // 根据控制模式设定旋转速度
    switch (chassis_cmd_recv.chassis_mode)
    {
    case CHASSIS_NO_FOLLOW: // 底盘不旋转,但维持全向机动,一般用于调整云台姿态
        chassis_cmd_recv.wz = chassis_cmd_recv.wz / rpm_2_wheel_vector;
        break;     
    case CHASSIS_FOLLOW_GIMBAL_YAW: // 跟随云台,不单独设置pid,以误差角度平方为速度输出
        chassis_cmd_recv.wz = -1.5f * chassis_cmd_recv.offset_angle * abs(chassis_cmd_recv.offset_angle);
        break;
    case CHASSIS_ROTATE: // 自旋,同时保持全向机动;当前wz维持定值,后续增加不规则的变速策略
        chassis_cmd_recv.wz = 5000;
        break;
    default:
        break;
    }

    // 根据云台和底盘的角度offset将控制量映射到底盘坐标系上
    // 底盘逆时针旋转为角度正方向;云台命令的方向以云台指向的方向为x,采用右手系(x指向正北时y在正东)
    static float sin_theta, cos_theta;
    cos_theta = arm_cos_f32(chassis_cmd_recv.offset_angle * DEGREE_2_RAD);
    sin_theta = arm_sin_f32(chassis_cmd_recv.offset_angle * DEGREE_2_RAD);
    chassis_vx = (chassis_cmd_recv.vx * cos_theta - chassis_cmd_recv.vy * sin_theta) / rpm_2_wheel_vector;
    chassis_vy = (chassis_cmd_recv.vx * sin_theta + chassis_cmd_recv.vy * cos_theta) / rpm_2_wheel_vector;
   
    // 根据控制模式进行正运动学解算,计算底盘输出
    ChassisCalculate();

    // // 根据裁判系统的反馈数据和电容数据对输出限幅并设定闭环参考值
    // LimitChassisOutput();

    // 根据电机的反馈速度和IMU(如果有)计算真实速度
    EstimateSpeed();

// #ifdef ONE_BOARD
//     // 根据电机状态反馈是否离线
//     DJIMotorIsOnline(motor_lf);
//     DJIMotorIsOnline(motor_rf);
//     DJIMotorIsOnline(motor_lb);
//     DJIMotorIsOnline(motor_rb);
//     // 反馈电机离线数量
//     if (motor_lf->online_flag || motor_rf->online_flag || motor_lb->online_flag || motor_rb->online_flag)
//     {
//         chassis_feedback_data.motor_offline_count = motor_lf->online_flag + motor_rf->online_flag + motor_lb->online_flag + motor_rb->online_flag;  
//         chassis_feedback_data.motor_state = CHASSIS_MOTOR_OFFLINE;
//     }
//     else
//     {
//         chassis_feedback_data.motor_offline_count = 0;
//         chassis_feedback_data.motor_state = CHASSIS_MOTOR_ONLINE;
//     }
// #endif

#ifdef CHASSIS_BOARD
    ;
#endif // CHASSIS_BOARD

    // 推送反馈消息
#ifdef ONE_BOARD
    PubPushMessage(chassis_pub, (void *)&chassis_feedback_data);
#endif
#ifdef CHASSIS_BOARD
    CANCommSend(chasiss_can_comm, (void *)&chassis_feedback_data);
#endif // CHASSIS_BOARD
}
#endif 