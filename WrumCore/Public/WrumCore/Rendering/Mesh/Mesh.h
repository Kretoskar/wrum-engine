#pragma once
#include "WrumCore/Rendering/Vertex.h"
#include <vector>

#include "WrumCore/Math/Mat4.h"
#include "WrumCore/Rendering/VertexArrayObject.h"


namespace Wrum
{
    struct Mesh
    {
        void Bind();
        void Init(Wrum::Vertices&& vertices, std::vector<u32>&& indices);
        void BindInstanceTransforms(const std::vector<Mat4>& transforms);
        
        Wrum::Vertices Vertices;
        std::vector<u32> Indices;

    private:
        VertexArrayObject _vao;
        u32 _instanceVbo {};
    };
}
