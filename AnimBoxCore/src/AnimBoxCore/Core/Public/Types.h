#pragma once

#include "Assert.h"
#include <stdint.h>
#include <limits.h>
#include <stdio.h>

#define int8 int8_t
#define uint8 uint8_t

#define int16 int16_t
#define uint16 uint16_t

#define int32 int32_t
#define uint32 uint32_t

#define int64 int64_t
#define uint64 uint64_t

#define ufloat unsigned float

#define udouble unsigned double

static int16 SafeCast_int16(int i)
{
    ASSERT(i >= INT16_MIN && i <= INT16_MAX, "Failed to cast integer to int16")
    return static_cast<int16>(i);
}

static uint16 SafeCast_uint16(unsigned i)
{
    ASSERT(i <= UINT16_MAX, "Failed to cast integer to int16")
    return static_cast<uint16>(i);
}

static int SafeCast_int(uint32 i)
{
    ASSERT(i <= INT_MAX, "Failed to cast uint32 to int")
    return static_cast<int>(i);
}