#define _GNU_SOURCE
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>

#define panic_(FILE, LINE, FMT, ...) do {                       \
        fprintf(stderr, "PANIC %s:%d: ", FILE, LINE);           \
        fprintf(stderr, FMT, __VA_ARGS__);                      \
        fprintf(stderr, "\n");                                  \
    } while (0)

#define panic(FMT, ...) panic_(__FILE__, __LINE__, FMT, __VA_ARGS__)

int 
main(void) {
    int status = 0;
    struct addrinfo hints = {0};
    struct addrinfo *res = NULL;

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    status = getaddrinfo(NULL, "8080", &hints, &res);

    if (status != 0) {
        panic("getaddrinfo error: %s\n", gai_strerror(status));
    }

    int sockfd = 0;
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    if (sockfd == -1) {
        panic("could not get socket: %s", strerror(errno));
    }

    status = bind(sockfd, res->ai_addr, res->ai_addrlen);

    if (status == -1) {
        panic("could not bind socket: %s", strerror(errno));
    }

    freeaddrinfo(res);

    return 0;
}
