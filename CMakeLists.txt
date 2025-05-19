cmake_minimum_required(VERSION 3.10.0)
project(sistema_banco VERSION 0.1.0 LANGUAGES C CXX)

find_package(PkgConfig REQUIRED)
pkg_check_modules(MARIADB REQUIRED mariadb)

include_directories(${MARIADB_INCLUDE_DIRS})
link_directories(${MARIADB_LIBRARY_DIRS})

file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
)
    
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
)

add_executable(sistema_banco ${all_SRCS})

target_link_libraries(sistema_banco ${MARIADB_LIBRARIES})