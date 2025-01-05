#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>

int 
main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "PANIC: wrong number of arguments: expected 2 got %d\n", argc - 1);
        exit(1);
    }

    struct addrinfo *res = NULL;
    struct addrinfo hints = {0};
    int sockfd = 0;
    int status = 0;

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    status = getaddrinfo(argv[1], argv[2], &hints, &res);
    if (status == -1) {
        fprintf(stderr, 
                "PANIC: could not get addrinfo for: '%s:%s': %s\n", 
                argv[1], argv[2], gai_strerror(status));
        exit(1);
    }

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfd == -1) {
        fprintf(stderr, "PANIC: could not get socket: %s\n", strerror(errno));
        exit(1);
    }

    status = connect(sockfd, res->ai_addr, res->ai_addrlen);

    if (status == -1) {
        fprintf(stderr, "could not connect to server: %s", strerror(errno));
        exit(1);
    }

    freeaddrinfo(res);

    return 0;
}
