#include "PCH.h"
#include "WrumCore/Rendering/Material.h"

#include "WrumCore/ResourceHandling/ResourceManager.h"

namespace Wrum
{
    void Material::Bind()
    {
        if (IsResourceIDValid(BoundShaderResourceID))
        {
            ASSERT(GetResourceIDType(BoundShaderResourceID) == ResourceType::Shader, "Trying to bind material with invalid shader resource ID")
            
            Shader* shader = ResourceManager::GetInstance()->GetShader(BoundShaderResourceID);
            
            shader->Bind();
            
            shader->SetUniform1f("metallic", metallic);
            shader->SetUniform1f("roughness", roughness);
            shader->SetUniform1i("hasRoughnessMap", roughnessMapResource != INVALID_RESOURCE_ID);
            shader->SetUniform1i("hasMetallicMap", metallicMapResource != INVALID_RESOURCE_ID);
            shader->SetUniform1i("hasNormalMap", normalMapResource != INVALID_RESOURCE_ID);

            if (IsResourceIDValid(diffuseMapResource))
            {
                Texture* texture = ResourceManager::GetInstance()->GetTexture(diffuseMapResource);
                shader->AssignDiffuseMap(*texture);
            }

            if (IsResourceIDValid(roughnessMapResource))
            {
                Texture* texture = ResourceManager::GetInstance()->GetTexture(roughnessMapResource);
                texture->Bind(1);
                shader->SetUniform1i("roughnessMap", 1);
            }

            if (IsResourceIDValid(metallicMapResource))
            {
                Texture* texture = ResourceManager::GetInstance()->GetTexture(metallicMapResource);
                texture->Bind(2);
                shader->SetUniform1i("metallicMap", 2);
            }

            if (IsResourceIDValid(normalMapResource))
            {
                Texture* texture = ResourceManager::GetInstance()->GetTexture(normalMapResource);
                texture->Bind(3);
                shader->SetUniform1i("normalMap", 3);
            }
        }
        else
        {
            LOG_ERROR("Failed to bind material, shader is null")
        }
    }
}
