#pragma once

#include "WrumCore/Rendering/Vertex.h"

namespace Wrum
{
    class VertexBufferObject
    {
    public:
        VertexBufferObject(float* vertices, long long size);
        VertexBufferObject(const std::vector<Vertex>& vertices);
        void Init(float* vertices, long long size);
        void Init(const std::vector<Vertex>& vertices);

        void Bind() const;
        void Delete();

        unsigned int GetId() const { return _id; }

    private:
        unsigned int _id;
    };

    class VertexArrayObject
    {
    public:
        VertexArrayObject();

        void LinkAttrib(const VertexBufferObject& vbo, unsigned layout, int numComponents, unsigned type, int stride, void* offset);
        void Bind();
        void Delete();

        unsigned int GetId() const { return _id; }

    private:
        unsigned int _id;
    };
    
    class Renderer
    {
        
    };
}