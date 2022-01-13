/* 
 * 随机数
 *
 * Pseudo random number generation functions derived from the drand48()
 * function obtained from pysam source code.
 *
 * This functions are used in order to replace the default math.random()
 * Lua implementation with something having exactly the same behavior
 * across different systems (by default Lua uses libc's rand() that is not
 * required to implement a specific PRNG generating the same sequence
 * in different systems if seeded with the same integer).
 *
 * The original code appears to be under the public domain.
 * I modified it removing the non needed functions and all the
 * 1960-style C coding stuff...
 *
 */

#ifndef REDIS_RANDOM_H
#define REDIS_RANDOM_H

int32_t redisLrand48();
void redisSrand48(int32_t seedval);

#define REDIS_LRAND48_MAX INT32_MAX

#endif
