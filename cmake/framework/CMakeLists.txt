cmake_minimum_required(VERSION 3.22)
# Enable CMake support for ASM and C languages
enable_language(C ASM)

# STM32CubeMX generated include paths
set(Include_Dirs
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Bsp/can
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Bsp/dwt
    
    # ${CMAKE_CURRENT_SOURCE_DIR}/../../Modules
    # ${CMAKE_CURRENT_SOURCE_DIR}/../../Application
)

# STM32CubeMX generated application sources
set(Src_Dirs
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Bsp/dwt/bsp_dwt.c
    # ${CMAKE_CURRENT_SOURCE_DIR}/../../Modules
    # ${CMAKE_CURRENT_SOURCE_DIR}/../../Application
)

# Interface library for includes and symbols
add_library(framework INTERFACE)
target_include_directories(framework INTERFACE ${Include_Dirs})
target_compile_definitions(framework INTERFACE ${Src_Dirs})
