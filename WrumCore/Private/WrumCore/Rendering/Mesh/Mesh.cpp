#include "PCH.h"

#include "WrumCore/Rendering/Mesh/Mesh.h"

#include "WrumCore/Rendering/ElementBufferObject.h"

void Wrum::Mesh::Bind()
{
    _vao.Bind();
}

void Wrum::Mesh::Init(const std::vector<Vertex>& vertices, std::vector<uint32_t> indices)
{
    Vertices = vertices;
    Indices = indices;

    // already created in vao constructor
    _vao.Bind();

    const VertexBufferObject vbo = VertexBufferObject(vertices);
    const ElementBufferObject ebo = ElementBufferObject(indices);

    // position
    _vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
    //normals
    _vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
    // color
    _vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
    // UV
    _vao.LinkAttrib(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));
}
