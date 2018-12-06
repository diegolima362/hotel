#include <stdio.h>
#include <stdlib.h>

int main(){
	system("clear"); system("clear");
	system("gcc -c main.c \n gcc -c LIB/datas.c \n gcc -c LIB/fatura.c \n gcc -c LIB/log.c \n gcc -c LIB/sis.c \n gcc -c LIB/cfg.c \n gcc -c LIB/base.c \n gcc -c LIB/files.c \n gcc -c LIB/elements.c \n gcc -c LIB/guest.c\ngcc -c LIB/rooms.c");
	system("\n gcc -c LIB/texts.c \n gcc -c LIB/hotel.c \n gcc -c LIB/search.c\n gcc -c LIB/services.c \n");
	system("gcc -o 0 main.o log.o fatura.o services.o datas.o base.o files.o  elements.o  guest.o  texts.o  hotel.o  search.o rooms.o sis.o cfg.o\n");
	system("rm main.o\n rm fatura.o\n rm log.o \n rm services.o \n rm datas.o \n rm base.o \nrm files.o \nrm elements.o  \nrm guest.o \nrm texts.o \nrm hotel.o \nrm search.o \nrm rooms.o\nrm sis.o\nrm cfg.o \n");
	
}
