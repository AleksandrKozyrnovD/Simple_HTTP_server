#include <string.h>
#include "server.h"

int server_create(struct logger *slog, char *ip, int port, struct server_ops *ops, void *private_data, struct server *server)
{
    if (!slog || !ip || !ops || !server)
    {
        return -1;
    }
    if (!ops->start || !ops->stop)
    {
        return -1;
    }
    if (port < 0 || port > 65535)
    {
        return -1;
    }
    server->slog = slog;
    strcpy(server->sip, ip);
    server->sport = port;
    server->sops = ops;
    server->private_data = private_data;
    return 0;
}