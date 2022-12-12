cmake_minimum_required(VERSION 3.25)
project(linuxHazi)

set(CMAKE_CXX_STANDARD 23)

find_package(PkgConfig)
pkg_check_modules(Pistache REQUIRED IMPORTED_TARGET libpistache)


find_package(spdlog REQUIRED)
add_executable(${PROJECT_NAME} main.cpp OAuthEndpoint.cpp LoginValidator.h)
target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::Pistache)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)
