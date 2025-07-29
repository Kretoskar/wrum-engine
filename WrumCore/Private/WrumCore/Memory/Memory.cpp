#include "PCH.h"

#include "WrumCore/Memory/Memory.h"
#include "WrumCore/Core/Logger.h"

void Wrum::AllocationMetrics::LogAllocationMetrics() const
{
    LOG_MESSAGE("Memory usage: %u bytes. Allocated: %u, freed: %u", 
        GetCurrentUsage(), TotalAllocated, TotalFreed)
}

void* operator new(uint64 size)
{
#ifdef AB_DEBUG
    Wrum::AllocationMetrics::GetHeapAllocationMetrics().TotalAllocated += size;
#endif
    
    return malloc(size);
}

void operator delete(void* memory, uint64 size)
{
#ifdef AB_DEBUG
    Wrum::AllocationMetrics::GetHeapAllocationMetrics().TotalFreed += size;
#endif
    
    free(memory);
}