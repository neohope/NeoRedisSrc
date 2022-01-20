NeoRedisSrc
=========
NeoRedisSrc is a practing project which is based on Redis6.2

how-to-build
============
make

how-to-run
============
make and run

source files
=========

数据结构：
- 字符串（t_string.c、sds.c、sdsalloc.h）
- 链表（t_list.c、ziplist.c）
- 双向链表（adlist.c、quicklist.c）
- 压缩链表（ziplist.c、quicklist.c、listpack.c）
- 哈希表（t_hash.c、ziplist.c、dict.c、zipmap.c）
- 集合（t_set.c、intset.c）
- 有序集合（t_zset.c、ziplist.c、dict.c）
- 位运算（bitops.c）
- 基数树（rax.c）
- 访问统计HyperLogLog（hyperloglog.c）【比如当日访问IP数统计】
- 经纬度（geo.c、geohash.c、geohash_helper.c）
- 消息队列（t_stream.c、rax.c、listpack.c）
- Redis对象（object.c）

算法：
- 排序（Sort.c、pqsort.c）
- 哈希（spihash.c）
- SHA（sha1.c、sha256.c）
- CRC（crc16.c、crc16_slottable.h、crc64.c、crcspeed.c）
- 随机数（rand.c、mt19937-64.c）
- 压缩（lzf_c.c、lzf_d.c、lzf_h.c）
- 微线图（sparkline.c）

全局功能：
- Server入口（server.c、anet.c）
- 命令入口(server.h)
- CLI（cli-common.c、reids-cli.c、help.h、setproctitle.c）
- 事件驱动（ae.c、ae_epoll.c、ae_kqueue.c、ae_evport.c、ae_select.c、networking.c）
- 事务（multi.c）
- 时钟管理（单调时钟monotonic.c、本地时钟localtime.c）
- 权限管理（acl.c）
- 配置管理（config.c）
- 模块管理（module.c）
- 客户端缓存支持（tracking.c）

内存与CPU：
- 内存分配（zmalloc.c）
- 内存回收（expire.c、lazyfree.c）
- 内存碎片整理（defrag.c）
- 大小端转换（endinconv.c）
- 内存配额（evict.c）
- 原子操作（atomicvar.h）
- CPU绑核（setcpuaffinity.c）

IO与网络：
- IO（syncio.c、rio.c）
- 后台IO线程（bio.c）
- DB API（db.c）
- 阻塞操作（blocked.c）
- 传输管理（anet.c、networking.c、connection.c、connhelpers.h、gopher.c、tls.c、timeout.c）

高可用与集群：
- 内存快照RDB（rdb.c、redis-check-rdb.c)
- AOF日志（aof.c、redis-check-aof.c）
- 主从复制（replication.c）
- 订阅发布PubSub（pubsub.c）
- 集群（cluster.c）
- 哨兵（sentinel.c）

辅助功能：
- 延迟统计（latency.c）
- 慢日志（slowlog.c）
- 通知（notify.c）
- 基准性能（redis-benchmark.c）
- 调试工具（memtest.c、testhelper.c、redisassert.h、debug.c、debugmacro.h）
