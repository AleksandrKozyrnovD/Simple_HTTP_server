#ifndef __LOG_H__
#define __LOG_H__

#include <stdarg.h>
#include "rwlock.h"

struct logger;

enum log_level
{
    DEBUG = 0,
    INFO,
    WARN,
    ERROR
};

struct logger_ops
{
    void (*log)(struct logger *log, const char *fmt, va_list args);
    void (*log_level)(struct logger *log, enum log_level level, const char *fmt, va_list args);
    void (*private_free)(void *private_data);
};

struct logger
{
    struct logger_ops *lops;
    rwlock_t lock;
    void *private_data;
};


int log_create(struct logger_ops *lops, void *private_data, struct logger *log);
void log_free(struct logger *log);

void log_debug(struct logger *log, const char *fmt, ...);
void log_info(struct logger *log, const char *fmt, ...);
void log_warn(struct logger *log, const char *fmt, ...);
void log_error(struct logger *log, const char *fmt, ...);


extern struct logger *logger;

void logger_set(struct logger *log);
void logger_unset(void);

#define LOG_DEBUG(fmt, ...) log_debug(logger, fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...) log_info(logger, fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...) log_warn(logger, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) log_error(logger, fmt, ##__VA_ARGS__)

#endif
