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

#define MAKE_TAG32(a, b, c, d) u32(u32(a) | u32(b) << 8 | u32(c) << 16 | u32(d) << 24)
union Tag32String
{
    char str[5] = {0};
    u32 tag;

    Tag32String(const char* s, u32 length)
    {
        length = length > 5 ? 5 : length;
        for (u32 i = 0; i < length; ++i)
            str[i] = s[i];
    }
    
    Tag32String(u32 t)
    {
        tag = t;
        str[4] = 0;
    }
};

#define BIT_KILO_BYTE(x) (x << 10)
#define BIT_MEGA_BYTE(x) (x << 20)
#define BIT_GIGA_BYTE(x) ((size_t)(x) << 30)

#if defined(_MSC_VER)
    #define FORCE_INLINE __forceinline
#elif defined(__GNUC__) || defined(__clang__)
    #define FORCE_INLINE inline __attribute__((always_inline))
#else
    #define FORCE_INLINE inline
#endif