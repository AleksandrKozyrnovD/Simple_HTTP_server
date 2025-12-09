#ifndef SERVER_EPOLL_H
#define SERVER_EPOLL_H

#include "server.h"

int epoll_socket_create(char *host, int port);
int epoll_loop(struct server *server);

#endif // SERVER_EPOLL_H

