#include <stdio.h>
#include "log.h"

int main(void)
{
    struct logger *log = logger_new(NULL);
    logger_log(log, "Im working!\n");



    
    logger_free(log);
    return 0;
}