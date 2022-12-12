cmake_minimum_required(VERSION 3.25)
project(linuxHazi)

set(CMAKE_CXX_STANDARD 23)

find_package(PkgConfig)
pkg_check_modules(Pistache REQUIRED IMPORTED_TARGET libpistache)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PkgConfig::Pistache)