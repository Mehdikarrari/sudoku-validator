CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pthread
LDFLAGS = -pthread

sudoku_single: src/main.o src/validator_pthread.o src/io.o src/test_runner.o
	$(CC) $(LDFLAGS) -o $@ $^

SRC = src
OBJS = $(SRC)/main.o $(SRC)/validator_pthread.o $(SRC)/io.o $(SRC)/test_runner.o

EXEC = sudoku_single

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(SRC)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXEC) $(SRC)/*.o
