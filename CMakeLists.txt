cmake_minimum_required(VERSION 3.26)
project(BabyPhotoshop)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR})

add_executable(BabyPhotoshop main.cpp
        Editors/filters.h
        Editors/adjustments.h
        Editors/effects.h
)