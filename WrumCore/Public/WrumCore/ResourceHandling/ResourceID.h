#pragma once

#include "WrumCore/Core/Types.h"

namespace Wrum
{
    enum class ResourceType : u16
    {
        Shader = MAKE_TAG16('S', 'H'),
        Material = MAKE_TAG16('M', 'T'),
        Texture = MAKE_TAG16('T', 'X'),
        Mesh = MAKE_TAG16('M', 'S')
    };
    
    // 16 bits type (2 chars) followed by 16 bits version and 32 bits type index
    struct ResourceID
    {
        u64 ID;
        
        static constexpr u64 InvalidID = static_cast<u64>(MAKE_TAG16('I', 'N')) << 48 | 0xFFFFFFFF;
        
        ResourceID() : ID(InvalidID) {}
        ResourceID(ResourceType type, u16 version, u32 typeIdx)
            : ID(static_cast<u64>(type) << 48 | static_cast<u64>(version) << 32 | typeIdx) {}
        
        FORCE_INLINE bool IsValid() const { return ID != InvalidID && GetVersion() != 0; }
        [[nodiscard]] FORCE_INLINE ResourceType GetType() const { return static_cast<ResourceType>(ID >> 48); }
        [[nodiscard]] FORCE_INLINE u16 GetVersion() const { return static_cast<u16>(ID >> 32); }
        [[nodiscard]] FORCE_INLINE u32 GetTypeIdx() const { return static_cast<u32>(ID); }
        
        bool operator==(const ResourceID& other) const { return ID == other.ID; }
        bool operator!=(const ResourceID& other) const { return ID != other.ID; }
    };
}
