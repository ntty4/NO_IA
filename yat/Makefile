CC = gcc
FLAGS = -Wall -Wextra -g -ggdb
SRC = yat.c

yat.out:
	$(CC) $(SRC) $(FLAGS) -o $@ 

clean:
	rm yat.out
	make

exec:
	make clean
	./yat.out .
