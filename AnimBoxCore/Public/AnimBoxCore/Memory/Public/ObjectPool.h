#pragma once

#include "PCH.h"

/*

#include <stack>
#include <type_traits>

namespace AnimBox
{
    class ArenaAllocator;

    class IPoolableObject
    {
    public:
        virtual ~IPoolableObject() = default;

        void GetFromPool()
        {
            // TODO: Set pool idx here, or straight from the pool
            GetFromPool_Internal();
        }

        void ReturnToPool()
        {
            ReturnToPool_Internal();
        }
        
        size_t GetIdxInPool() const;
    
    protected:
        virtual void GetFromPool_Internal() = 0;
        virtual void ReturnToPool_Internal() = 0;
        
    private:
        size_t _idxInPool {};

        friend class ObjectPool;
    };

    template <typename T, typename ... Args>
    class ObjectPool
    {
        static_assert(std::is_base_of_v<IPoolableObject, T>, "T should inherit from IPoolableObject");
        
    public:
        ObjectPool() = delete;
        ObjectPool(const ObjectPool&) = delete;
        
        ObjectPool(ArenaAllocator& arena, uint32_t count)
        {
            // TODO: reserve memory for stack first to avoid multiple allocs
            
            for (int32_t i = 0; i < count; ++i)
            {
                _objects.push(ArenaAllocator::New<T>(&arena));
                 _freeIdxs.push(i);
            }
        }

        T* GetFromPool()
        {
            ASSERT(!_freeIdxs.empty(), "Object pool exceeded max elements count")
            
            size_t idx = _freeIdxs.top();
            _objects.pop();

            T* obj = _objects.top();
            
            _freeIdxs.pop();
            return obj;
        }

        void ReturnToPool()
        {
            
        }

    private:
        std::stack<IPoolableObject*> _objects;
        std::stack<size_t> _freeIdxs;
    };
}
*/