#pragma once
#include "WrumCore/Rendering/Vertex.h"
#include <vector>
#include "WrumCore/Rendering/VertexArrayObject.h"


namespace Wrum
{
    struct Mesh
    {
        void Bind();
        void Init(std::vector<Vertex>&& vertices, std::vector<u32>&& indices);
        
        std::vector<Vertex> Vertices;
        std::vector<u32> Indices;

    private:
        VertexArrayObject _vao;
    };
}
