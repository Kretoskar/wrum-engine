#pragma once

#include <cstdint>
#include "WrumCore/Core/Types.h"

namespace Wrum
{
    struct AllocationMetrics
    {
        u32 TotalAllocated = 0;
        u32 TotalFreed = 0;

        void LogAllocationMetrics() const;
        u32 GetCurrentUsage() const { return TotalAllocated - TotalFreed; }

        static AllocationMetrics& GetHeapAllocationMetrics()
        {
            static AllocationMetrics heapAllocationMetrics;
            return heapAllocationMetrics;
        }
    };
}

void* operator new(u64 size);
void operator delete(void* memory, u64 size);