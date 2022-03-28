/* 
 * 慢日志
 *
 * Slowlog implements a system that is able to remember the latest N
 * queries that took more than M microseconds to execute.
 *
 * The execution time to reach to be logged in the slow log is set
 * using the 'slowlog-log-slower-than' config directive, that is also
 * readable and writable using the CONFIG SET/GET command.
 *
 * The slow queries log is actually not "logged" in the Redis log file
 * but is accessible thanks to the SLOWLOG command.
 *
 */

#ifndef __SLOWLOG_H__
#define __SLOWLOG_H__

#define SLOWLOG_ENTRY_MAX_ARGC 32
#define SLOWLOG_ENTRY_MAX_STRING 128

/* This structure defines an entry inside the slow log list */
typedef struct slowlogEntry {
    robj **argv;                                                            //日志项对应的命令及参数
    int argc;                                                               //日志项对应的参数个数
    long long id;       /* Unique entry identifier. */                      //日志项的唯一ID
    long long duration; /* Time spent by the query, in microseconds. */     //日志项对应命令的执行时长（以微秒为单位）
    time_t time;        /* Unix time at which the query was executed. */    //日志项对应命令的执行时间戳
    sds cname;          /* Client name. */                                  //日志项对应命令的发送客户端名称
    sds peerid;         /* Client network address. */                       //日志项对应命令的发送客户端网络地址
} slowlogEntry;

/* Exported API */
void slowlogInit(void);
void slowlogPushEntryIfNeeded(client *c, robj **argv, int argc, long long duration);

/* Exported commands */
void slowlogCommand(client *c);

#endif /* __SLOWLOG_H__ */
