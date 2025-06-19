#include "PCH.h"
#include "AnimBoxCore/Memory/Public/ArenaAllocator.h"

AnimBox::ArenaAllocator::ArenaAllocator(size_t capacity)
{
    _buffer = static_cast<uint8_t*>(malloc(capacity));
    _capacity = capacity;
    _offset = 0;
}

void* AnimBox::ArenaAllocator::Allocate(size_t size, size_t alignment)
{
    const uint8_t* currentPtr = (_buffer + _offset);

    const size_t currentAddress = reinterpret_cast<size_t>(currentPtr);
    // round up the pointer to next multiple of alignment
    const size_t alignedAddress = (currentAddress + alignment - 1) & ~(alignment - 1);

    const size_t padding = alignedAddress - currentAddress;

    ASSERT(_offset + size + padding <= _capacity, "Arena Allocator overflow")

    _offset += padding;
    uint8_t* alignedPtr = _buffer + _offset;
    
    _offset += size;
    return alignedPtr;
}

void AnimBox::ArenaAllocator::Reset()
{
    _offset = 0;
}

void AnimBox::ArenaAllocator::Free()
{
    _capacity = 0;
    _offset = 0;
    free(_buffer);
}

AnimBox::ArenaAllocator::~ArenaAllocator()
{
    free(_buffer);
}
