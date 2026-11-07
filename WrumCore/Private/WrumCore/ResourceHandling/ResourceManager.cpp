#include "PCH.h"
#include "WrumCore/ResourceHandling/ResourceManager.h"

namespace Wrum
{
    Resource* ResourceManager::MakeShaderResource(HString vertexPath, HString fragmentPath)
    {
        Resource* resource = 
            ArenaAllocator::New<Resource>(_resourcesArena, vertexPath, fragmentPath, NewResourceID(ResourceType::Shader));
        
        return resource;
    }

    ResourceID ResourceManager::NewResourceID(ResourceType type)
    {
        switch (type)
        {
        case ResourceType::Shader:
        #if AB_DEBUG
            ASSERT(_shadersCount < 0xFFFFFFFF, "Reached max shaders count")
        #endif
            _shadersCount++;
            return ResourceID(type, _shadersCount - 1);
        
        case ResourceType::Material:
        #if AB_DEBUG
            ASSERT(_materialsCount < 0xFFFFFFFF, "Reached max materials count")
        #endif
            _materialsCount++;
            return ResourceID(type, _materialsCount - 1);
                
        case ResourceType::Texture:
        #if AB_DEBUG
            ASSERT(_texturesCount < 0xFFFFFFFF, "Reached max textures count")
        #endif
            _texturesCount++;
            return ResourceID(type, _texturesCount - 1);
                
        case ResourceType::Mesh:
        #if AB_DEBUG
            ASSERT(_meshesCount < 0xFFFFFFFF, "Reached max meshes count")
        #endif
            _meshesCount++;
            return ResourceID(ResourceType::Mesh, _meshesCount - 1);
        }
            
        return ResourceID();
    }

    Shader* ResourceManager::LoadShader(const Resource& resource)
    {
        ASSERT(resource.GetResourceId().GetType() == ResourceType::Shader, "Invalid resource type")
        
        u32 idx = resource.GetResourceId().GetTypeIdx();
        Shader& shader = _shaders[idx];
        
        File vertFile(resource.GetPath1().Get());
        File fragFile(resource.GetPath2().Get());
        
        shader.Create(vertFile, fragFile);
        
        return &shader;
    }

    bool Resource::Load(ResourceManager& manager)
    {
        switch (_resourceId.GetType()) 
        {
        case ResourceType::Shader:
            _shader = manager.LoadShader(*this);
            return _shader != nullptr;
            
        case ResourceType::Material:
            break;
            
        case ResourceType::Texture:
            break;
            
        case ResourceType::Mesh:
            break;
        }
        
        return true;
    }
}
