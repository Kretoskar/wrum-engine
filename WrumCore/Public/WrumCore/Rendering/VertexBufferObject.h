#pragma once

#include "WrumCore/Rendering/Vertex.h"

namespace Wrum
{
    class VertexBufferObject
    {
    public:
        VertexBufferObject(const float* vertices, long long size);
        VertexBufferObject(const std::vector<Vertex>& vertices);
        void Init(const float* vertices, long long size);
        void Init(const std::vector<Vertex>& vertices);

        void Bind() const;
        void Delete();

        unsigned int GetId() const { return _id; }

    private:
        unsigned int _id;
    };
}