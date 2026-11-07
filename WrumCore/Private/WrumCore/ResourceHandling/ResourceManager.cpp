#include "PCH.h"
#include "WrumCore/ResourceHandling/ResourceManager.h"

namespace Wrum
{
    ResourceID ResourceManager::NewResourceID(ResourceType type)
    {
        switch (type)
        {
        case ResourceType::Shader:
        #if AB_DEBUG
            ASSERT(_shadersCount < 0xFFFFFFFF, "Reached max shaders count")
        #endif
            _shadersCount++;
            return static_cast<u64>(ResourceType::Shader) << 32 | _shadersCount - 1;
                
        case ResourceType::Material:
        #if AB_DEBUG
            ASSERT(_materialsCount < 0xFFFFFFFF, "Reached max materials count")
        #endif
            _materialsCount++;
            return static_cast<u64>(ResourceType::Material) << 32 | _materialsCount - 1;
                
        case ResourceType::Texture:
        #if AB_DEBUG
            ASSERT(_texturesCount < 0xFFFFFFFF, "Reached max textures count")
        #endif
            _texturesCount++;
            return static_cast<u64>(ResourceType::Texture) << 32 | _texturesCount - 1;
                
        case ResourceType::Mesh:
        #if AB_DEBUG
            ASSERT(_meshesCount < 0xFFFFFFFF, "Reached max meshes count")
        #endif
            _meshesCount++;
            return static_cast<u64>(ResourceType::Mesh) << 32 | _meshesCount - 1;
        }
            
        return InvalidResourceID;
    }
}
