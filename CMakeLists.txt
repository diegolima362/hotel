cmake_minimum_required(VERSION 3.14)
project(hotel C)

set(CMAKE_C_STANDARD 99)

add_executable(hotel main.c libs/datas.h libs/tipos.h libs/services.h libs/services.c libs/extrafuncs.c libs/extrafuncs.h libs/login.c libs/login.h)