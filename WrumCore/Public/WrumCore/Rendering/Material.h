#pragma once
#include <map>

#include "Shader.h"

namespace Wrum
{
    struct Material
    {
        Material(Shader* shader) : BoundShader(shader) {}
        virtual ~Material() = default;
        
        Shader* BoundShader;

        void Bind();

    protected:
        virtual void Bind_Internal(Shader* shaderPtr) {}
    };
    
    struct PbrMaterial : public Material
    {
        PbrMaterial(Shader* shader) : Material(shader), diffuseMap(nullptr) {}

        // TODO: GUID system for detecting deletion etc
        Texture* diffuseMap;
        f32 metallic = 0.0f;
        f32 roughness = 0.5f;
        
    protected:
        void Bind_Internal(Shader* shaderPtr) override;
    };
}
