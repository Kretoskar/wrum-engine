#pragma once

#include <string>
#include "AnimBoxCore/Core/Public/Assert.h"

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

        uint32_t GetHash() const { return _hash; }

        static HString None;

    private:
        uint32_t _hash {};

    public:
        const char* Get() const
        {
            return hashTable[_hash];
        }

    private:
        // hash using prime numbers
        static constexpr uint32_t Hash(const char* s)
        {
            uint32_t h = 37;
            uint32_t size = 0;

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
                for (unsigned i = 0; i < hashTableMaxStringLength; i++)
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

            unsigned i = 0;

            while (*s)
            {
                hashTable[h][i] = *s;
                i++;
                s++;
            }

            return h;
        }

        static constexpr uint32_t hashTableSize = 65536;
        static constexpr uint32_t hashTableMaxStringLength = 512;
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