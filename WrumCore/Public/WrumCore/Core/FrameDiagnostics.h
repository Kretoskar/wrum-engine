#pragma once

namespace Wrum
{
    class FrameDiagnostics
    {
    public:
        static void GatherFrameStart();
        static void GatherFrameEnd();
        
        static inline f64 last = 0.0;
        static inline f64 min = 99999.0;
        static inline f64 max = -1.0;
        static inline f64 avg = -1.0;

        static inline f64 frameStart = 0.0;
    };
}