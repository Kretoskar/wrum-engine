#include "PCH.h"
#include "WrumCore/Rendering/ElementBufferObject.h"

namespace Wrum
{
    ElementBufferObject::ElementBufferObject(uint32_t* indices, long long size)
    {
        Init(indices, size);
    }

    ElementBufferObject::ElementBufferObject(const std::vector<unsigned>& indices)
    {
        Init(indices);
    }

    void ElementBufferObject::Init(const std::vector<unsigned>& indices)
    {
        glGenBuffers(1, &_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned), indices.data(), GL_STATIC_DRAW);
    }

    void ElementBufferObject::Init(uint32_t* indices, long long size)
    {
        glGenBuffers(1, &_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
    }

    void ElementBufferObject::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
    }

    void ElementBufferObject::Delete()
    {
        glDeleteBuffers(1, &_id);
    }
}
