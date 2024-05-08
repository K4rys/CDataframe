cmake_minimum_required(VERSION 3.27)
project(CDataframe C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(CDataframe
        column.c
        column.h
        main.c
        list.c
        list.h
        CDataframe.c
        CDataframe.h
)
