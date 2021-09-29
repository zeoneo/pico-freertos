cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)
include(FreeRTOS_Kernel_import.cmake)

project(mypico C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()


# Add hello world example

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        -Wno-maybe-uninitialized
        )

add_executable(mypico
        ${FREERTOS_KERNEL_PATH}/event_groups.c
        ${FREERTOS_KERNEL_PATH}/list.c
        ${FREERTOS_KERNEL_PATH}/queue.c
        ${FREERTOS_KERNEL_PATH}/stream_buffer.c
        ${FREERTOS_KERNEL_PATH}/tasks.c
        ${FREERTOS_KERNEL_PATH}/timers.c 
        ${FREERTOS_KERNEL_PATH}/${FREERTOS_KERNEL_RP2040_RELATIVE_PATH}/port.c
        ${FREERTOS_KERNEL_PATH}/portable/MemMang/heap_4.c 

        main.c
        free_rtos_hooks.c
)

target_link_libraries(mypico 
        FreeRTOS-Kernel
        FreeRTOS-Kernel-Heap4
        pico_multicore
        hardware_adc
        hardware_spi
        hardware_dma
        hardware_clocks
        hardware_rtc
        hardware_timer
        pico_stdlib
        pico_stdlib
)

target_include_directories(mypico PUBLIC 
        include/
        ${FREERTOS_KERNEL_PATH}/include 
        ${FREERTOS_KERNEL_PATH}/${FREERTOS_KERNEL_RP2040_RELATIVE_PATH}/include
        ${PICO_SDK_FREERTOS_SOURCE}/portable/GCC/ARM_CM0
)

IF (NOT DEFINED N_SD_CARDS)
    SET(N_SD_CARDS 1)
ENDIF()

target_compile_definitions(mypico PUBLIC DEBUG N_SD_CARDS=${N_SD_CARDS})

pico_enable_stdio_uart(mypico 0)
pico_enable_stdio_usb(mypico 1)

pico_add_extra_outputs(mypico)

# Hardware-specific examples in subdirectories:
