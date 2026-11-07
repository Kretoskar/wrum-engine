#include "PCH.h"
#include "WrumCore/Rendering/Material.h"

namespace Wrum
{
    void Material::Bind()
    {
        if (BoundShader)
        {
            BoundShader->Bind();
            doBind(BoundShader);
        }
        else
        {
            LOG_ERROR("Failed to bind material, shader is null")
        }
    }

    void PbrMaterial::doBind(Shader* shaderPtr)
    {
        shaderPtr->SetUniform1f("metallic", metallic);
        shaderPtr->SetUniform1f("roughness", roughness);
        shaderPtr->SetUniform1i("hasRoughnessMap", roughnessMap != nullptr);
        shaderPtr->SetUniform1i("hasMetallicMap", metallicMap != nullptr);
        shaderPtr->SetUniform1i("hasNormalMap", normalMap != nullptr);

        if (diffuseMap)
        {
            shaderPtr->AssignDiffuseMap(*diffuseMap);   
        }

        if (roughnessMap)
        {
            roughnessMap->Bind(1);
            shaderPtr->SetUniform1i("roughnessMap", 1);
        }

        if (metallicMap)
        {
            metallicMap->Bind(2);
            shaderPtr->SetUniform1i("metallicMap", 2);
        }

        if (normalMap)
        {
            normalMap->Bind(3);
            shaderPtr->SetUniform1i("normalMap", 3);
        }
    }
}
