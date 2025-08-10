#include "PCH.h"
#include "WrumCore/Rendering/Renderer.h"

#include "WrumCore/Rendering/Camera.h"

void Wrum::Renderer::DrawMesh(Mesh& mesh, Material& material, const Mat4& transform) const
{
        
        material.BoundShader->SetModelMatrix(transform);
        material.BoundShader->SetCameraPosition(_camera->GetPosition());
        material.BoundShader->SetVPMatrix(_camera->GetVPMatrix());
        
        mesh.Bind();

        glDrawElements(GL_TRIANGLES, mesh.Indices.size(), GL_UNSIGNED_INT, 0);
}
