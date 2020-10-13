include_directories("${PROJECT_SOURCE_DIR}/include")

file(GLOB sources "${PROJECT_SOURCE_DIR}/src/*.c")
list(REMOVE_ITEM sources "${PROJECT_SOURCE_DIR}/src/main.c")

file(GLOB tests "${PROJECT_SOURCE_DIR}/test/*.cpp")
list(REMOVE_ITEM tests "${PROJECT_SOURCE_DIR}/test/main.cpp")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/test/cmake_modules)

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


foreach(file ${tests})
  set(name)
  get_filename_component(name ${file} NAME_WE)
  add_executable("${name}_tests"
    ${sources}
    ${file}
    "${PROJECT_SOURCE_DIR}/test/main.cpp")
  target_link_libraries("${name}_tests" gtest_main)
  add_test(NAME ${name} COMMAND "${name}_tests" WORKING_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/Resources")
endforeach()
