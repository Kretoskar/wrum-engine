#pragma once

#include <cstdint>

namespace AnimBox
{
    struct AllocationMetrics
    {
        uint32_t TotalAllocated = 0;
        uint32_t TotalFreed = 0;

        void LogAllocationMetrics() const;
        uint32_t GetCurrentUsage() const { return TotalAllocated - TotalFreed; }

        static AllocationMetrics& GetHeapAllocationMetrics()
        {
            static AllocationMetrics heapAllocationMetrics;
            return heapAllocationMetrics;
        }
    };
}

void* operator new(size_t size);
void operator delete(void* memory, size_t size);