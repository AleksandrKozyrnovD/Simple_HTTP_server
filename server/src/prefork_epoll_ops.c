#include "prefork_epoll_ops.h"
#include "epoll.h"
#include <unistd.h>

int prefork_epoll_ops_start(struct server *server)
{
    struct prefork_epoll_data *data = server->private_data;
    server->sfd = epoll_socket_create(server->sip, server->sport);
    if (server->sfd == -1)
    {
        return -1;
    }
    if (!data)
    {
        return -1;
    }
    for (size_t i = 0; i < data->child_num; i++)
    {
        int pid = fork();
        if (pid == -1) /* error on fork */
        {
            return -1;
        }
        if (pid == 0) /* child process */
        {
            return epoll_loop(server);
        }
    }
    /* parent process */
    return epoll_loop(server);
}

int prefork_epoll_ops_stop(struct server *server)
{
    server->running = 0;
    close(server->sfd);
    return 0;
}

struct server_ops prefork_epoll_ops = {
    .start = prefork_epoll_ops_start,
    .stop = prefork_epoll_ops_stop,
};
