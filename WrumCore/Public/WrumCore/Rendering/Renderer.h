#pragma once

#include <vector>

#include "Framebuffer.h"
#include "Material.h"
#include "Mesh/Mesh.h"
#include "WrumCore/Rendering/Vertex.h"

namespace Wrum
{
    class Camera;
}

namespace Wrum
{
    class Renderer
    {
    public:
        Renderer(Camera* camera) : _camera(camera)
        {
        }
        
        void DrawMesh(Mesh& mesh, Material& material, const Mat4& transform);
        
        std::vector<PointLight> PointLights;
        
    private:
        Camera* _camera;
        std::vector<std::weak_ptr<Shader>> _shaders;
    };
}
