cmake_minimum_required(VERSION 3.14)
project(hotel C)

set(CMAKE_C_STANDARD 11)

add_executable(hotel main.c libs/datas.h libs/extrafuncs.c libs/extrafuncs.h libs/login.c libs/login.h libs/datas.c libs/database.h libs/database.c libs/browserdb.c libs/browserdb.h libs/elementos_hotel/clientes.c libs/elementos_hotel/clientes.h libs/elementos_hotel/reservas.c libs/elementos_hotel/reservas.h libs/elementos_hotel/servicos.c libs/elementos_hotel/servicos.h libs/elementos_hotel/quartos.c libs/elementos_hotel/quartos.h)
target_link_libraries(hotel LINK_PUBLIC sqlite3)
