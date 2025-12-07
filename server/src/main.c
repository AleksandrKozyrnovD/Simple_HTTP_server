#include <stdio.h>
#include "console_log_ops.h"

int main(void)
{
    int ret = 0;
    struct logger slog;
    struct console_log_data console_log_data = { .out = stdout };

    ret = log_create(&console_log_ops, &console_log_data, &slog);
    if (ret)
    {
        perror("log_create");
        return -1;
    }

    for (int i = 0; i < 10; i++)
    {
        log_debug(&slog, "Hello (%d)\n", i);
    }

    log_free(&slog);

    return 0;
}