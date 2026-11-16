#pragma once
#include "WrumCore/Rendering/Vertex.h"
#include <vector>
#include "WrumCore/Rendering/VertexArrayObject.h"


namespace Wrum
{
    struct Mesh
    {
        void Bind();
        void Init(Wrum::Vertices&& vertices, std::vector<u32>&& indices);
        
        Wrum::Vertices Vertices;
        std::vector<u32> Indices;

    private:
        VertexArrayObject _vao;
    };
}
