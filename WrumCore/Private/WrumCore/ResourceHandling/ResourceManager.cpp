#include "PCH.h"
#include "WrumCore/ResourceHandling/ResourceManager.h"

namespace Wrum
{
    Resource* ResourceManager::MakeShaderResource(HString vertexPath, HString fragmentPath)
    {
        ResourceID resourceId = NewResourceID(ResourceType::Shader);
        if (!resourceId.IsValid())
        {
            return nullptr;
        }

        Resource* resource =
            ArenaAllocator::New<Resource>(_resourcesArena, vertexPath, fragmentPath, resourceId);
        
        return resource;
    }

    ResourceID ResourceManager::NewResourceID(ResourceType type)
    {
        switch (type)
        {
        case ResourceType::Shader:
        {
            auto handle = _shaders.Add();
            return handle.IsValid() ? ResourceID(type, handle.Version, handle.Index) : ResourceID();
        }
        
        case ResourceType::Material:
        {
            auto handle = _materials.Add();
            return handle.IsValid() ? ResourceID(type, handle.Version, handle.Index) : ResourceID();
        }
                
        case ResourceType::Texture:
        {
            auto handle = _textures.Add();
            return handle.IsValid() ? ResourceID(type, handle.Version, handle.Index) : ResourceID();
        }
                
        case ResourceType::Mesh:
        {
            auto handle = _meshes.Add();
            return handle.IsValid() ? ResourceID(type, handle.Version, handle.Index) : ResourceID();
        }
        }
            
        return ResourceID();
    }

    Shader* ResourceManager::LoadShader(const Resource& resource)
    {
        Shader* shader = GetShader(resource.GetResourceId());
        if (shader == nullptr)
        {
            return nullptr;
        }
        
        File vertFile(resource.GetPath1().Get());
        File fragFile(resource.GetPath2().Get());
        
        shader->Create(vertFile, fragFile);
        
        return shader;
    }

    Shader* ResourceManager::GetShader(ResourceID shaderId)
    {
        if (!shaderId.IsValid() || shaderId.GetType() != ResourceType::Shader)
        {
            return nullptr;
        }

        return _shaders.Get(shaderId.GetTypeIdx(), shaderId.GetVersion());
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
