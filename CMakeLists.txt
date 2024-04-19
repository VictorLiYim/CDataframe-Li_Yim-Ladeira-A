cmake_minimum_required(VERSION 3.27)
project(CDataframe_Li_Yim_Ladeira_A C)

set(CMAKE_C_STANDARD 11)

add_executable(CDataframe_Li_Yim_Ladeira_A
        main.c
        functions.h
        functions.c
        cdataframe.h
        cdataframe.c
        column.h
        column.c)
