#pragma once

#include <cstdint>
#include "WrumCore/Core/Types.h"

namespace Wrum
{
    struct AllocationMetrics
    {
        uint32 TotalAllocated = 0;
        uint32 TotalFreed = 0;

        void LogAllocationMetrics() const;
        uint32 GetCurrentUsage() const { return TotalAllocated - TotalFreed; }

        static AllocationMetrics& GetHeapAllocationMetrics()
        {
            static AllocationMetrics heapAllocationMetrics;
            return heapAllocationMetrics;
        }
    };
}

void* operator new(uint64 size);
void operator delete(void* memory, uint64 size);