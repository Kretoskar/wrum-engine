#include "PCH.h"
#include "WrumCore/Rendering/Material.h"

namespace Wrum
{
    void Material::Bind()
    {
        if (BoundShader)
        {
            BoundShader->Bind();
            Bind_Internal(BoundShader);
        }
        else
        {
            LOG_ERROR("Failed to bind material, shader is null")
        }
    }

    void PbrMaterial::Bind_Internal(Shader* shaderPtr)
    {
        shaderPtr->SetUniform1f("metallic", metallic);
        shaderPtr->SetUniform1f("roughness", roughness);

        if (diffuseMap)
        {
            shaderPtr->AssignDiffuseMap(*diffuseMap);   
        }
    }
}
