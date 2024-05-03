cmake_minimum_required(VERSION 3.0.0)
project(NesEmulator VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(NesEmulator
        src/cpu.h
        src/cpu.cpp
        src/bus.cpp
        src/bus.h
        src/apu.h
        src/apu.cpp
        src/ppu.h
        src/ppu.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
