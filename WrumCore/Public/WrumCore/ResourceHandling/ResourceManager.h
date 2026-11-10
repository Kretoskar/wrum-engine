#pragma once

#include "WrumCore/ResourceHandling/ResourceID.h"
#include "WrumCore/Containers/StaticVersionedArray.h"

#include "WrumCore/Rendering/Material.h"
#include "WrumCore/Rendering/Shader.h"
#include "WrumCore/Rendering/Mesh/Mesh.h"

namespace Wrum
{
    constexpr u32 MaxResourcesPerType = 128;
    constexpr u32 ResourcesTypesNum = 4;
    
    class ResourceManager
    {
    public:
        ResourceManager() = default;
        ResourceID MakeShaderResource(HString vertexPath, HString fragmentPath);
        
        ResourceID NewResourceID(ResourceType type);
        
        Shader* LoadShader(ResourceID resourceID);
        Shader* GetShader(ResourceID shaderId);
        
    private:
        struct Resource
        {
            Resource() = default;
            Resource(HString path1, HString path2, ResourceID resourceId) 
                : _resourceId(resourceId), _path1(path1), _path2(path2) {};
            
            virtual ~Resource() = default;
        
            ResourceID GetResourceId() const
            {
                return _resourceId;
            }
        
            bool IsLoaded() const
            {
                return _isLoaded;
            }
        
            HString GetPath1() const { return _path1; }
            HString GetPath2() const { return _path2; }
        
        private:
            ResourceID _resourceId;
            bool _isLoaded = false;
        
            // 2 paths for shaders (frag and vert)
            HString _path1;
            HString _path2;
        };
        
        StaticVersionedArray<Shader, MaxResourcesPerType> _shaders;
        StaticVersionedArray<Material, MaxResourcesPerType> _materials;
        StaticVersionedArray<Texture, MaxResourcesPerType> _textures;
        StaticVersionedArray<Mesh, MaxResourcesPerType> _meshes;
        
        StaticVersionedArray<Resource, MaxResourcesPerType> _shadersResources;
    };
}
