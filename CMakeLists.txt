cmake_minimum_required(VERSION 2.8)

project(GTKLearning)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall ${CMAKE_CXX_FLAGS}")

set(SOURCE_DIR "src")

set(CMAKE_MODULE_PATH "/usr/local/share/Logger/;/usr/local/share/MiscUtils/;/usr/local/share/SFML/cmake/Modules;${CMAKE_MODULE_PATH}")

set(EXECUTABLE_NAME "GTKLearning")

add_executable(${EXECUTABLE_NAME}
               ${SOURCE_DIR}/main.cpp)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM gtkmm-3.0)

link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})
target_link_libraries(${EXECUTABLE_NAME} ${GTKMM_LIBRARIES})

find_package(Logger REQUIRED)
target_link_libraries(${EXECUTABLE_NAME} Logger)

find_package(MiscUtils REQUIRED)
target_link_libraries(${EXECUTABLE_NAME} MiscUtils)
