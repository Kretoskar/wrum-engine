#pragma once

#include "WrumCore/Core/Types.h"

namespace Wrum
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

        template<typename T>
        static T* NewArray(ArenaAllocator& arena, size_t count)
        {
            void* memory = arena.Allocate(sizeof(T) * count, alignof(T));
            T* array = static_cast<T*>(memory);
            
            for (size_t i = 0; i < count; ++i)
            {
                new (&array[i]) T();
            }

            return array;
        }
    
        uint8* _buffer;
        uint64 _offset;
        uint64 _capacity;
    };
}