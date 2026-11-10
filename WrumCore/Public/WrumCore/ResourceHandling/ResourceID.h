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
    
    typedef u64 ResourceID;
    
    constexpr u64 INVALID_RESOURCE_ID = static_cast<u64>(MAKE_TAG16('I', 'N')) << 48 | 0xFFFFFFFF;
    
    [[nodiscard]] FORCE_INLINE ResourceID MakeResourceID(ResourceType type, u16 version, u32 typeIdx)
    {
        return static_cast<u64>(type) << 48 | static_cast<u64>(version) << 32 | typeIdx;
    }
    
    [[nodiscard]] FORCE_INLINE ResourceType GetResourceIDType(ResourceID ID)    {  return static_cast<ResourceType>(ID >> 48);  }
    [[nodiscard]] FORCE_INLINE u16 GetResourceIDVersion(ResourceID ID)          {  return static_cast<u16>(ID >> 32);           }
    [[nodiscard]] FORCE_INLINE u32 GetResourceIDTypeIdx(ResourceID ID)          {  return static_cast<u32>(ID);                 }
    
    [[nodiscard]] FORCE_INLINE bool IsResourceIDValid(ResourceID ID)
    {
        return ID != INVALID_RESOURCE_ID && GetResourceIDVersion(ID) != 0;
    }
}