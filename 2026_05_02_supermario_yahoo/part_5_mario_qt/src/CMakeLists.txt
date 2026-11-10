cmake_minimum_required(VERSION 3.2...3.27.5)

project(super_mario)
find_package(Qt5 REQUIRED COMPONENTS Widgets)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_CXX_FLAGS "-finput-charset=utf-8 -fexec-charset=utf-8")

set(SOURCES main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)

add_subdirectory(os_controls)
add_subdirectory(controller)
add_subdirectory(levels)
add_subdirectory(model)
add_subdirectory(objects)
add_subdirectory(ui)
add_subdirectory(util)

