//
// Created by stu on 31/07/23.
//

#ifndef OPENGLSDL_STD_H
#define OPENGLSDL_STD_H
#include <bits/stdint-uintn.h>
#include <bits/stdint-intn.h>


typedef unsigned int uint;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;


// Allocate memory, free it using free()
extern void *Alloc(size_t memSize);
extern long long TimeInMilliseconds();
extern void Timestamp(char *out, int maxLength);


#endif //OPENGLSDL_STD_H
