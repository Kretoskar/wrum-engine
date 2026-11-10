#include "PCH.h"
#include "WrumCore/ResourceHandling/ResourceManager.h"

namespace Wrum
{
    ResourceID ResourceManager::MakeShaderResource(HString vertexPath, HString fragmentPath)
    {
        ResourceID resourceId = NewResourceID(ResourceType::Shader);
        if (!IsResourceIDValid(resourceId))
        {
            return {};
        }

        u32 resourceIdx = GetResourceIDTypeIdx(resourceId);
        u16 resourceVersion = GetResourceIDVersion(resourceId);
        
        Resource* resource = _shadersResources.Get(resourceIdx, resourceVersion);
        *resource = Resource(vertexPath, fragmentPath, resourceId);
        
        return resourceId;
    }

    ResourceID ResourceManager::MakeTextureResource(HString path)
    {
        ResourceID resourceId = NewResourceID(ResourceType::Texture);
        if (!IsResourceIDValid(resourceId))
        {
            return {};
        }

        u32 resourceIdx = GetResourceIDTypeIdx(resourceId);
        u16 resourceVersion = GetResourceIDVersion(resourceId);
        
        Resource* resource = _texturesResources.Get(resourceIdx, resourceVersion);
        *resource = Resource(path, path, resourceId);
        
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
    
                return MakeResourceID(type, SafeCast_uint16(handle.Version), handle.Index);
            }
            
            case ResourceType::Material:
            {
                auto handle = _materials.Add();
                return handle.IsValid() ? MakeResourceID(type, SafeCast_uint16(handle.Version), handle.Index) : ResourceID();
            }
                    
            case ResourceType::Texture:
            {
                auto handle = _textures.Add();
                if (!handle.IsValid())
                {
                    return {};
                }
                
                // Both arrays must resolve the same resource ID.
                auto resourceHandle = _texturesResources.Add();
                if (!resourceHandle.IsValid() || resourceHandle.Index != handle.Index || resourceHandle.Version != handle.Version)
                {
                    _textures.Remove(handle.Index, handle.Version);
                    if (resourceHandle.IsValid())
                    {
                        _texturesResources.Remove(resourceHandle.Index, resourceHandle.Version);
                    }
                    return {};
                }
                
                return handle.IsValid() ? MakeResourceID(type, SafeCast_uint16(handle.Version), handle.Index) : ResourceID();
            }
                    
            case ResourceType::Mesh:
            {
                auto handle = _meshes.Add();
                return handle.IsValid() ? MakeResourceID(type, SafeCast_uint16(handle.Version), handle.Index) : ResourceID();
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
        
        Resource* resource = _shadersResources.Get(GetResourceIDTypeIdx(resourceID), GetResourceIDVersion(resourceID));
        
        File vertFile(resource->GetPath1().Get());
        File fragFile(resource->GetPath2().Get());
        
        shader->Create(vertFile, fragFile);
        
        return shader;
    }

    Shader* ResourceManager::GetShader(ResourceID resourceID)
    {
        if (!IsResourceIDValid(resourceID) || GetResourceIDType(resourceID) != ResourceType::Shader)
        {
            return nullptr;
        }

        return _shaders.Get(GetResourceIDTypeIdx(resourceID), GetResourceIDVersion(resourceID));
    }

    Texture* ResourceManager::LoadTexture(ResourceID resourceID)
    {
        Texture* texture = GetTexture(resourceID);
        
        if (texture == nullptr)
        {
            return nullptr;
        }
        
        Resource* resource = _texturesResources.Get(GetResourceIDTypeIdx(resourceID), GetResourceIDVersion(resourceID));
        *texture = Texture(resource->GetPath1()); 
        
        return texture;
    }

    Texture* ResourceManager::GetTexture(ResourceID resourceID)
    {
        if (!IsResourceIDValid(resourceID) || GetResourceIDType(resourceID) != ResourceType::Texture)
        {
            return nullptr;
        }

        return _textures.Get(GetResourceIDTypeIdx(resourceID), GetResourceIDVersion(resourceID));
    }
}
