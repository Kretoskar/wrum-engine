#include "PCH.h"
#include "WrumCore/Rendering/Material.h"

#include "WrumCore/ResourceHandling/ResourceManager.h"

namespace Wrum
{
    Shader* Material::GetShader() const
    {
        return ResourceManager->GetShader(BoundShaderResourceID);
    }

    void Material::Bind()
    {
        if (ResourceManager && BoundShaderResourceID.IsValid())
        {
            ASSERT(BoundShaderResourceID.GetType() == ResourceType::Shader, "Trying to bind material with invalid shader resource ID")
            
            Shader* shader = GetShader();
            
            shader->Bind();
            
            shader->SetUniform1f("metallic", metallic);
            shader->SetUniform1f("roughness", roughness);
            shader->SetUniform1i("hasRoughnessMap", roughnessMap != nullptr);
            shader->SetUniform1i("hasMetallicMap", metallicMap != nullptr);
            shader->SetUniform1i("hasNormalMap", normalMap != nullptr);

            if (diffuseMap)
            {
                shader->AssignDiffuseMap(*diffuseMap);   
            }

            if (roughnessMap)
            {
                roughnessMap->Bind(1);
                shader->SetUniform1i("roughnessMap", 1);
            }

            if (metallicMap)
            {
                metallicMap->Bind(2);
                shader->SetUniform1i("metallicMap", 2);
            }

            if (normalMap)
            {
                normalMap->Bind(3);
                shader->SetUniform1i("normalMap", 3);
            }
        }
        else
        {
            LOG_ERROR("Failed to bind material, shader is null")
        }
    }
}
