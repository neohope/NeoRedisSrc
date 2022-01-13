/*
 * 后台IO线
 */

#ifndef __BIO_H
#define __BIO_H

typedef void lazy_free_fn(void *args[]);

/* Exported API */
void bioInit(void);
unsigned long long bioPendingJobsOfType(int type);
unsigned long long bioWaitStepOfType(int type);
time_t bioOlderJobOfType(int type);
void bioKillThreads(void);
void bioCreateCloseJob(int fd);
void bioCreateFsyncJob(int fd);
void bioCreateLazyFreeJob(lazy_free_fn free_fn, int arg_count, ...);

/* Background job opcodes */
#define BIO_CLOSE_FILE    0 /* Deferred close(2) syscall. */
#define BIO_AOF_FSYNC     1 /* Deferred AOF fsync. */
#define BIO_LAZY_FREE     2 /* Deferred objects freeing. */
#define BIO_NUM_OPS       3

#endif
