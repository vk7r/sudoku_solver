
CC = gcc
CFLAGS = -Wall -Wextra -Werror -O3
INCLUDES=
LDFLAGS=
# -lm

graphics_test: main.c
	$(CC) -o main main.c $(LDFLAGS)


clean:
	rm -f ./main
