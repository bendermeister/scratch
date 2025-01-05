CFLAGS := -g -Wall -Wpedantic -std=c99 -Wextra -fsanitize=address,leak -lc
CC := clang

build: server client

server: server.c
	${CC} server.c ${CFLAGS} -o server.out

client: client.c
	${CC} client.c ${CFLAGS} -o client.out

clean:
	rm -f server.out client.out
