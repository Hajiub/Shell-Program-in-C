CC = gcc
CFLAGS = -Wextra -Wall
SRC = shell.c
EXEC = ./bin/shell

all: $(EXEC)

$(EXEC): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(EXEC)

run:
	./$(EXEC)

val:
	valgrind ./$(EXEC)