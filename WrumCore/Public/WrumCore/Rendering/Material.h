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
        Material(ResourceID shaderResourceID)
            : BoundShaderResourceID(shaderResourceID) {}
        virtual ~Material() = default;
        
        void Bind();
        
        ResourceID BoundShaderResourceID = INVALID_RESOURCE_ID;

        ResourceID diffuseMapResource = INVALID_RESOURCE_ID;
        ResourceID roughnessMapResource = INVALID_RESOURCE_ID;
        ResourceID metallicMapResource = INVALID_RESOURCE_ID;
        ResourceID normalMapResource = INVALID_RESOURCE_ID;

        // Used when the corresponding map is not assigned.
        f32 metallic = 0.0f;
        f32 roughness = 0.5f;
    };
}
