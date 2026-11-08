#pragma once

#include <bitset>
#include <cstdint>
#include <limits>
#include <utility>

namespace Wrum
{
    // Fixed array with versioned slots. Version increments every time a slot is reused.
    // Bitset tracks occupied slots.
    template <typename T, std::uint32_t Capacity>
    class StaticVersionedArray
    {
        static_assert(Capacity > 0, "StaticVersionedArray requires a nonzero capacity");

    public:
        struct Handle
        {
            u32 Index = Capacity;
            u32 Version = 0;

            bool IsValid() const { return Index < Capacity && Version != 0; }
        };

        // Versions start at 1 and advance on each successful reuse.
        [[nodiscard]] Handle Add(T value = T{})
        {
            for (u32 i = 0; i < Capacity; ++i)
            {
                if (_taken[i])
                {
                    continue;
                }
                
                // like this could ever happen
                ASSERT(_versions[i] != U32_MAX, "skibidi")

                _entries[i] = std::move(value);
                ++_versions[i];
                _taken.set(i);
                
                return {i, _versions[i]};
            }

            return {};
        }

        T* Get(u32 index, u32 version)
        {
            return IsValid(index, version) ? &_entries[index] : nullptr;
        }

        const T* Get(u32 index, u32 version) const
        {
            return IsValid(index, version) ? &_entries[index] : nullptr;
        }

        bool Remove(u32 index, u32 version)
        {
            if (!IsValid(index, version))
            {
                return false;
            }

            _taken.reset(index);
            return true;
        }

    private:
        bool IsValid(u32 index, u32 version) const
        {
            return index < Capacity && _taken[index] && _versions[index] == version;
        }

        T _entries[Capacity]{};
        std::bitset<Capacity> _taken{};
        u32 _versions[Capacity]{};
    };
}
