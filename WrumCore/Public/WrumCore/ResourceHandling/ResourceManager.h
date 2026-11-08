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
    
    struct Resource;
    
    class ResourceManager
    {
    public:
        ResourceManager() = default;
        Resource* MakeShaderResource(HString vertexPath, HString fragmentPath);
        
        ResourceID NewResourceID(ResourceType type);
        
        Shader* LoadShader(const Resource& resource);
    
        Shader* GetShader(ResourceID shaderId);
        
    private:
        StaticVersionedArray<Shader, MaxResourcesPerType> _shaders;
        StaticVersionedArray<Material, MaxResourcesPerType> _materials;
        StaticVersionedArray<Texture, MaxResourcesPerType> _textures;
        StaticVersionedArray<Mesh, MaxResourcesPerType> _meshes;
        
        ArenaAllocator _resourcesArena = ArenaAllocator(BIT_KILO_BYTE(10), "Resources");
    };
    
    struct Resource
    {
        Resource() = default;
        Resource(HString path1, HString path2, ResourceID resourceId) : _resourceId(resourceId), _path1(path1), _path2(path2) {};
        virtual ~Resource() = default;
        
        ResourceID GetResourceId() const
        {
            return _resourceId;
        }
        
        bool IsLoaded() const
        {
            return _isLoaded;
        }
        
        bool Load(ResourceManager& manager);
        
        HString GetPath1() const { return _path1; }
        HString GetPath2() const { return _path2; }
        
        Shader& GetShader() const
        {
            ASSERT(_shader != nullptr, "Trying to retrieve unloaded shader");
            return *_shader;
        }
        
    private:
        ResourceID _resourceId;
        bool _isLoaded = false;
        
        // 2 paths for shaders (frag and vert)
        HString _path1;
        HString _path2;
        
        Shader* _shader = nullptr;
        Material* _material = nullptr;
        Texture* _texture = nullptr;
        Mesh* _mesh = nullptr;
    };
}
