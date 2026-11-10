#include "PCH.h"
#include "WrumCore/ResourceHandling/ResourceManager.h"

namespace Wrum
{
    ResourceID ResourceManager::MakeShaderResource(HString vertexPath, HString fragmentPath)
    {
        ResourceID resourceId = NewResourceID(ResourceType::Shader);
        if (!resourceId.IsValid())
        {
            return {};
        }

        u32 resourceIdx = resourceId.GetTypeIdx();
        u16 resourceVersion = resourceId.GetVersion();
        
        
        Resource* resource = _shadersResources.Get(resourceIdx, resourceVersion);
        *resource = Resource(vertexPath, fragmentPath, resourceId);
        
        return resourceId;
    }

    ResourceID ResourceManager::NewResourceID(ResourceType type)
    {
        switch (type)
        {
        case ResourceType::Shader:
        {
            auto handle = _shaders.Add();
            if (!handle.IsValid())
            {
                return {};
            }

            // Both arrays must resolve the same resource ID.
            auto resourceHandle = _shadersResources.Add();
            if (!resourceHandle.IsValid() || resourceHandle.Index != handle.Index || resourceHandle.Version != handle.Version)
            {
                _shaders.Remove(handle.Index, handle.Version);
                if (resourceHandle.IsValid())
                {
                    _shadersResources.Remove(resourceHandle.Index, resourceHandle.Version);
                }
                return {};
            }

            return ResourceID(type, handle.Version, handle.Index);
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

    Shader* ResourceManager::LoadShader(ResourceID resourceID)
    {
        Shader* shader = GetShader(resourceID);
        
        if (shader == nullptr)
        {
            return nullptr;
        }
        
        Resource* resource = _shadersResources.Get(resourceID.GetTypeIdx(), resourceID.GetVersion());
        
        File vertFile(resource->GetPath1().Get());
        File fragFile(resource->GetPath2().Get());
        
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
}
