#pragma once

#include "WrumCore/Rendering/Vertex.h"

namespace Wrum
{
    class VertexBufferObject
    {
    public:
        VertexBufferObject() = default;
        VertexBufferObject(const float* vertices, long long size);
        VertexBufferObject(const Vertices& vertices);
        VertexBufferObject(const SimpleVertices& vertices);
        void Init(const float* vertices, long long size);
        void Init(const Vertices& vertices);
        void Init(const SimpleVertices& vertices);

        void Bind() const;
        void Delete();

        u32 GetId() const { return _id; }

    private:
        u32 _id {};
    };
}
