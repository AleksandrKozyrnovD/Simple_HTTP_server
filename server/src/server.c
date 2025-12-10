#include <string.h>
#include "server.h"

int server_create(char *ip, int port, struct server_ops *ops, void *private_data, struct server *server)
{
    if (!ip || !ops || !server)
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
    strcpy(server->sip, ip);
    server->sport = port;
    server->sops = ops;
    server->private_data = private_data;
    LOG_INFO("Created server with IP: %s, port: %d\n", server->sip, server->sport);
    return 0;
}