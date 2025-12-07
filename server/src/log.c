#include <stdarg.h>
#include "log.h"

int log_create(struct logger_ops *lops, void *private_data, struct logger *log)
{
    int ret = 0;
    if (!lops || !log)
    {
        return -1;
    }
    log->lops = lops;
    rwlock_init(&log->lock);
    log->private_data = private_data;
    return ret;
}

void log_free(struct logger *log)
{
    if (log)
    {
        log->lops->private_free(log->private_data);
    }
}

void log_debug(struct logger *log, const char *fmt, ...)
{
    va_list args;
    if (!log)
    {
        return;
    }
    write_lock(&log->lock);
    va_start(args, fmt);
    log->lops->log_level(log, DEBUG, fmt, args);
    va_end(args);
    write_unlock(&log->lock);
}

void log_info(struct logger *log, const char *fmt, ...)
{
    va_list args;
    if (!log)
    {
        return;
    }
    write_lock(&log->lock);
    va_start(args, fmt);
    log->lops->log_level(log, INFO, fmt, args);
    va_end(args);
    write_unlock(&log->lock);
}

void log_warn(struct logger *log, const char *fmt, ...)
{
    va_list args;
    if (!log)
    {
        return;
    }
    write_lock(&log->lock);
    va_start(args, fmt);
    log->lops->log_level(log, WARN, fmt, args);
    va_end(args);
    write_unlock(&log->lock);
}

void log_error(struct logger *log, const char *fmt, ...)
{
    va_list args;
    if (!log)
    {
        return;
    }
    write_lock(&log->lock);
    va_start(args, fmt);
    log->lops->log_level(log, ERROR, fmt, args);
    va_end(args);
    write_unlock(&log->lock);
}