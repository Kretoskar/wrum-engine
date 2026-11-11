#include "PCH.h"
#include "WrumCore/ResourceHandling/ResourceManager.h"

namespace Wrum
{
    ResourceID ResourceManager::MakeShaderResource(HString vertexPath, HString fragmentPath)
    {
        ResourceID resourceId = NewResourceID(ResourceType::Shader);
        if (!IsResourceIDValid(resourceId))
        {
            LOG_WARNING("Can't create resource id")
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
            LOG_WARNING("Can't create resource id")
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
                    LOG_WARNING("Can't create shader ID")
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
                    LOG_WARNING("Resource or shaders array invalid")
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
                    LOG_WARNING("Can't create texture ID")
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
                    LOG_WARNING("Resource or textures array invalid")
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
        Shader* shader = _shaders.Get(GetResourceIDTypeIdx(resourceID), GetResourceIDVersion(resourceID));
        
        if (shader == nullptr)
        {
            LOG_WARNING("Trying to load shader with invalid ID")
            return nullptr;
        }
        
        Resource* resource = GetResource(resourceID);
        if(resource == nullptr || !resource->IsCreated)
        {
            LOG_WARNING("Resource you're trying to load shader from is invalid")
            return nullptr;
        }
        
        File vertFile(resource->GetPath1().Get());
        File fragFile(resource->GetPath2().Get());
        
        shader->Create(vertFile, fragFile);
        resource->IsLoaded = true;
        
        return shader;
    }

    Shader* ResourceManager::GetShader(ResourceID resourceID)
    {
        if (!IsResourceIDValid(resourceID) || GetResourceIDType(resourceID) != ResourceType::Shader)
        {
            LOG_WARNING("Trying to get shader using invalid ID")
            return nullptr;
        }
        
        Resource* res = GetResource(resourceID);
        if (!res->IsCreated || !res->IsLoaded)
        {
            LOG_WARNING("Resource you're trying to get shader from is invalid")
            return nullptr;
        }
        
        return _shaders.Get(GetResourceIDTypeIdx(resourceID), GetResourceIDVersion(resourceID));
    }

    Texture* ResourceManager::LoadTexture(ResourceID resourceID)
    {
        Texture* texture = _textures.Get(GetResourceIDTypeIdx(resourceID), GetResourceIDVersion(resourceID));
        
        if (texture == nullptr)
        {
            LOG_WARNING("Trying to load texture using invalid ID")
            return nullptr;
        }
        
        Resource* resource = GetResource(resourceID);
        if(resource == nullptr || !resource->IsCreated)
        {
            LOG_WARNING("Resource you're trying to load texture from is invalid")
            return nullptr;
        }
        
        *texture = Texture(resource->GetPath1()); 
        resource->IsLoaded = true;
        
        return texture;
    }

    Texture* ResourceManager::GetTexture(ResourceID resourceID)
    {
        if (!IsResourceIDValid(resourceID) || GetResourceIDType(resourceID) != ResourceType::Texture)
        {
            LOG_WARNING("Trying to get texture using invalid ID")
            return nullptr;
        }

        Resource* res = GetResource(resourceID);
        if (!res->IsCreated || !res->IsLoaded)
        {
            LOG_WARNING("Resource you're trying to get texture from is invalid")
            return nullptr;
        }
        
        return _textures.Get(GetResourceIDTypeIdx(resourceID), GetResourceIDVersion(resourceID));
    }

    ResourceManager::Resource* ResourceManager::GetResource(ResourceID resourceID)
    {
        switch (GetResourceIDType(resourceID)) 
        {
            case ResourceType::Shader:
                {
                    Resource* res = _shadersResources.Get(GetResourceIDTypeIdx(resourceID), GetResourceIDVersion(resourceID));
                    if (res->IsCreated)
                    {
                        return res;
                    }
                    return nullptr;
                }
            case ResourceType::Material:
                {
                    Resource* res = _materialsResources.Get(GetResourceIDTypeIdx(resourceID), GetResourceIDVersion(resourceID));
                    if (res->IsCreated)
                    {
                        return res;
                    }
                    return nullptr;
                }
            case ResourceType::Texture:
                {
                    Resource* res = _texturesResources.Get(GetResourceIDTypeIdx(resourceID), GetResourceIDVersion(resourceID));
                    if (res->IsCreated)
                    {
                        return res;
                    }
                    return nullptr;
                }
            case ResourceType::Mesh:
                {
                    Resource* res = _meshesResources.Get(GetResourceIDTypeIdx(resourceID), GetResourceIDVersion(resourceID));
                    if (res->IsCreated)
                    {
                        return res;
                    }
                    return nullptr;
                }
        }
        
        ASSERT_NO_ENTRY()
    }
}
