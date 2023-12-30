OS := $(shell uname -s)
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
TEST_LIBS = -lcheck -lm -lpthread -lsubunit
OBJECTS = s21_decimal.o
SOURSES = s21_decimal.c
GCOVFLAGS = -fprofile-arcs -ftest-coverage


ifeq ($(OS), Darwin)
 FLAGS_PLATFORM = -lcheck
else
 FLAGS_PLATFORM = -lcheck -lsubunit -lrt -lm -lpthread
endif

all: clean s21_decimal.a test

s21_decimal.a: s21_decimal.o
	$(CC) $(CFLAGS) -g -c  $(SOURSES)
	ar rcs s21_decimal.a $(OBJECTS)

clean:
	rm -rf ./*.o ./*.a ./a.out gcov_test *.html *.css ./GcovReport ./*.gcno ./*.gcda ./report ./*.info ./s21_decimal.so ./*.dSYM ./s21_decimal_test test

test: test.c s21_decimal.a
	$(CC) $(CFLAGS) -c test.c $(FLAGS_PLATFORM) -o test.o
	$(CC) $(CFLAGS) -g test.o s21_decimal.a $(FLAGS_PLATFORM) -o test

gcov_report: s21_decimal.a
	$(CC) $(CFLAGS) --coverage test.c s21_decimal.c s21_decimal.a $(FLAGS_PLATFORM) -o gcov_test
	chmod +x *
	./gcov_test
	lcov -t test -o test.info -c -d .
	genhtml -o report test.info
	open ./report/index.html

check: s21_decimal.a
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.c
	clang-format -n *.h
	cppcheck *.h *.c

rebuild: clean all

mini_grind:test
	valgrind --leak-check=full --track-origins=yes --trace-children=yes -s ./test

