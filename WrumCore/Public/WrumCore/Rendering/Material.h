#pragma once
#include <map>

#include "Shader.h"
#include "WrumCore/ResourceHandling/ResourceID.h"

namespace Wrum
{
    class ResourceManager;

    struct Material
    {
        Material() = default;
        Material(ResourceID shaderResourceID, ResourceManager* resourceManager)
            : BoundShaderResourceID(shaderResourceID), ResourceManager(resourceManager) {}
        virtual ~Material() = default;
        
        Shader* GetShader() const;
        
        ResourceID BoundShaderResourceID;

        void Bind();

        Texture* diffuseMap= nullptr;
        Texture* roughnessMap = nullptr;
        Texture* metallicMap = nullptr;
        Texture* normalMap = nullptr;

        // Used when the corresponding map is not assigned.
        f32 metallic = 0.0f;
        f32 roughness = 0.5f;
        
        ResourceManager* ResourceManager = nullptr;
    };
}
