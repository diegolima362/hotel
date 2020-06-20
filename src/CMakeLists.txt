PROJECT(hotel)
cmake_minimum_required(VERSION 3.14)

include_directories(${CMAKE_SOURCE_DIR}/src)
add_library(sqlite3 STATIC libs/db/sqlite3.c libs/db/sqlite3.h libs/db/sqlite3ext.h)

add_executable(Hotel
        libs/db/sqlite3.c
        libs/db/sqlite3.h
        libs/db/sqlite3ext.h
        libs/elementos_hotel/clientes.c
        libs/elementos_hotel/clientes.h
        libs/elementos_hotel/quartos.c
        libs/elementos_hotel/quartos.h
        libs/elementos_hotel/reservas.c
        libs/elementos_hotel/reservas.h
        libs/elementos_hotel/servicos.c
        libs/elementos_hotel/servicos.h
        libs/browserdb.c
        libs/browserdb.h
        libs/database.c
        libs/database.h
        libs/datas.c
        libs/datas.h
        libs/extrafuncs.c
        libs/extrafuncs.h
        libs/login.c
        libs/login.h
        libs/home.c
        libs/home.h
        main.c)

set_target_properties(Hotel PROPERTIES OUTPUT_NAME hotel)

add_definitions(-DSQLITE_ENABLE_RTREE)
add_definitions(-DSQLITE_ENABLE_FTS4)
add_definitions(-DSQLITE_ENABLE_FTS5)
add_definitions(-DSQLITE_ENABLE_JSON1)
add_definitions(-DSQLITE_ENABLE_RBU)
add_definitions(-DSQLITE_ENABLE_STAT4)

# Uncomment this for single-threaded variant (faster)
#add_definitions(-DSQLITE_THREADSAFE=0)

if (WIN32)
    add_custom_command(TARGET Hotel POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Hotel> ${CMAKE_BINARY_DIR}/Hotel.exe
            DEPENDS Hotel
            )
    install(FILES Hotel.exe DESTINATION bin)
else ()
    include(FindThreads)
    target_link_libraries(Hotel m ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})
    install(TARGETS Hotel RUNTIME DESTINATION bin)
endif ()

install(FILES src/sqlite3.h src/sqlite3ext.h DESTINATION include)
install(TARGETS sqlite3 LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)