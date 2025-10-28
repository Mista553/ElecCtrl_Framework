/**
 * @file robot_def.h
 * @author Zero lanmeiop@163.com
 * @author Zero
 * @version 0.1
 * @date 2025-03-04
 *
 * @copyright Copyright (c) HNU YueLu EC 2022 all rights reserved
 *
 */
#include "robot_def.h"

#include "infantry_config.h"

static Robot_Config_s *robot_instance = {NULL}; 

Robot_Config_s *RobotConfigInit(uint8_t id)
{
    Robot_Config_s *instance = (Robot_Config_s *)malloc(sizeof(Robot_Config_s));
    memset(instance, 0, sizeof(Robot_Config_s));

    if (id == ROBOT_ID)
    {
        switch (id)
        {
        case DART_ROBOT:
            break;
        default:
            break;
        }
    }

    robot_instance = instance;
    return instance;
}

Chassis_Config_s *ChassisConfigFeed(void)
{
    return &robot_instance->chassis_param;
}
