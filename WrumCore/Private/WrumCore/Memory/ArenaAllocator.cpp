#include "PCH.h"
#include "WrumCore/Memory/ArenaAllocator.h"

Wrum::ArenaAllocator::ArenaAllocator(uint64 capacity)
{
    _buffer = static_cast<uint8_t*>(malloc(capacity));
    _capacity = capacity;
    _offset = 0;
}

void* Wrum::ArenaAllocator::Allocate(uint64 size, uint64 alignment)
{
    const uint8_t* currentPtr = (_buffer + _offset);

    const uint64 currentAddress = reinterpret_cast<uint64>(currentPtr);
    // round up the pointer to next multiple of alignment
    const uint64 alignedAddress = (currentAddress + alignment - 1) & ~(alignment - 1);

    const uint64 padding = alignedAddress - currentAddress;

    ASSERT(_offset + size + padding <= _capacity, "Arena Allocator overflow")

    _offset += padding;
    uint8* alignedPtr = _buffer + _offset;
    
    _offset += size;
    return alignedPtr;
}

void Wrum::ArenaAllocator::Reset()
{
    _offset = 0;
}

void Wrum::ArenaAllocator::Free()
{
    _capacity = 0;
    _offset = 0;
    free(_buffer);
}

Wrum::ArenaAllocator::~ArenaAllocator()
{
    free(_buffer);
}
