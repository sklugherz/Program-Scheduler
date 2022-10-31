cmake_minimum_required(VERSION 3.11)
project(Program Scheduler)


# Using -Wall is required:
add_compile_options(-Wall)

# These compile flags are highly recommended:
add_compile_options(-Wextra -Wpedantic)

# Super-strict mode:
add_compile_options(-fmessage-length=80 -fno-diagnostics-show-option
    -fstack-protector-all -g -O3 -std=c++17 -Walloc-zero -Walloca
    -Wconversion -Wctor-dtor-privacy -Wduplicated-cond
    -Wduplicated-branches -Wextra-semi -Wfatal-errors
    -Winit-self -Wlogical-op -Wold-style-cast -Wshadow
    -Wunused-const-variable=1 -Wzero-as-null-pointer-constant)
 #-Werror
# add_compile_options must be BEFORE add_executable.

# Create the executable from the source file main.cc:
add_library(${PROJECT_NAME} Show.cc Schedule.cc)
add_executable(test test.cc)
target_link_libraries(test ${PROJECT_NAME})

# Create a tar file every time:
add_custom_target(${PROJECT_NAME}.tar ALL COMMAND
    tar -czf ${PROJECT_NAME}.tar *.cc *.h CMakeLists.txt)
