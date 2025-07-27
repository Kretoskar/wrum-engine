#include "PCH.h"
#include "AnimBoxCore/Rendering/Renderer.h"

AnimBox::VertexBufferObject::VertexBufferObject(float* vertices, long long size)
{
    Init(vertices, size);
}

AnimBox::VertexBufferObject::VertexBufferObject(const std::vector<Vertex>& vertices)
{
    Init(vertices);;
}

void AnimBox::VertexBufferObject::Init(float* vertices, long long size)
{
    glGenBuffers(1, &_id);
    glBindBuffer(GL_ARRAY_BUFFER, _id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void AnimBox::VertexBufferObject::Init(const std::vector<Vertex>& vertices)
{
    glGenBuffers(1, &_id);
    glBindBuffer(GL_ARRAY_BUFFER, _id);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

void AnimBox::VertexBufferObject::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, _id);
}

void AnimBox::VertexBufferObject::Delete()
{
    glDeleteBuffers(1, &_id);
}

AnimBox::VertexArrayObject::VertexArrayObject()
{
    glGenVertexArrays(1, &_id);
}

void AnimBox::VertexArrayObject::LinkAttrib(const VertexBufferObject& vbo, unsigned layout, int numComponents,
    unsigned type, int stride, void* offset)
{
    vbo.Bind();
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
}

void AnimBox::VertexArrayObject::Bind()
{
    glBindVertexArray(_id);
}

void AnimBox::VertexArrayObject::Delete()
{
    glDeleteVertexArrays(1, &_id);
}
