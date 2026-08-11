CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -Iinclude
TARGET  = programa

SRCDIR  = src
BUILDDIR = build

SRCS    = $(wildcard $(SRCDIR)/*.c)
OBJS    = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SRCS))

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

run: all
	./$(TARGET)

clean:
	rm -rf $(BUILDDIR) $(TARGET)
