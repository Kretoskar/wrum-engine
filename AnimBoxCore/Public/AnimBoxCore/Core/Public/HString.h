#pragma once

#include <string>
#include "AnimBoxCore/Core/Public/Types.h"

namespace AnimBox
{
    class HString
    {
    public:
        HString()
            : _hash(hashTableSize + 1) {}

        HString(const char* s)
            : _hash(Hash(s)) {}

        HString(std::string s)
            : _hash(Hash(s.c_str())) {}

        [[nodiscard]]
        uint32 GetHash() const { return _hash; }

        static HString None;

    private:
        uint32 _hash {};

    public:
        [[nodiscard]]
        const char* Get() const
        {
            return hashTable[_hash];
        }

    private:
        // hash using prime numbers
        static constexpr uint32 Hash(const char* s)
        {
            uint32 h = 37;
            uint32 size = 0;

            while (*s)
            {
                h = (h * 54059) ^ (s[0] * 76963);
                size++;
                s++;
            }

            h %= hashTableSize;

            s = s - size;

#ifdef AB_DEBUG
            // Check for hash conflicts
            if (hashTable[h][0] != '\0')
            {
                for (uint32 i = 0; i < hashTableMaxStringLength; i++)
                {
                    const char existingChar = hashTable[h][i];
                    const char newChar = *(s + i);

                    if ((existingChar == newChar) && newChar == '\0')
                    {
                        break;
                    }

                    ASSERT(existingChar == newChar, "HASH_CONFLICT")
                }
            }
#endif

            uint32 i = 0;

            while (*s)
            {
                hashTable[h][i] = *s;
                i++;
                s++;
            }

            return h;
        }

        static constexpr uint32 hashTableSize = 65536;
        static constexpr uint32 hashTableMaxStringLength = 512;
        static char hashTable[hashTableSize][hashTableMaxStringLength];

    public:
        bool operator==(const HString& other) const
        {
            return other._hash == _hash;
        }

        bool operator!=(const HString& other) const
        {
            return !(*this == other);
        }

        bool operator<(const HString other) const
        {
            return _hash < other._hash;
        }

        struct HStringHasher
        {
            std::size_t operator()(const HString& k) const
            {
                return k.GetHash();
            }
        };
    };
}