#pragma once

#include <stdio.h>
#include <windows.h>

namespace Wrum
{
    enum class TimeUnit : uint8
    {
        Microseconds,
        Milliseconds,
        Seconds,
    };
    
    class Time
    {
        static double GetCurrentTimeMicroSec() {
            LARGE_INTEGER freq, counter;
            QueryPerformanceFrequency(&freq);
            QueryPerformanceCounter(&counter);
            return (counter.QuadPart * 1000000LL) / freq.QuadPart;
        }
        
        static inline const ULONGLONG ProgramStartTime = GetCurrentTimeMicroSec();

    public:
        static double TimeSinceProgramStart(TimeUnit unit)
        {
            double timeMicroS = GetCurrentTimeMicroSec() - SafeCast_double(ProgramStartTime);
            switch (unit)
            {
                case TimeUnit::Microseconds:
                    return timeMicroS;
                case TimeUnit::Milliseconds:
                    return timeMicroS / 1000.0;
                case TimeUnit::Seconds:
                    return timeMicroS / 1000000.0;
                default:
                    ASSERT_NO_ENTRY()
            }
            
            return 0.0;
        }
    };
}
