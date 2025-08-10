#pragma once
#include "WrumCore/Rendering/Vertex.h"
#include "WrumCore/Rendering/VertexArrayObject.h"


namespace Wrum
{
    struct Mesh
    {
        void Bind();
        void Init(const std::vector<Vertex>& vertices,  std::vector<uint32> indices);
        
        std::vector<Vertex> Vertices;
        std::vector<uint32> Indices;

    private:
        VertexArrayObject _vao;
    };
}
