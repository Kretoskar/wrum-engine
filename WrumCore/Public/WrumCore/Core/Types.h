#pragma once

#include "Assert.h"
#include <stdint.h>
#include <limits.h>
#include <stdio.h>

#define i8 int8_t
#define u8 uint8_t

#define i16 int16_t
#define u16 uint16_t

#define i32 int32_t
#define u32 uint32_t

#define i64 int64_t
#define u64 uint64_t

#define uf32 unsigned float

#define uf64 unsigned double

#define f32 float
#define f64 double

static i16 SafeCast_int16(int i)
{
    ASSERT(i >= INT16_MIN && i <= INT16_MAX, "Failed to cast integer to int16")
    return static_cast<i16>(i);
}

static u16 SafeCast_uint16(unsigned i)
{
    ASSERT(i <= UINT16_MAX, "Failed to cast integer to int16")
    return static_cast<u16>(i);
}

static int SafeCast_int(u32 i)
{
    ASSERT(i <= INT_MAX, "Failed to cast uint32 to int")
    return static_cast<int>(i);
}

static double SafeCast_double(unsigned long long i)
{
    ASSERT(i <= DBL_MAX, "Failed to cast unsigned long long to uint")
    return static_cast<double>(i);
}