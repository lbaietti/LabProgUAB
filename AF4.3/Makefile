CC = gcc
CFLAGS = -Wall -std=c11 -Iinclude

all: tests/test_temperaturas
	./tests/test_temperaturas

tests/test_temperaturas: tests/test_temperaturas.c src/temperaturas.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f tests/test_temperaturas

.PHONY: all clean
