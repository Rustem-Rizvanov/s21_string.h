OS := $(shell uname -s)
CC = gcc 

OBJ_DIR := .src/obj
MEM_DIR = $(wildcard .core/s21_mem/*.c)
SPRINTF = $(wildcard ./core/s21_sprintf/*.c)
SSCANF = $(wildcard ./core/s21_sscanf/*.c)
STR = $(wildcard ./core/s21_str/*.c)
HEADERS = s21_string.h
OBJ_LIBRARY := $(patsubst %.c, %.o, $(MEM_DIR) $(SPRINTF) $(SSCANF) $(STR))

ifeq ($(OS), Darwin)
	@FLAGS := -Wall -Wextra -Werror -std=c11
else
	@FLAGS := -Wall -Wextra -Werror -std=c11 -D_GNU_SOURCE
endif

all: $(OBJ_LIBRARY) test s21_string s21_strgcov

my_program: $(OBJ_LIBRARY)
	$(CC) $(CFLAGS) $(OBJ_LIBRARY) -o my_program

$(OBJ_DIR)/%.o: %.c 
	$(CC) $(CFLAGS) (MEM_DIR) $(SPRINTF) $(SSCANF) $(STR) -c $< -o ./

s21_string:
	$(CC) $(FLAGC) $(MEM_DIR) $(SPRINTF) $(SSCANF) $(STR) -c ./

s21_strgcov:
	$(CC) $(FLAGC)

s21_string.a: $(OBJ_LIBRARY) $(HEADERS)
	ar rcs s21_string.a $(OBJ_LIBRARY) 
	ranlib s21_string.a
	rm -rf ./*/*.o

test_1: s21_string.a TESTS/SUITE_aux__1.c
	gcc $(CFLAGS) TESTS/SUITE_aux__1.c s21_string.a -o test.out -lm -lcheck
	./test_1.out

test_2: s21_string.a TESTS/SUITE_aux__2.c
	gcc $(CFLAGS) TESTS/SUITE_aux__2.c s21_string.a -o test.out -lm -lcheck
	./test_2.out

test_3: s21_string.a TESTS/SUITE_aux__3.c
	gcc $(CFLAGS) TESTS/SUITE_aux__3.c s21_string.a -o test.out -lm -lcheck
	./test_3.out

gcov_report: s21_string.a TESTS/SUITE_main.c
	gcc $(GCOVFLAGS) TESTS/SUITE_main.c $(SOURCES) -o report.out -lm -lcheck
	./report.out
	gcov -f $(SOURCES)
	lcov -t "gcov_report" -o Coverage_Report.info -c -d .
	genhtml -o ./report Coverage_Report.info
	rm -f *.gcno *.gcda *.info report.out *.gcov
	open ./report/index-sort-f.html

check:
	clang-format -style=Google -n ./*/*.c

rebuild: clean all

clean:
	rm -f ./core/s21_bonus/*.o ./core/s21_str/*o ./core/s21_sscanf/*o ./core/s21_sprintf/*.o *.o *.a *.gcno *.gcda *.info *.out *.gcov
	rm -rf ./report