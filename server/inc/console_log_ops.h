#ifndef __CONSOLE_LOG_OPS_H__
#define __CONSOLE_LOG_OPS_H__

#include <stdio.h>
#include "log.h"

extern struct logger_ops console_log_ops;

struct console_log_data
{
    FILE *out;
};

#endif
