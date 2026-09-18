CC = gcc
CFLAGS = -Wall -std=c11 -Iinclude

all: tests/test_temperaturas
	./tests/test_temperaturas

#Alias opcional: permite make test ao invés de make all
# Ao dar o comando make test / make all o output será o mesmo
test: all

tests/test_temperaturas: tests/test_temperaturas.c src/temperaturas.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f tests/test_temperaturas

.PHONY: all clean
