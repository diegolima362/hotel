cmake_minimum_required(VERSION 3.14)
project(hotel C)

set(CMAKE_C_STANDARD 11)

add_executable(hotel main.c libs/datas.h libs/services.h libs/services.c libs/extrafuncs.c libs/extrafuncs.h libs/login.c libs/login.h libs/datas.c libs/reservas.h libs/reservas.c libs/database.h libs/database.c)
target_link_libraries(hotel LINK_PUBLIC sqlite3)
