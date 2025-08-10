#include "PCH.h"
#include "WrumCore/Rendering/Material.h"

namespace Wrum
{
    void Material::Bind()
    {
        if (std::shared_ptr<Shader> shaderPtr = BoundShader.lock())
        {
            shaderPtr->Bind();
            Bind_Internal(shaderPtr.get());
        }
        else
        {
            LOG_ERROR("Failed to bind material, shader is null")
        }
    }

    void PbrMaterial::Bind_Internal(Shader* shaderPtr)
    {
        shaderPtr->SetUniform3f("color", Color.x, Color.y, Color.z);
    }
}
