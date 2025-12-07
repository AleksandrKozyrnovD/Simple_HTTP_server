#ifndef __SERVER_H__
#define __SERVER_H__

#include "log.h"

struct server;

struct server_ops
{
    int (*start)(struct server *server);
    int (*stop)(struct server *server);
};

struct server
{
    struct logger *slog;
    char sip[16];               /*IPv4 max char size*/ 
    int sport;                  /* server port */
    int sfd;                    /* server socket */
    int running;
    struct server_ops *sops;
    /* connection queue here, but later */
    void *private_data;
};


int server_create(struct logger *slog,
    char *ip,
    int port,
    struct server_ops *ops,
    void *private_data,
    struct server *server_out);


#endif
