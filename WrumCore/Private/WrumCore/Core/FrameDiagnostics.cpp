#include "PCH.h"

#include "WrumCore/Core/FrameDiagnostics.h"

#include "WrumCore/Core/Time.h"

namespace Wrum
{
    void FrameDiagnostics::GatherFrameStart()
    {
        frameStart = Time::Convert(Time::GetCurrentTimeMicroSec(), TimeUnit::Microseconds, TimeUnit::Milliseconds); 
    }

    void FrameDiagnostics::GatherFrameEnd()
    {
        double frameEnd = Time::Convert(Time::GetCurrentTimeMicroSec(), TimeUnit::Microseconds, TimeUnit::Milliseconds);

        last = frameEnd - frameStart;
        min = last < min ? last : min;
        max = last > max ? last : max;
        double n = Time::GetFrame();
        
        avg = avg * (n-1)/n + last /n;
    }
}
