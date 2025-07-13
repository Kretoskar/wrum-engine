#include "PCH.h"

#include "AnimBoxCore/Memory/Memory.h"
#include "AnimBoxCore/Core/Logger.h"

void AnimBox::AllocationMetrics::LogAllocationMetrics() const
{
    LOG_MESSAGE("Memory usage: %u bytes. Allocated: %u, freed: %u", 
        GetCurrentUsage(), TotalAllocated, TotalFreed)
}

void* operator new(uint64 size)
{
#ifdef AB_DEBUG
    AnimBox::AllocationMetrics::GetHeapAllocationMetrics().TotalAllocated += size;
#endif
    
    return malloc(size);
}

void operator delete(void* memory, uint64 size)
{
#ifdef AB_DEBUG
    AnimBox::AllocationMetrics::GetHeapAllocationMetrics().TotalFreed += size;
#endif
    
    free(memory);
}