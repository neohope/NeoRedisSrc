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
    robj **argv;
    int argc;
    long long id;       /* Unique entry identifier. */
    long long duration; /* Time spent by the query, in microseconds. */
    time_t time;        /* Unix time at which the query was executed. */
    sds cname;          /* Client name. */
    sds peerid;         /* Client network address. */
} slowlogEntry;

/* Exported API */
void slowlogInit(void);
void slowlogPushEntryIfNeeded(client *c, robj **argv, int argc, long long duration);

/* Exported commands */
void slowlogCommand(client *c);

#endif /* __SLOWLOG_H__ */
