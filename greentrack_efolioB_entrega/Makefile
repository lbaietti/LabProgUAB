CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c11 -I include
SRC=src/plantas.c src/regas.c src/tarefas.c src/persistencia.c

all: greentrack

greentrack: src/main.c $(SRC)
	$(CC) $(CFLAGS) src/main.c $(SRC) -o greentrack

unit:
	$(CC) $(CFLAGS) tests/test_plantas.c src/plantas.c -o test_plantas
	./test_plantas
	$(CC) $(CFLAGS) tests/test_regas.c src/plantas.c src/regas.c -o test_regas
	./test_regas
	$(CC) $(CFLAGS) tests/test_tarefas.c src/tarefas.c -o test_tarefas
	./test_tarefas

integration:
	$(CC) $(CFLAGS) tests/test_integracao.c $(SRC) -o test_integracao
	./test_integracao

test: unit integration

clean:
	rm -f greentrack test_plantas test_regas test_tarefas test_integracao
	-rm -f plantas.csv regas.csv tarefas.csv
