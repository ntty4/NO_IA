CC = gcc
CFLAGS = -Wall -Wextra -Werror -O2
OUT = unisee

all: main.c
	$(CC) $(CFLAGS) $< -o $(OUT)

exec:
	./$(OUT)

clean:
	rm  $(OUT)

.PHONY: clean all exec
