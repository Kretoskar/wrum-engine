#pragma once

#include "AnimBoxCore/Core/Public/Types.h"

namespace AnimBox
{
    class ArenaAllocator
    {
    public:
        ArenaAllocator() = delete;
        ArenaAllocator(uint64 capacity);
        ~ArenaAllocator();
        
        void* Allocate(uint64 size, uint64 alignment);
        void Reset();
        void Free();

        template<typename T, typename ... Args>
        static T* New(ArenaAllocator& arena, Args&&... args)
        {
            void* memory = arena.Allocate(sizeof(T), alignof(T));
            return new (memory) T(std::forward<Args>(args)...);
        }
    
        uint8* _buffer;
        uint64 _offset;
        uint64 _capacity;
    };
}