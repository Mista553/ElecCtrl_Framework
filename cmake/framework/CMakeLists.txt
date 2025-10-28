cmake_minimum_required(VERSION 3.22)
# Enable CMake support for ASM and C languages
enable_language(C ASM)

# include paths
set(Include_Dirs
    # BSP include paths
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Bsp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Bsp/can
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Bsp/dwt

    # Modules include paths
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Modules/algorithm
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Modules/daemon
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Modules/imu
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Modules/message_center
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Modules/motor
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Modules/motor/DJImotor
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Modules/tools

    # Application include paths
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Application
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Application/chassis
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Application/config
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Application/config/infantry_robot
)

# STM32CubeMX generated application sources
set(Src_Dirs
    # BSP include paths
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Bsp/can/bsp_can.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Bsp/dwt/bsp_dwt.c

    # Modules include paths
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Modules/algorithm/controller.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Modules/algorithm/kalman_filter.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Modules/algorithm/QuaternionEKF.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Modules/algorithm/user_lib.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Modules/daemon/daemon.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Modules/imu/BMI088driver.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Modules/imu/BMI088Middleware.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Modules/imu/ins_task.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Modules/message_center/message_center.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Modules/motor/motor_task.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Modules/motor/DJImotor/dji_motor.c

    # Application include paths
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Application/robot.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Application/robot_def.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Application/chassis/balance_chassis.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Application/config/infantry_robot/infantry_config.c
)

# Interface library for includes and symbols
add_library(framework INTERFACE)
target_include_directories(framework INTERFACE ${Include_Dirs})
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${Src_Dirs})
