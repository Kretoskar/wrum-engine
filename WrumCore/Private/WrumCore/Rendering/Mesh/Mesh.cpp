#include "PCH.h"

#include "WrumCore/Rendering/Mesh/Mesh.h"

#include "WrumCore/Rendering/ElementBufferObject.h"

void Wrum::Mesh::Bind()
{
    _vao.Bind();
}

void Wrum::Mesh::BindInstanceTransforms(const std::vector<Mat4>& transforms)
{
    _vao.Bind();
    if (_instanceVbo == 0)
    {
        glGenBuffers(1, &_instanceVbo);
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, _instanceVbo);
    glBufferData(GL_ARRAY_BUFFER, transforms.size() * sizeof(Mat4), transforms.data(), GL_STREAM_DRAW);
    
    for (u32 column = 0; column < 4; ++column)
    {
        const u32 location = 4 + column;
        glEnableVertexAttribArray(location);
        glVertexAttribPointer(location, 4, GL_FLOAT, GL_FALSE, sizeof(Mat4), reinterpret_cast<void*>(column * sizeof(Vec4)));
        glVertexAttribDivisor(location, 1);
    }
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
