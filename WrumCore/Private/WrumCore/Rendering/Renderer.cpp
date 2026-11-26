#include "PCH.h"
#include "WrumCore/Rendering/Renderer.h"

#include "WrumCore/Rendering/Camera.h"
#include "WrumCore/ResourceHandling/ResourceManager.h"

void Wrum::Renderer::DrawMesh(Mesh& mesh, Material& material, const Mat4& transform)
{
    material.Bind();
    Shader* shader = ResourceManager::GetInstance()->GetShader(material.BoundShaderResourceID);
    
    shader->SetModelMatrix(transform);
    shader->SetCameraPosition(_camera->Position);
    shader->SetVPMatrix(_camera->GetVPMatrix());
    shader->SetPointLights(PointLights);
    
    mesh.Bind();
    glDrawElements(GL_TRIANGLES, mesh.Indices.size(), GL_UNSIGNED_INT, 0);
}

void Wrum::Renderer::AddMeshToRender(ResourceID mesh, ResourceID material, const Mat4& transform)
{
    const BatchKey key{mesh, material};
    const auto found = _batchLookup.find(key);
    if (found != _batchLookup.end())
    {
        _batches[found->second].Transforms.push_back(transform);
        return;
    }

    const size_t batchIndex = _batches.size();
    _batches.push_back({mesh, material, {transform}});
    _batchLookup.emplace(key, batchIndex);
}

void Wrum::Renderer::AddEntityToRender(const Entity& entity)
{
    AddMeshToRender(entity.MeshID, entity.MaterialID, entity.Transform);
}

void Wrum::Renderer::Render()
{
    ResourceManager* resources = ResourceManager::GetInstance();
    for (const Batch& batch : _batches)
    {
        Mesh* mesh = resources->GetMesh(batch.MeshResource);
        Material* material = resources->GetMaterial(batch.MaterialResource);
        if (mesh == nullptr || material == nullptr)
        {
            continue;
        }

        material->Bind();
        Shader* shader = resources->GetShader(material->BoundShaderResourceID);
        if (shader == nullptr)
        {
            continue;
        }
        shader->SetCameraPosition(_camera->Position);
        shader->SetVPMatrix(_camera->GetVPMatrix());
        shader->SetPointLights(PointLights);
        mesh->Bind();

        mesh->BindInstanceTransforms(batch.Transforms);
        glDrawElementsInstanced(GL_TRIANGLES, static_cast<GLsizei>(mesh->Indices.size()), GL_UNSIGNED_INT, 0,
            static_cast<GLsizei>(batch.Transforms.size()));
    }
    _batches.clear();
    _batchLookup.clear();
}
