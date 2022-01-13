/*
   随机数
   
   A C-program for MT19937-64 (2004/9/29 version).
   Coded by Takuji Nishimura and Makoto Matsumoto.

   This is a 64-bit version of Mersenne Twister pseudorandom number
   generator.

   Before using, initialize the state by using init_genrand64(seed)
   or init_by_array64(init_key, key_length).
*/

#ifndef __MT19937_64_H
#define __MT19937_64_H

/* initializes mt[NN] with a seed */
void init_genrand64(unsigned long long seed);

/* initialize by an array with array-length */
/* init_key is the array for initializing keys */
/* key_length is its length */
void init_by_array64(unsigned long long init_key[],
                     unsigned long long key_length);

/* generates a random number on [0, 2^64-1]-interval */
unsigned long long genrand64_int64(void);


/* generates a random number on [0, 2^63-1]-interval */
long long genrand64_int63(void);

/* generates a random number on [0,1]-real-interval */
double genrand64_real1(void);

/* generates a random number on [0,1)-real-interval */
double genrand64_real2(void);

/* generates a random number on (0,1)-real-interval */
double genrand64_real3(void);

/* generates a random number on (0,1]-real-interval */
double genrand64_real4(void);

#endif
