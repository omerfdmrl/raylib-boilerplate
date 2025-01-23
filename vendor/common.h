#ifndef COMMON_H

#define COMMON_H

#include "./utils/assert.h"
#include "./utils/logger.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char uint8;
typedef unsigned short int uint16;
typedef unsigned int uint32;
typedef unsigned long long int uint64;

typedef signed char int8;
typedef signed short int int16;
typedef signed int int32;
typedef signed long long int int64;

#define MALLOC(size) malloc(size)
#define FREE(ptr) free(ptr)
#define REALLOC(ptr, size) realloc(ptr, size)

#endif // !COMMON_H
