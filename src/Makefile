OS := $(shell uname -s)
CC = gcc 
DIR_SRC = ./
DIR_OBJ = ./obj/
DIR_MEM = ./core/s21_mem/
DIR_STR = ./core/s21_str/

ifeq ($(OS), Darwin)
	@FLAGS := -Wall -Wextra -Werror -std=c11
else
	@FLAGS := -Wall -Wextra -Werror -std=c11 -D_GNU_SOURCE
endif

all: test s21_string s21_strgcov

s21_string:
	$(CC) $(FLAGC)

s21_strgcov:
	$(CC) $(FLAGC)

test:
	$(CC) $(FLAGC)