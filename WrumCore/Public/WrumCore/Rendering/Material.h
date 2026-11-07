#pragma once
#include <map>

#include "Shader.h"

namespace Wrum
{
    struct Material
    {
        Material() = default;
        Material(Shader* shader) : BoundShader(shader) {}
        virtual ~Material() = default;
        
        Shader* BoundShader;

        void Bind();

        Texture* diffuseMap= nullptr;
        Texture* roughnessMap = nullptr;
        Texture* metallicMap = nullptr;
        Texture* normalMap = nullptr;

        // Used when the corresponding map is not assigned.
        f32 metallic = 0.0f;
        f32 roughness = 0.5f;
    };
}
