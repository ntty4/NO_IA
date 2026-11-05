CC = gcc
CFLAGS = -Wall -Wextra -g
OUT = yat.out
ARGS ?= .

all: $(OUT)

$(OUT): yat.c
	$(CC) $(FLAGS) $< -o $@

run: $(OUT)
	./$(OUT) $(ARGS)

clean:
	rm -f yat.out

.PHONY: all run clean
