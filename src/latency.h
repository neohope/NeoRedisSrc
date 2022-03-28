/* 
 * 延迟统计
 * The latency monitor allows to easily observe the sources of latency
 * in a Redis instance using the LATENCY command. Different latency
 * sources are monitored, like disk I/O, execution of commands, fork
 * system call, and so forth.
 *
 */

#ifndef __LATENCY_H
#define __LATENCY_H

#define LATENCY_TS_LEN 160 /* History length for every monitored event. */

/* Representation of a latency sample: the sampling time and the latency
 * observed in milliseconds. */
struct latencySample {
    int32_t time; /* We don't use time_t to force 4 bytes usage everywhere. */            //事件的采样时间
    uint32_t latency; /* Latency in milliseconds. */                                      //事件的执行时长（以毫秒为单位）
};

/* The latency time series for a given event. */
struct latencyTimeSeries {
    int idx; /* Index of the next sample to store. */                                     //采样事件数组的写入位置
    uint32_t max; /* Max latency observed for this event. */                              //当前事件的最大延迟
    struct latencySample samples[LATENCY_TS_LEN]; /* Latest history. */                   //采样事件数组，记录LATENCY_TS_LEN个采样结果，LATENCY_TS_LEN默认为160};
};

/* Latency statistics structure. */
struct latencyStats {
    uint32_t all_time_high; /* Absolute max observed since latest reset. */
    uint32_t avg;           /* Average of current samples. */
    uint32_t min;           /* Min of current samples. */
    uint32_t max;           /* Max of current samples. */
    uint32_t mad;           /* Mean absolute deviation. */
    uint32_t samples;       /* Number of non-zero samples. */
    time_t period;          /* Number of seconds since first event and now. */
};

void latencyMonitorInit(void);
void latencyAddSample(const char *event, mstime_t latency);
int THPIsEnabled(void);
int THPDisable(void);

/* Latency monitoring macros. */

/* Start monitoring an event. We just set the current time. */
#define latencyStartMonitor(var) if (server.latency_monitor_threshold) { \
    var = mstime(); \
} else { \
    var = 0; \
}

/* End monitoring an event, compute the difference with the current time
 * to check the amount of time elapsed. */
#define latencyEndMonitor(var) if (server.latency_monitor_threshold) { \
    var = mstime() - var; \
}

/* Add the sample only if the elapsed time is >= to the configured threshold. */
#define latencyAddSampleIfNeeded(event,var) \
    if (server.latency_monitor_threshold && \
        (var) >= server.latency_monitor_threshold) \
          latencyAddSample((event),(var));

/* Remove time from a nested event. */
#define latencyRemoveNestedEvent(event_var,nested_var) \
    event_var += nested_var;

#endif /* __LATENCY_H */
