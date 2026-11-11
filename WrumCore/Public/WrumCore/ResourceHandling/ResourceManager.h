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
        ResourceID MakeTextureResource(HString path);
        
        ResourceID NewResourceID(ResourceType type);
        
        Shader* LoadShader(ResourceID resourceID);
        [[nodiscard]] Shader* GetShader(ResourceID resourceID);
        
        Texture* LoadTexture(ResourceID resourceID);
        [[nodiscard]] Texture* GetTexture(ResourceID resourceID);
        
        // split to set and get to find where the instance is set easier
        static FORCE_INLINE ResourceManager* SetInstance(ResourceManager* instance) { return _instance = instance; }
        static [[nodiscard]] FORCE_INLINE ResourceManager* GetInstance() { return _instance; }
        
    private:
        static inline ResourceManager* _instance;
        
        struct Resource
        {
            Resource() = default;
            Resource(HString path1, HString path2, ResourceID resourceId) 
                : IsCreated(true), _resourceId(resourceId), _path1(path1), _path2(path2) {};
            
            virtual ~Resource() = default;
        
            ResourceID GetResourceId() const
            {
                return _resourceId;
            }
        
            HString GetPath1() const { return _path1; }
            HString GetPath2() const { return _path2; }
        
            bool IsCreated = false;
            bool IsLoaded = false;
            
        private:
            ResourceID _resourceId;
        
            // 2 paths for shaders (frag and vert)
            HString _path1;
            HString _path2;
        };
        
        Resource* GetResource (ResourceID resourceID);
        
        StaticVersionedArray<Shader, MaxResourcesPerType> _shaders;
        StaticVersionedArray<Material, MaxResourcesPerType> _materials;
        StaticVersionedArray<Texture, MaxResourcesPerType> _textures;
        StaticVersionedArray<Mesh, MaxResourcesPerType> _meshes;
        
        StaticVersionedArray<Resource, MaxResourcesPerType> _shadersResources;
        StaticVersionedArray<Resource, MaxResourcesPerType> _materialsResources;
        StaticVersionedArray<Resource, MaxResourcesPerType> _texturesResources;
        StaticVersionedArray<Resource, MaxResourcesPerType> _meshesResources;
    };
}
