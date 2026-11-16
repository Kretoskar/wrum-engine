#include "PCH.h"

#include "WrumCore/Rendering/Mesh/Mesh.h"

#include "WrumCore/Rendering/ElementBufferObject.h"

void Wrum::Mesh::Bind()
{
    _vao.Bind();
}

void Wrum::Mesh::Init(Wrum::Vertices&& vertices, std::vector<u32>&& indices)
{
    Vertices = std::move(vertices);
    Indices = std::move(indices);

    // already created in vao constructor
    _vao.Bind();

    const VertexBufferObject vbo = VertexBufferObject(Vertices);
    const ElementBufferObject ebo = ElementBufferObject(Indices);

    const size_t attributeSize = Vertices.Positions.size() * sizeof(Vec3);
    _vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vec3), nullptr);
    _vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vec3), reinterpret_cast<void*>(attributeSize));
    _vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(Vec3), reinterpret_cast<void*>(2 * attributeSize));
    _vao.LinkAttrib(vbo, 3, 2, GL_FLOAT, sizeof(Vec2), reinterpret_cast<void*>(3 * attributeSize));
}
