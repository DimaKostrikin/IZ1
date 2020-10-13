cmake_minimum_required(VERSION 3.3)

set(${TARGET_NAME} HWRK)

project(HWRK)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)

include(CTest)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)

if(CMAKE_COMPILER_IS_GNUCXX) # Покрытие кода.
    include(CodeCoverage)
    link_libraries(gcov)
    APPEND_COVERAGE_COMPILER_FLAGS()
endif()

set(CMAKE_CXX_CPPLINT "/usr/bin/cppcheck;--std=c++11")

configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

enable_testing()
add_subdirectory(test)

##
### Source definitions ###
##

include_directories("${PROJECT_SOURCE_DIR}/include")

file(GLOB sources
  "${PROJECT_SOURCE_DIR}/include/HWRK/*.h"
  "${PROJECT_SOURCE_DIR}/src/*.c"
  "${PROJECT_SOURCE_DIR}/test/*.test")

add_executable(HWRK ${sources})
