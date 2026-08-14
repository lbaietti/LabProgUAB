CC = gcc	
CFLAG = -I ./include -Wall -Wextra -Wpedantic
OBJS = src/*.c -o log_test

log_test: $(OBJS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAG) -c $< -o $@