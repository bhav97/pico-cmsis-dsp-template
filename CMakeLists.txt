cmake_minimum_required(VERSION 3.13)

# initialize pico-sdk from GIT
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_FETCH_FROM_GIT on)
include(pico_sdk_import.cmake)
include(cmsis_dsp_import.cmake)
# Rpi pico CMSIS core is used by CMSISDSP
set(CMSISCORE ${PICO_SDK_PATH}/src/rp2_common/cmsis/stub/CMSIS/Core)

project(pico-template
    LANGUAGES C CXX ASM 
    VERSION 1.0
)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

# GLobal options for gcc
add_compile_options(-Wall
    -Wno-format
    -Wno-unused-function
    -Wno-maybe-unintialized
    -ffunction-sections
    -fdata-sections
    )

add_subdirectory(${CMSIS_DSP_PATH}/Source CMSISDSP)
target_compile_options(CMSISDSP PRIVATE -Ofast)

# projects can have multiple executables and/or libraries
add_executable(hello_world)

# sources for hello_world
target_sources(hello_world 
    PUBLIC
        main.c
        arm_fft_bin_data.c
)

# depends on
target_link_libraries(hello_world 
    CMSISDSP
    pico_stdlib
)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(hello_world)
