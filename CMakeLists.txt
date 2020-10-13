cmake_minimum_required(VERSION 3.3)

project(HWRK)

set(CMAKE_C_STANDARD 99)

if(CMAKE_COMPILER_IS_GNUCXX)
    include(CodeCoverage CMAKE_MODULE_PATH)
    SETUP_TARGET_FOR_COVERAGE_LCOV(
        NAME coverage                 # New target name
        EXECUTABLE ctest -C ${ROOT_DIR}/CTestTestfile.cmake # Executable in PROJECT_BINARY_DIR
        DEPENDENCIES ${Boost_LIBRARIES}         # Dependencies to build first
)
endif()

APPEND_COVERAGE_COMPILER_FLAGS()

if(CMAKE_COMPILER_IS_GNUCXX)
    link_libraries(gcov)
endif()

##
### Test definitions ###
##

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
