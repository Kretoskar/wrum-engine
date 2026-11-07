#pragma once

#include <map>

#include "WrumCore/Core/Types.h"

namespace Wrum
{
    class ArenaAllocator
    {
    public:
        ArenaAllocator() = delete;
        ArenaAllocator(u64 capacity);
        ArenaAllocator(const ArenaAllocator& a) = delete;
        
#ifdef AB_DEBUG
        ArenaAllocator(u64 capacity, HString tag);
#endif
        ~ArenaAllocator();
        
        void* Allocate(u64 size, u64 alignment);
        void Reset();
        void Free();

#ifdef AB_DEBUG
    private:
        HString _tag;
    public:
        HString GetTag() const { return _tag; }

        static std::map<int, ArenaAllocator*>& GetMapOfObjects()
        {
            return _objects;
        }
#endif
        
        template<typename T, typename ... Args>
        static T* New(ArenaAllocator& arena, Args&&... args)
        {
            void* memory = arena.Allocate(sizeof(T), alignof(T));
            return new (memory) T(std::forward<Args>(args)...);
        }

        template<typename T, typename ... Args>
        static T* NewArray(ArenaAllocator& arena, size_t count, Args&&... args)
        {
            void* memory = arena.Allocate(sizeof(T) * count, alignof(T));
            T* array = static_cast<T*>(memory);
            
            for (size_t i = 0; i < count; ++i)
            {
                new (&array[i]) T(std::forward<Args>(args)...);
            }

            return array;
        }

        // for built-in types
        template<typename T, typename ... Args>
        static T* NewArrayBuiltIn(ArenaAllocator& arena, size_t count)
        {
            void* memory = arena.Allocate(sizeof(T) * count, alignof(T));
            T* array = static_cast<T*>(memory);
            
            for (size_t i = 0; i < count; ++i)
            {
                new (&array[i]) T;
            }

            return array;
        }

        u64 GetOffset() const { return _offset; }
        u64 GetCapacity() const { return _capacity; }
        
    private:
        static inline i32 _currID;  
        static inline std::map<i32, ArenaAllocator*> _objects;
        i32 _id;
        
        u8* _buffer;
        u64 _offset;
        u64 _capacity;
    };
}