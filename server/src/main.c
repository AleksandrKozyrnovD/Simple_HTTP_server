#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "console_log_ops.h"
#include "prefork_epoll_ops.h"

static struct server server;

void sigint_handler(int sig)
{
    printf("Caught signal %d\n", sig);
    server.sops->stop(&server);
}

int main(void)
{
    int ret = 0;
    struct logger slog;
    struct console_log_data console_log_data = { .out = stdout };
    struct prefork_epoll_data prefork_epoll_data = { .child_num = 4, .static_dir = "static" };

    ret = log_create(&console_log_ops, &console_log_data, &slog);
    if (ret)
    {
        perror("log_create");
        return -1;
    }

    ret = server_create(&slog, "127.0.0.1", 12345, &prefork_epoll_ops, &prefork_epoll_data, &server);
    if (ret)
    {
        perror("server_create");
        return -1;
    }

    /* signal kill, interrupt into sigint_handler */
    signal(SIGINT, sigint_handler);

    server.sops->start(&server);

    log_free(&slog);

    return 0;
}