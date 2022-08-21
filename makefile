.PHONY: all

CC = gcc
CFLAGS = -g

SRCS = main.c bmp.c
DEPS = bmp.h
TAG = main.exe

all:
	${CC} ${CFLAGS} -o ${TAG} ${SRCS} ${DEPS}
	./${TAG}
	
