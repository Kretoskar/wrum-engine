#pragma once

namespace Wrum
{
    class FrameDiagnostics
    {
    public:
        static void GatherFrameStart();
        static void GatherFrameEnd();
        
        static inline double last = 0.0;
        static inline double min = 99999.0;
        static inline double max = -1.0;
        static inline double avg = -1.0;

        static inline double frameStart = 0.0;
    };
}