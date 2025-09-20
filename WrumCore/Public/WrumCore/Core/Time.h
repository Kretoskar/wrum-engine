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
    public:
        static double GetCurrentTimeMicroSec()
        {
            LARGE_INTEGER freq, counter;
            QueryPerformanceFrequency(&freq);
            QueryPerformanceCounter(&counter);
            return (counter.QuadPart * 1000000LL) / freq.QuadPart;
        }
        
    private:
        static inline const double ProgramStartTime = GetCurrentTimeMicroSec();
        static inline double ProgramCurrentTime = ProgramStartTime;
        static inline unsigned long long Frame = 0;
        
    public:
        
        static unsigned long long GetFrame() { return Frame; }
        
        static void Update()
        {
            Frame++;
            ProgramCurrentTime = GetCurrentTimeMicroSec();
        }
        
        static double TimeSinceProgramStart(TimeUnit unit)
        {
            double timeMicroS = ProgramCurrentTime - ProgramStartTime;
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

        static double Convert(double num, TimeUnit from, TimeUnit to)
        {
            // TODO: do it smarter
            
            double microSTime = num;
            switch (from)
            {
                case TimeUnit::Microseconds:
                    break;
                case TimeUnit::Milliseconds:
                    microSTime *= 1000.0;
                    break;
                case TimeUnit::Seconds:
                    microSTime *= 1000000.0;
                    break;
                default:
                    ASSERT_NO_ENTRY()
            }

            switch (to)
            {
                case TimeUnit::Microseconds:
                    return microSTime;
                case TimeUnit::Milliseconds:
                    microSTime /= 1000.0;
                    return microSTime;
                case TimeUnit::Seconds:
                    microSTime /= 1000000.0;
                    return microSTime;
                default:
                    ASSERT_NO_ENTRY()
            }
        }
    };
}
