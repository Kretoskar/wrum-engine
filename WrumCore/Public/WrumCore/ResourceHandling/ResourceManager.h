#pragma once

namespace Wrum
{
    typedef u64 ResourceID;
    
    constexpr ResourceID InvalidResourceID = static_cast<u64>(MAKE_TAG32('I', 'N', 'V', 'D')) << 32 | 0xFFFFFFFF;
    
    enum class ResourceType : u32
    {
        Shader = MAKE_TAG32('S', 'H', 'D', 'R'),
        Material = MAKE_TAG32('M', 'T', 'R', 'L'),
        Texture = MAKE_TAG32('T', 'X', 'T', 'R'),
        Mesh = MAKE_TAG32('M', 'E', 'S', 'H')
    };
    
    struct Resource
    {
        Resource() = default;
        virtual ~Resource() = default;
        
        ResourceID GetResourceId() const
        {
            return _resourceId;
        }
        
        bool IsLoaded() const
        {
            return _isLoaded;
        }
        
        bool Load()
        {
            doLoad();
            return _isLoaded;
        }
        
    protected:
        virtual bool doLoad() = 0;
        virtual bool doUnload() = 0;
        
    private:
        ResourceID _resourceId;
        bool _isLoaded = false;
    };
    
    struct ShaderResource : public Resource
    {
        
    };
    
    class ResourceManager
    {
        ResourceID NewResourceID(ResourceType type);
        
        u32 _shadersCount = 0;
        u32 _materialsCount = 0;
        u32 _texturesCount = 0;
        u32 _meshesCount = 0;
    };
}