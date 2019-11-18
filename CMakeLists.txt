cmake_minimum_required(VERSION 3.14)
project(hotel C)

set(CMAKE_C_STANDARD 99)

add_executable(hotel main.c libs/sqlite/sqlite3.h libs/sqlite/sqlite3.c libs/datas.h libs/services.h libs/services.c libs/extrafuncs.c libs/extrafuncs.h libs/login.c libs/login.h libs/datas.c libs/reservas.h libs/reservas.c libs/database.h libs/database.c)