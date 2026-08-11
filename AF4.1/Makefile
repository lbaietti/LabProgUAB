CC=g++
CFLAGS=-Wall -Wextra -IInclude
OBJS=obj/plantas.o obj/regas.o obj/tarefas.o obj/main.o

greentrack.exe: $(OBJS)
	$(CC) -o $@ $^

obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@