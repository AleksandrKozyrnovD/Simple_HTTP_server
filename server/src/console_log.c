#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "log.h"
#include "rwlock.h"

struct logger
{
    rwlock_t lock;        /* read write lock */
    FILE *out;            /* stdout или другой FILE* */
};

struct logger *logger_new(void *private_data)
{
    (void)private_data;   /* можно FILE*, но не захотелось */
    struct logger *log = malloc(sizeof(struct logger));
    if (!log)
    {
        return NULL;
    }
    rwlock_init(&log->lock);

    log->out = stdout;

    return log;
}

void logger_free(struct logger *log)
{
    if (!log)
        return;
    /* Если логгер работал с файлом */
    if (log->out && (log->out != stdout || log->out != stderr))
    {
        fclose(log->out);
    }
    free(log);
}

void logger_log(struct logger *log, const char *fmt, ...)
{
    va_list args;
    if (!log)
    {
        perror("log");
        return;
    }
    write_lock(&log->lock);

    va_start(args, fmt);
    vfprintf(log->out, fmt, args);
    va_end(args);
    fflush(log->out);
    
    write_unlock(&log->lock);
}
