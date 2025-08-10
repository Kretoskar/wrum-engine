#pragma once
#include <map>

#include "Shader.h"

namespace Wrum
{
    struct Material
    {
        virtual ~Material() = default;
        
        std::weak_ptr<Shader> BoundShader;

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
