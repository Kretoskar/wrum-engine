#pragma once

namespace Wrum
{
    enum class ResourceType : u32
    {
        Shader = MAKE_TAG32('S', 'H', 'D', 'R'),
        Material = MAKE_TAG32('M', 'T', 'R', 'L'),
        Texture = MAKE_TAG32('T', 'X', 'T', 'R'),
        Mesh = MAKE_TAG32('M', 'E', 'S', 'H')
    };
    
    struct ResourceID
    {
        u64 ID;
        
        static constexpr u64 InvalidID = static_cast<u64>(MAKE_TAG32('I', 'N', 'V', 'D')) << 32 | 0xFFFFFFFF;
        
        ResourceID() : ID(InvalidID) {}
        ResourceID(ResourceType type, u32 typeIdx) : ID(static_cast<u64>(type) << 32 |typeIdx) {}
        
        FORCE_INLINE bool IsValid() const { return ID != InvalidID; }
        FORCE_INLINE ResourceType GetType() const { return static_cast<ResourceType>(ID >> 32); }
        FORCE_INLINE u32 GetTypeIdx() const { return static_cast<u32>(ID); }
        
        bool operator==(const ResourceID& other) const { return ID == other.ID; }
        bool operator!=(const ResourceID& other) const { return ID != other.ID; }
    };
}