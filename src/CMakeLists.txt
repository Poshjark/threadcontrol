cmake_minimum_required(VERSION 3.0)

project(atomiq_test LANGUAGES CXX)

find_package(Threads REQUIRED)

set(SOURCE_EXE main.cpp threadswrapper.cpp threadswrapper.h storage.cpp storage.h colors.h colors.cpp)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin)

add_executable(${PROJECT_NAME} ${SOURCE_EXE})

target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
