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
