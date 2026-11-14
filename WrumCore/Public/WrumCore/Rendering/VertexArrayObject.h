#pragma once


#include "VertexBufferObject.h"

namespace Wrum
{
    class VertexArrayObject
    {
    public:
        VertexArrayObject();

        void LinkAttrib(const VertexBufferObject& vbo, u32 layout, i32 numComponents, u32 type, i32 stride, void* offset);
        void Bind();
        void Delete();

        u32 GetId() const { return _id; }

    private:
        u32 _id;
    };
}