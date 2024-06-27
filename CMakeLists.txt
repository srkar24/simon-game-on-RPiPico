# Set minimum required version of CMake
# This line sets the minimum version of CMake required to build the project. 
# If a lower version of CMake is used, an error will be raised.
cmake_minimum_required(VERSION 3.12)

# Include build function from Pico SDK
# This line includes the build functions from the Pico SDK. 
# The location of the Pico SDK is specified in the environment 
# variable `$ENV{PICO_SDK_PATH}`.
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Set name of project in PROJECT_NAME variable
# This line sets the name of the project to `simon-game` and specifies 
# the programming languages used in the project (C, C++, and ASM).
project(simon-game C CXX ASM)

# Set C language standard to C11
# This line sets the C language standard used in the project to C11.
set(CMAKE_C_STANDARD 11)

# Set C++ language standard to C++17
# This line sets the C++ language standard used in the project to C++17.
set(CMAKE_CXX_STANDARD 17)

# Export compile commands
# This line sets the flag to export the compile commands used during
# the build process. This can be useful for various development tools.
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# The code checks if the VERBOSE variable is set, and if it is, it adds VERBOSE as a preprocessor definition to the compilation of the target.
# In C/C++, preprocessor definitions are used to conditionally compile parts of the code based on whether a certain definition is set. In this case, if VERBOSE is set, the code will be compiled with the VERBOSE definition.
# In the source code, you can then check for the presence of VERBOSE to enable verbose output:
# #ifdef VERBOSE
# // Verbose output code
# #endif
# The value of VERBOSE can be set from the command line when running cmake:
# cmake -DVERBOSE=ON ..

if (VERBOSE)
  add_compile_definitions(VERBOSE)
endif()

# Creates a pico-sdk subdir in our proj for libs
# This line creates a `pico-sdk` subdirectory in the project for the
# libraries specified by the Pico SDK.
pico_sdk_init()

# Add executable target with specified source files
# This line creates an executable target named `simon-game` using the 
# specified source files.
add_executable(${PROJECT_NAME}
    main.cpp
    core1.cpp
    callback.cpp
    debounce.cpp
    simon_game.cpp
)

# Create map, bin, extra, uf2 files
# This line creates the specified output files (`map`, `bin`, `extra`, `uf2`)
# for the `simon-game` target.
pico_add_extra_outputs(${PROJECT_NAME})

# Link to pico_stdlib and pico_multicore libraries
# This line links the project target to the `pico_stdlib` and `pico_multicore` 
# and additional i2c hardware support dependencies
# libraries.
target_link_libraries(
    ${PROJECT_NAME}
    pico_stdlib
    pico_multicore
    hardware_i2c
)

# Specify private include directories for target
# This line adds the current directory to the private include directories for the
# `simon-game` target.
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR} )

# Enable USB output and disable UART output
# This line enables USB output for the `simon-game` target and disables UART output.
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)