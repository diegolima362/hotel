# PROTOTIPO DE UM SISTEMA DE GERENCIAMENTO DE HOTEL

- 2018: Projeto Linguagem de Programacao I
- 2019~2020: Refatoracao e utilizacao Sqlite3


# Build na linha de comando
\
CMake >= 3.14

-> Linux
```sh
$ mkdir build
$ cd build
$ cmake ../src
$ make
```

-> Windows : Path C compiler, MinGW

```sh
$ mkdir build
$ cd build
$ cmake ../src/
$ make
```
ou
```
$ mkdir build
$ cd build
$ cmake ../src/
$ cmake -DCMAKE_C_COMPILER=C:/MinGW/bin/gcc.exe -DCMAKE_CXX_COMPILER=C:/MinGW/bin/g++.exe ../src/ -G "MinGW Makefiles"
$ make
```

