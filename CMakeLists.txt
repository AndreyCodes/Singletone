cmake_minimum_required(VERSION 3.0.0)
project(proj VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(proj main.cpp)
target_compile_options(proj PRIVATE -masm=intel)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
