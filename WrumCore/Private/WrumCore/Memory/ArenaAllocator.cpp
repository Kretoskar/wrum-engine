#include "PCH.h"
#include "WrumCore/Memory/ArenaAllocator.h"

Wrum::ArenaAllocator::ArenaAllocator(u64 capacity)
    : _buffer(static_cast<uint8_t*>(malloc(capacity))), _offset(0), _capacity(capacity)
{
    _id = _currID++;
    _objects[_id] = this;
}

Wrum::ArenaAllocator::ArenaAllocator(uint64_t capacity, HString tag)
    : ArenaAllocator(capacity)
{
    _tag = tag;
}

void* Wrum::ArenaAllocator::Allocate(u64 size, u64 alignment)
{
    const uint8_t* currentPtr = (_buffer + _offset);

    const u64 currentAddress = reinterpret_cast<u64>(currentPtr);
    // round up the pointer to next multiple of alignment
    const u64 alignedAddress = (currentAddress + alignment - 1) & ~(alignment - 1);

    const u64 padding = alignedAddress - currentAddress;

    ASSERT(_offset + size + padding <= _capacity, "Arena Allocator overflow")

    _offset += padding;
    u8* alignedPtr = _buffer + _offset;
    
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
    _objects.erase(_id);
    free(_buffer);
}
