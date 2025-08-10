#pragma once

#include "Material.h"
#include "Mesh/Mesh.h"
#include "WrumCore/Rendering/Vertex.h"

namespace Wrum
{
    class Renderer
    {
    public:
        void DrawMesh(const Mesh& mesh, Material& material, const Mat4& transform);
    };
}