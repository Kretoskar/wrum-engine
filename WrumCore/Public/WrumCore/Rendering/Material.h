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
        Vec3 Color;

    protected:
        void Bind_Internal(Shader* shaderPtr) override;
    };
}
