tests: tests.out
	./tests.out

tests.out: bitcount.c bitcount.h tests.c
	gcc bitcount.c tests.c -o tests.out

.PHONY: tests
