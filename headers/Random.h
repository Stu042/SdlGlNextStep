//
// Created by stu on 31/07/23.
//

#ifndef OPENGLSDL_RANDOM_H
#define OPENGLSDL_RANDOM_H
#include "Std.h"



extern void RandomSeed(uint64 seed, uint64 seed2);

// return 0 <= value < max
extern uint64 RandomUint64(uint64 max);

// return 0 <= value < max
extern uint32 RandomUint32(uint32 max);

// return 0 <= value < max
extern uint16 RandomUint16(uint16 max);


// return -max < value < max
extern int64 RandomInt64(int64 max);

// return -max < value < max
extern int32 RandomInt32(int32 max);

// return -max < value < max
extern int16 RandomInt16(int16 max);

// return 0 <= value < max
extern uint URandom(uint max);

// return -max < value < max
extern int Random(int max);


#endif //OPENGLSDL_RANDOM_H
