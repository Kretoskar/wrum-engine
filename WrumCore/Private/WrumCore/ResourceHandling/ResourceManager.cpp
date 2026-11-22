#include "PCH.h"
#include "WrumCore/ResourceHandling/ResourceManager.h"

#include "WrumCore/Rendering/Mesh/Primitives/Arrow.h"
#include "WrumCore/Rendering/Mesh/Primitives/Cube.h"
#include "WrumCore/Rendering/Mesh/Primitives/Plane.h"
#include "WrumCore/Rendering/Mesh/Primitives/Sphere.h"

namespace Wrum
{
    ResourceID ResourceManager::MakeShaderResource(HString vertexPath, HString fragmentPath)
    {
        return MakeResource(ResourceType::Shader, vertexPath, fragmentPath);
    }

    ResourceID ResourceManager::MakeTextureResource(HString path)
    {
        return MakeResource(ResourceType::Texture, path, "");
    }

    ResourceID ResourceManager::MakeMaterialResource(ResourceID shaderResourceID)
    {
        if (!IsResourceIDValid(shaderResourceID) || GetResourceIDType(shaderResourceID) != ResourceType::Shader)
        {
            LOG_WARNING("Trying to create material using invalid shader ID")
            return {};
        }

        ResourceID materialResourceID = MakeResource(ResourceType::Material, "", "");
        if (!IsResourceIDValid(materialResourceID))
        {
            return {};
        }

        Material* material = _materials.Get(GetResourceIDTypeIdx(materialResourceID), GetResourceIDVersion(materialResourceID));
        Resource* resource = GetResource(materialResourceID);
        if (material == nullptr || resource == nullptr)
        {
            LOG_WARNING("Can't create material resource")
            return {};
        }

        *material = Material(shaderResourceID);
        resource->IsLoaded = true;
        return materialResourceID;
    }

    ResourceID ResourceManager::MakePrimitiveMeshResource(PrimitiveType type)
    {
        // encoding primitive type in path
        Tag16String tag((u16)type);
        return MakeResource(ResourceType::Mesh, tag.str, "");
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
                if (!handle.IsValid())
                {
                    LOG_WARNING("Can't create shader ID")
                    return {};
                }
    
                // Both arrays must resolve the same resource ID.
                auto resourceHandle = _materialsResources.Add();
                if (!resourceHandle.IsValid() || resourceHandle.Index != handle.Index || resourceHandle.Version != handle.Version)
                {
                    _materials.Remove(handle.Index, handle.Version);
                    if (resourceHandle.IsValid())
                    {
                        _materialsResources.Remove(resourceHandle.Index, resourceHandle.Version);
                    }
                    LOG_WARNING("Resource or materials array invalid")
                    return {};
                }
    
                return MakeResourceID(type, SafeCast_uint16(handle.Version), handle.Index);
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
                if (!handle.IsValid())
                {
                    LOG_WARNING("Can't create shader ID")
                    return {};
                }
    
                // Both arrays must resolve the same resource ID.
                auto resourceHandle = _meshesResources.Add();
                if (!resourceHandle.IsValid() || resourceHandle.Index != handle.Index || resourceHandle.Version != handle.Version)
                {
                    _meshes.Remove(handle.Index, handle.Version);
                    if (resourceHandle.IsValid())
                    {
                        _meshesResources.Remove(resourceHandle.Index, resourceHandle.Version);
                    }
                    LOG_WARNING("Resource or meshes array invalid")
                    return {};
                }
    
                return MakeResourceID(type, SafeCast_uint16(handle.Version), handle.Index);
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

    Mesh* ResourceManager::LoadPrimitiveMesh(ResourceID resourceID)
    {
        Mesh* mesh = _meshes.Get(GetResourceIDTypeIdx(resourceID), GetResourceIDVersion(resourceID));
        
        if (mesh == nullptr)
        {
            LOG_WARNING("Trying to load mesh with invalid ID")
            return nullptr;
        }
        
        Resource* resource = GetResource(resourceID);
        if(resource == nullptr || !resource->IsCreated)
        {
            LOG_WARNING("Resource you're trying to load mesh from is invalid")
            return nullptr;
        }
        
        HString path = resource->GetPath1();
        Tag16String tag(path.Get(), 2);
        PrimitiveType primitiveType = (PrimitiveType)tag.tag;
        switch (primitiveType)
        {
        case PrimitiveType::Sphere:
            *mesh = Wrum::Sphere();
            break;
        case PrimitiveType::Cube:
            *mesh = Wrum::Cube();
            break;
        case PrimitiveType::Plane:
            *mesh = Wrum::Plane();
            break;
        case PrimitiveType::Arrow:
            *mesh = Wrum::Arrow();
            break;
        }
        
        resource->IsLoaded = true;
        return mesh;
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

    Material* ResourceManager::GetMaterial(ResourceID resourceID)
    {
        if (!IsResourceIDValid(resourceID) || GetResourceIDType(resourceID) != ResourceType::Material)
        {
            LOG_WARNING("Trying to get material using invalid ID")
            return nullptr;
        }
        return _materials.Get(GetResourceIDTypeIdx(resourceID), GetResourceIDVersion(resourceID));
    }

    Mesh* ResourceManager::GetMesh(ResourceID resourceID)
    {
        if (!IsResourceIDValid(resourceID) || GetResourceIDType(resourceID) != ResourceType::Mesh)
        {
            LOG_WARNING("Trying to get mesh using invalid ID")
            return nullptr;
        }
        return _meshes.Get(GetResourceIDTypeIdx(resourceID), GetResourceIDVersion(resourceID));
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

    ResourceID ResourceManager::MakeResource(ResourceType type, HString path1, HString path2)
    {
        ResourceID resourceId = NewResourceID(type);
        if (!IsResourceIDValid(resourceId))
        {
            LOG_WARNING("Can't create resource id")
            return {};
        }

        u32 resourceIdx = GetResourceIDTypeIdx(resourceId);
        u16 resourceVersion = GetResourceIDVersion(resourceId);
        
        Resource* resource;
        switch (type)
        {
        case ResourceType::Shader:
            resource = _shadersResources.Get(resourceIdx, resourceVersion);
            break;
        case ResourceType::Material:
            resource = _materialsResources.Get(resourceIdx, resourceVersion);
            break;
        case ResourceType::Texture:
            resource = _texturesResources.Get(resourceIdx, resourceVersion);
            break;
        case ResourceType::Mesh:
            resource = _meshesResources.Get(resourceIdx, resourceVersion);
            break;
        default: 
            ASSERT_NO_ENTRY()
        }
        
        *resource = Resource(path1, path2, resourceId);
        return resourceId;
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
