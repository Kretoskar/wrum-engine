#include "PCH.h"
#include "WrumCore/Rendering/Renderer.h"

Wrum::VertexBufferObject::VertexBufferObject(float* vertices, long long size)
{
    Init(vertices, size);
}

Wrum::VertexBufferObject::VertexBufferObject(const std::vector<Vertex>& vertices)
{
    Init(vertices);;
}

void Wrum::VertexBufferObject::Init(float* vertices, long long size)
{
    glGenBuffers(1, &_id);
    glBindBuffer(GL_ARRAY_BUFFER, _id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void Wrum::VertexBufferObject::Init(const std::vector<Vertex>& vertices)
{
    glGenBuffers(1, &_id);
    glBindBuffer(GL_ARRAY_BUFFER, _id);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

void Wrum::VertexBufferObject::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, _id);
}

void Wrum::VertexBufferObject::Delete()
{
    glDeleteBuffers(1, &_id);
}

Wrum::VertexArrayObject::VertexArrayObject()
{
    glGenVertexArrays(1, &_id);
}

void Wrum::VertexArrayObject::LinkAttrib(const VertexBufferObject& vbo, unsigned layout, int numComponents,
    unsigned type, int stride, void* offset)
{
    vbo.Bind();
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
}

void Wrum::VertexArrayObject::Bind()
{
    glBindVertexArray(_id);
}

void Wrum::VertexArrayObject::Delete()
{
    glDeleteVertexArrays(1, &_id);
}
