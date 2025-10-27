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
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Modules/motor
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Modules/motor/DJImotor

    ${CMAKE_CURRENT_SOURCE_DIR}/../../Modules/tools

    # Application include paths
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Application
)

# STM32CubeMX generated application sources
set(Src_Dirs
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Application/robot.c
)

# Interface library for includes and symbols
add_library(framework INTERFACE)
target_include_directories(framework INTERFACE ${Include_Dirs})
target_compile_definitions(framework INTERFACE ${Src_Dirs})
