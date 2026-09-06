CC = gcc
CFLAGS = -Wall -Wextra -Waddress -I./include
OBJS = bin/contacto.o bin/validacao.o bin/lista.o bin/io.o bin/main.o

programa: $(OBJS)
		$(CC) -o $@ $^

bin/%.o: ./src/%.c
		@mkdir -p bin
		$(CC) $(CFLAGS) -c $< -o $@