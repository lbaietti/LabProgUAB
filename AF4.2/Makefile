CC = gcc
CFLAGS = -Wall -Wextra -Wshadow -I./include
TESTS = tests/test_integracao.c tests/test_pontuacao.c

all: runTest

runTest: tests/test_integracao.c tests/test_pontuacao.c $(TESTS)
			$(CC) $(CFLAGS) tests/test_integracao.c tests/test_pontuacao.c $(TESTS) -o runTest

clean:
	-rm -f bin/test_integracao bin/test_pontuacao



