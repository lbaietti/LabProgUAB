CC = gcc
CFLAGS = -Wall -Wextra -Wshadow -I./include
OBJS = src/pontuacao.c

testeIntegracao: $(OBJS) src/nivel.c tests/test_integracao.c 
			$(CC) $(CFLAGS) $(OBJS) src/nivel.c tests/test_integracao.c -o testeIntegracao

testeUnidade: $(OBJS) tests/test_pontuacao.c 
			$(CC) $(CFLAGS) $(OBJS) tests/test_pontuacao.c -o testePontuacao


clean: 
	rm -f testeIntegracao testePontuacao




