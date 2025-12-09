#ifndef __PREFORKEPOLL_H__
#define __PREFORKEPOLL_H__

#include "server.h"

struct prefork_epoll_data
{
    size_t child_num;
    char *static_dir;
};

int prefork_epoll_ops_start(struct server *server);
int prefork_epoll_ops_stop(struct server *server);

extern struct server_ops prefork_epoll_ops;

#endif
