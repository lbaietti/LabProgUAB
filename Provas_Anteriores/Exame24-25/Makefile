CC = gcc 
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

# Lista dos executáveis de Teste (um por módulo)




# Regra Principal: Compila e executa todos os testes 
all: $(TESTES)
	@for test in $(TESTES); do \
		echo "Executando $$test..."; \
		./$$test; \
	done

