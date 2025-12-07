#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "console_log_ops.h"

void console_log_free(void *private_data)
{
    struct console_log_data *data = (struct console_log_data *)private_data;
    if (data)
    {
        FILE *out = data->out;
        if (out && (out != stdout || out != stderr))
        {
            fclose(out);
        }
    }
}

static void console_log(struct logger *log, const char *fmt, va_list args)
{
    struct console_log_data *data = (struct console_log_data *)log->private_data;
    if (!log)
    {
        perror("log");
        return;
    }
    vfprintf(data->out, fmt, args);
    fflush(data->out);
}

static void console_level_log(struct logger *log, enum log_level level, const char *fmt, va_list args)
{
    struct console_log_data *data = (struct console_log_data *)log->private_data;
    if (!log)
    {
        perror("log");
        return;
    }
    switch (level)
    {
        case DEBUG:
            fprintf(data->out, "[Debug] ");
            break;
        case INFO:
            fprintf(data->out, "[Info] ");
            break;
        case WARN:
            fprintf(data->out, "[Warn] ");
            break;
        case ERROR:
            fprintf(data->out, "[Error] ");
            break;
    }
    vfprintf(data->out, fmt, args);
    fflush(data->out);
}


struct logger_ops console_log_ops = {
    .log = console_log,
    .log_level = console_level_log,
    .private_free = console_log_free,
};
