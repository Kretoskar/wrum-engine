#include "PCH.h"
#include "WrumCore/Rendering/Material.h"

namespace Wrum
{
    void Material::Bind()
    {
        if (BoundShader)
        {
            BoundShader->Bind();
            
            BoundShader->SetUniform1f("metallic", metallic);
            BoundShader->SetUniform1f("roughness", roughness);
            BoundShader->SetUniform1i("hasRoughnessMap", roughnessMap != nullptr);
            BoundShader->SetUniform1i("hasMetallicMap", metallicMap != nullptr);
            BoundShader->SetUniform1i("hasNormalMap", normalMap != nullptr);

            if (diffuseMap)
            {
                BoundShader->AssignDiffuseMap(*diffuseMap);   
            }

            if (roughnessMap)
            {
                roughnessMap->Bind(1);
                BoundShader->SetUniform1i("roughnessMap", 1);
            }

            if (metallicMap)
            {
                metallicMap->Bind(2);
                BoundShader->SetUniform1i("metallicMap", 2);
            }

            if (normalMap)
            {
                normalMap->Bind(3);
                BoundShader->SetUniform1i("normalMap", 3);
            }
        }
        else
        {
            LOG_ERROR("Failed to bind material, shader is null")
        }
    }
}
