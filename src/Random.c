//
// Created by stu on 31/07/23.
//
#include <bits/stdint-uintn.h>
#include <stdio.h>
#include "Std.h"
#include <limits.h>
#include "Random.h"


typedef struct {
	uint64 s;
} SplitMix64State;


uint64 splitMix64(SplitMix64State* state) {
	uint64_t result = (state->s += 0x9E3779B97f4A7C15);
	result = (result ^ (result >> 30)) * 0xBF58476D1CE4E5B9;
	result = (result ^ (result >> 27)) * 0x94D049BB133111EB;
	return result ^ (result >> 31);
}


typedef struct {
	uint32 x[4];
} XorShift128State;


// one could do the same for any of the other generators.
void xorShift128Init(const uint64 seed, XorShift128State* outState) {
	SplitMix64State smState = {seed};
	uint64 tmp = splitMix64(&smState);
	outState->x[0] = (uint32)tmp;
	outState->x[1] = (uint32)(tmp >> 32);
	tmp = splitMix64(&smState);
	outState->x[2] = (uint32)tmp;
	outState->x[3] = (uint32)(tmp >> 32);
}


uint64 rol64(const uint64 x, const int k) {
	return (x << k) | (x >> (64 - k));
}

typedef struct {
	uint64 s[4];
} XoShiro256ssState;

uint64 xoShiro256ss(XoShiro256ssState* state) {
	uint64* s = state->s;
	uint64 const result = rol64(s[1] * 5, 7) * 9;
	uint64 const t = s[1] << 17;
	s[2] ^= s[0];
	s[3] ^= s[1];
	s[1] ^= s[2];
	s[0] ^= s[3];
	s[2] ^= t;
	s[3] = rol64(s[3], 45);
	return result;
}

XoShiro256ssState globalRndState;

void RandomSeed(uint64 seed, uint64 seed2) {
	if (seed == 0 && seed2 == 0) {
		seed = 3782560128497;
		seed2 = 178260123457;
	}
	XorShift128State initSeed;
	xorShift128Init(seed, &initSeed);
	XorShift128State initSeed2;
	xorShift128Init(seed2, &initSeed2);
	globalRndState.s[0] = (uint64)initSeed.x[0] | (uint64)initSeed.x[1] << 32;
	globalRndState.s[1] = (uint64)initSeed.x[2] | (uint64)initSeed.x[3] << 32;
	globalRndState.s[2] = (uint64)initSeed2.x[0] | (uint64)initSeed2.x[1] << 32;
	globalRndState.s[3] = (uint64)initSeed2.x[2] | (uint64)initSeed2.x[3] << 32;
}


uint64 RandomUint64(uint64 max) {
	const uint64 rnd = xoShiro256ss(&globalRndState);
	const uint64 rangedRnd = rnd % max;
	return rangedRnd;
}

uint32 RandomUint32(uint32 max) {
	const uint32 rnd = (uint32)(xoShiro256ss(&globalRndState) >> 32);
	const uint32 rangedRnd = rnd % max;
	return rangedRnd;
}

uint16 RandomUint16(uint16 max) {
	const uint16 rnd = (uint16)(xoShiro256ss(&globalRndState) >> 48);
	const uint16 rangedRnd = rnd % max;
	return rangedRnd;
}


int64 RandomInt64(int64 max) {
	const int64 rnd = (int64)xoShiro256ss(&globalRndState);
	const int64 rangedRnd = rnd % max;
	return rangedRnd;
}

int32 RandomInt32(int32 max) {
	const int32 rnd = (int32)(xoShiro256ss(&globalRndState) >> 32);
	const int32 rangedRnd = rnd % max;
	return rangedRnd;
}

int16 RandomInt16(const int16 max) {
	const int16 rnd = (int16)(xoShiro256ss(&globalRndState) >> 48);
	const int16 rangedRnd = (int16)(rnd % max);
	return rangedRnd;
}


uint URandom(uint max) {
#if UINT_MAX == 65535
	return RandomUint16(max);
#elif UINT_MAX == 4294967295
	return RandomUint32(max);
#else
	return RandomUint64(max);
#endif
}


int Random(int max) {
#if UINT_MAX == 65535
	return RandomInt16(max);
#elif UINT_MAX == 4294967295
	return RandomInt32(max);
#else
	return RandomInt64(max);
#endif
}
