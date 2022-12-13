cmake_minimum_required(VERSION 3.25)
project(linuxHazi)

set(CMAKE_CXX_STANDARD 23)

find_package(PkgConfig)
pkg_check_modules(Pistache REQUIRED IMPORTED_TARGET libpistache)


find_package(spdlog REQUIRED)
find_package(PostgreSQL REQUIRED)
find_package(cpp-jwt REQUIRED)
add_subdirectory(external/libbcrypt)

add_executable(${PROJECT_NAME} main.cpp OAuthEndpoint.cpp LoginValidator.h PostgresLoginValidator.cpp PostgresLoginValidator.h)

target_include_directories(${PROJECT_NAME} PRIVATE "external/libbcrypt/include" IMPORTED)
target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::Pistache)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)
target_link_libraries(${PROJECT_NAME} PRIVATE cpp-jwt::cpp-jwt)
target_link_libraries(${PROJECT_NAME} PRIVATE PostgreSQL::PostgreSQL)
target_link_libraries(${PROJECT_NAME} PRIVATE pqxx)
target_link_libraries(${PROJECT_NAME} PRIVATE bcrypt)
