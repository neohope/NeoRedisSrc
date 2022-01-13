/* 
 * 后台IO线程
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
#define BIO_CLOSE_FILE    0 /* Deferred close(2) syscall. */    //后台线程关闭文件fd
#define BIO_AOF_FSYNC     1 /* Deferred AOF fsync. */           //后台线程执行AOF文件的定期fsync
#define BIO_LAZY_FREE     2 /* Deferred objects freeing. */     //后台线程释放指定内存，调用指定函数释放指定对象，包括lazyfreeFreeObject、lazyfreeFreeDatabase、lazyfreeFreeDatabase、lazyFreeTrackingTable、lazyFreeLuaScripts等
#define BIO_NUM_OPS       3

#endif
