#include "PCH.h"
#include "AnimBoxCore/Memory/Public/ArenaAllocator.h"

AnimBox::ArenaAllocator::ArenaAllocator(size_t capacity)
{
    _buffer = static_cast<uint8_t*>(malloc(capacity));
    _capacity = capacity;
    _offset = 0;
}

void* AnimBox::ArenaAllocator::Allocate(size_t size)
{
    ASSERT(_offset + size < _capacity, "Arena Allocator overflow")
    uint8_t* data = _buffer + _offset;
    _offset += size;
    return data;
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
