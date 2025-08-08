#include "PCH.h"
#include "WrumCore/Rendering/VertexArrayObject.h"

namespace Wrum
{
    VertexArrayObject::VertexArrayObject()
    {
        glGenVertexArrays(1, &_id);
    }

    void VertexArrayObject::LinkAttrib(const VertexBufferObject& vbo, unsigned layout, int numComponents,
        unsigned type, int stride, void* offset)
    {
        vbo.Bind();
        glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
        glEnableVertexAttribArray(layout);
    }

    void VertexArrayObject::Bind()
    {
        glBindVertexArray(_id);
    }

    void VertexArrayObject::Delete()
    {
        glDeleteVertexArrays(1, &_id);
    }

}