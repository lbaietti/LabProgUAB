CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -I./include
OBJS = bin/senha.o bin/main.o 

#Do Not DEBUG can be used for jumping across tests and finish to read all the code from testar_senha.c

app: $(OBJS)
		$(CC) -o $@ $^

bin/%.o: ./src/%.c ./tests/%.c
		@mkdir -p bin
		$(CC) $(CFLAGS) -c $< -o $@