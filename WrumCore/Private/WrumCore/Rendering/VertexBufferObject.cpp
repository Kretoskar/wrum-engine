#include "PCH.h"
#include "WrumCore/Rendering/VertexBufferObject.h"

namespace Wrum
{
    VertexBufferObject::VertexBufferObject(const float* vertices, long long size)
    {
        Init(vertices, size);
    }

    VertexBufferObject::VertexBufferObject(const std::vector<Vertex>& vertices)
    {
        Init(vertices);
    }

    void VertexBufferObject::Init(const float* vertices, long long size)
    {
        glGenBuffers(1, &_id);
        glBindBuffer(GL_ARRAY_BUFFER, _id);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    void VertexBufferObject::Init(const std::vector<Vertex>& vertices)
    {
        glGenBuffers(1, &_id);
        glBindBuffer(GL_ARRAY_BUFFER, _id);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    }

    void VertexBufferObject::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, _id);
    }

    void VertexBufferObject::Delete()
    {
        glDeleteBuffers(1, &_id);
    }
}
