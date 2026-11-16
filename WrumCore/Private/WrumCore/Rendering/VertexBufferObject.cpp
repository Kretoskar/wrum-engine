#include "PCH.h"
#include "WrumCore/Rendering/VertexBufferObject.h"

#include <cassert>

namespace Wrum
{
    VertexBufferObject::VertexBufferObject(const float* vertices, long long size)
    {
        Init(vertices, size);
    }

    VertexBufferObject::VertexBufferObject(const Vertices& vertices)
    {
        Init(vertices);
    }

    void VertexBufferObject::Init(const float* vertices, long long size)
    {
        if (_id == 0)
        {
            glGenBuffers(1, &_id);
        }
        
        glBindBuffer(GL_ARRAY_BUFFER, _id);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    void VertexBufferObject::Init(const Vertices& vertices)
    {
        const size_t count = vertices.Positions.size();
        ASSERT(vertices.Normals.size() == count);
        ASSERT(vertices.Colors.size() == count);
        ASSERT(vertices.TexUVs.size() == count);

        const size_t attributeSize = count * sizeof(Vec3);
        const size_t uvSize = count * sizeof(Vec2);
        
        Init(nullptr, 3 * attributeSize + uvSize);
        if (count == 0)
        {
            return;
        }
        
        // Store each attribute in its own contiguous block.
        glBufferSubData(GL_ARRAY_BUFFER, 0, attributeSize, vertices.Positions.data());
        glBufferSubData(GL_ARRAY_BUFFER, attributeSize, attributeSize, vertices.Normals.data());
        glBufferSubData(GL_ARRAY_BUFFER, 2 * attributeSize, attributeSize, vertices.Colors.data());
        glBufferSubData(GL_ARRAY_BUFFER, 3 * attributeSize, uvSize, vertices.TexUVs.data());
    }

    VertexBufferObject::VertexBufferObject(const SimpleVertices& vertices)
    {
        Init(vertices);
    }

    void VertexBufferObject::Init(const SimpleVertices& vertices)
    {
        const size_t count = vertices.Positions.size();
        assert(vertices.Colors.size() == count);
        const size_t attributeSize = count * sizeof(Vec3);
        
        Init(nullptr, 2 * attributeSize);
        if (count == 0)
        {
            return;
        }
        
        glBufferSubData(GL_ARRAY_BUFFER, 0, attributeSize, vertices.Positions.data());
        glBufferSubData(GL_ARRAY_BUFFER, attributeSize, attributeSize, vertices.Colors.data());
    }
    void VertexBufferObject::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, _id);
    }

    void VertexBufferObject::Delete()
    {
        glDeleteBuffers(1, &_id);
        _id = 0;
    }
}
