cmake_minimum_required(VERSION 3.7)
project(vtest)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp vest_common.h vest.h vest_spec.h vest_defs.h)
add_executable(vtest ${SOURCE_FILES})