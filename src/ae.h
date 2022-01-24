/* 
 * 事件驱动
 */

#ifndef __AE_H__
#define __AE_H__

#include "monotonic.h"

#define AE_OK 0
#define AE_ERR -1

#define AE_NONE 0       /* No events registered. */
#define AE_READABLE 1   /* Fire when descriptor is readable. */
#define AE_WRITABLE 2   /* Fire when descriptor is writable. */
#define AE_BARRIER 4    /* With WRITABLE, never fire the event if the
                           READABLE event already fired in the same event
                           loop iteration. Useful when you want to persist
                           things to disk before sending replies, and want
                           to do that in a group fashion. */

#define AE_FILE_EVENTS (1<<0)
#define AE_TIME_EVENTS (1<<1)
#define AE_ALL_EVENTS (AE_FILE_EVENTS|AE_TIME_EVENTS)
#define AE_DONT_WAIT (1<<2)
#define AE_CALL_BEFORE_SLEEP (1<<3)
#define AE_CALL_AFTER_SLEEP (1<<4)

#define AE_NOMORE -1
#define AE_DELETED_EVENT_ID -1

/* Macros */
#define AE_NOTUSED(V) ((void) V)

struct aeEventLoop;

/* Types and data structures */
typedef void aeFileProc(struct aeEventLoop *eventLoop, int fd, void *clientData, int mask);
typedef int aeTimeProc(struct aeEventLoop *eventLoop, long long id, void *clientData);
typedef void aeEventFinalizerProc(struct aeEventLoop *eventLoop, void *clientData);
typedef void aeBeforeSleepProc(struct aeEventLoop *eventLoop);

// IO事件
/* File event structure */
typedef struct aeFileEvent {
    int mask; /* one of AE_(READABLE|WRITABLE|BARRIER) */   //事件类型的掩码
    aeFileProc *rfileProc;                                  //AE_READABLE的handler
    aeFileProc *wfileProc;                                  //AE_WRITABLE的handler
    void *clientData;                                       //client私有数据
} aeFileEvent;

// 定时事件
/* Time event structure */
typedef struct aeTimeEvent {
    long long id; /* time event identifier. */                           //事件事件id
    monotime when;                                                       //事件单调时钟的时刻
    aeTimeProc *timeProc;                                                //定时事件handler
    aeEventFinalizerProc *finalizerProc;                                 //事件类型的掩码
    void *clientData;                                                    //client私有数据
    struct aeTimeEvent *prev;                                            //上一个事件
    struct aeTimeEvent *next;                                            //下一个事件
    int refcount; /* refcount to prevent timer events from being         //应用计数
  		   * freed in recursive time event calls. */
} aeTimeEvent;

//已触发的事件
/* A fired event */
typedef struct aeFiredEvent {
    int fd;
    int mask;
} aeFiredEvent;

// 消息循环
/* State of an event based program */
typedef struct aeEventLoop {
    int maxfd;   /* highest file descriptor currently registered */      //当前最大fd
    int setsize; /* max number of file descriptors tracked */            //fd最大允许数量
    long long timeEventNextId;                                           //下一个消息id
    aeFileEvent *events; /* Registered events */                         //IO事件事件数组
    aeFiredEvent *fired; /* Fired events */                              //已触发事件数组
    aeTimeEvent *timeEventHead;                                          //时间事件
    int stop;
    void *apidata; /* This is used for polling API specific data */      //和API调用接口相关的数据
    aeBeforeSleepProc *beforesleep;                                      //进入事件循环流程前执行的函数
    aeBeforeSleepProc *aftersleep;                                       //退出事件循环流程后执行的函数
    int flags;
} aeEventLoop;

/* Prototypes */
aeEventLoop *aeCreateEventLoop(int setsize);
void aeDeleteEventLoop(aeEventLoop *eventLoop);
void aeStop(aeEventLoop *eventLoop);
int aeCreateFileEvent(aeEventLoop *eventLoop, int fd, int mask,
        aeFileProc *proc, void *clientData);
void aeDeleteFileEvent(aeEventLoop *eventLoop, int fd, int mask);
int aeGetFileEvents(aeEventLoop *eventLoop, int fd);
long long aeCreateTimeEvent(aeEventLoop *eventLoop, long long milliseconds,
        aeTimeProc *proc, void *clientData,
        aeEventFinalizerProc *finalizerProc);
int aeDeleteTimeEvent(aeEventLoop *eventLoop, long long id);
int aeProcessEvents(aeEventLoop *eventLoop, int flags);
int aeWait(int fd, int mask, long long milliseconds);
void aeMain(aeEventLoop *eventLoop);
char *aeGetApiName(void);
void aeSetBeforeSleepProc(aeEventLoop *eventLoop, aeBeforeSleepProc *beforesleep);
void aeSetAfterSleepProc(aeEventLoop *eventLoop, aeBeforeSleepProc *aftersleep);
int aeGetSetSize(aeEventLoop *eventLoop);
int aeResizeSetSize(aeEventLoop *eventLoop, int setsize);
void aeSetDontWait(aeEventLoop *eventLoop, int noWait);

#endif
