#ifndef __LOG_H__
#define __LOG_H__


struct logger;


struct logger *logger_new(void *private_data);
void logger_free(struct logger *log);
void logger_log(struct logger *log, const char *fmt, ...);


#endif
