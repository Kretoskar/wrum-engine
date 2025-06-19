#pragma once

namespace AnimBox
{
    class ArenaAllocator
    {
    public:
        ArenaAllocator() = delete;
        ArenaAllocator(size_t capacity);
        ~ArenaAllocator();
        
        void* Allocate(size_t size, size_t alignment);
        void Reset();
        void Free();

        template<typename T, typename ... Args>
        static T* New(ArenaAllocator* arena, Args&&... args)
        {
            void* memory = arena->Allocate(sizeof(T), alignof(T));
            return new (memory) T(std::forward<Args>(args)...);
        }
    
        uint8_t* _buffer;
        size_t _offset;
        size_t _capacity;
    };
}