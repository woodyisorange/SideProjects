#pragma once

#define static_assert _Static_assert

#define NULL 0

typedef signed char int8;
typedef signed short int16;
typedef signed int int32;
typedef signed long int64;

static_assert(sizeof(int8) == 1, "Bad width");
static_assert(sizeof(int16) == 2, "Bad width");
static_assert(sizeof(int32) == 4, "Bad width");
static_assert(sizeof(int64) == 8, "Bad width");

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long uint64;

static_assert(sizeof(uint8) == 1, "Bad width");
static_assert(sizeof(uint16) == 2, "Bad width");
static_assert(sizeof(uint32) == 4, "Bad width");
static_assert(sizeof(uint64) == 8, "Bad width");

typedef float float32;
typedef double float64;

static_assert(sizeof(float32) == 4, "Bad width");
static_assert(sizeof(float64) == 8, "Bad width");

typedef uint8 bool8;
#define TRUE 1
#define FALSE 0

