/* redisassert.h -- Drop in replacements assert.h that prints the stack trace
 *                  in the Redis logs.
 *
 * This file should be included instead of "assert.h" inside libraries used by
 * Redis that are using assertions, so instead of Redis disappearing with
 * SIGABORT, we get the details and stack trace inside the log file.
 *
 */

#ifndef __REDIS_ASSERT_H__
#define __REDIS_ASSERT_H__

#include "config.h"

#define assert(_e) (likely((_e))?(void)0 : (_serverAssert(#_e,__FILE__,__LINE__),redis_unreachable()))
#define panic(...) _serverPanic(__FILE__,__LINE__,__VA_ARGS__),redis_unreachable()

void _serverAssert(char *estr, char *file, int line);
void _serverPanic(const char *file, int line, const char *msg, ...);

#endif
