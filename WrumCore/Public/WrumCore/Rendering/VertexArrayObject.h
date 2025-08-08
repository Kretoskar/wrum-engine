#pragma once


#include "VertexBufferObject.h"

namespace Wrum
{
    class VertexArrayObject
    {
    public:
        VertexArrayObject();

        void LinkAttrib(const VertexBufferObject& vbo, unsigned layout, int numComponents, unsigned type, int stride, void* offset);
        void Bind();
        void Delete();

        unsigned int GetId() const { return _id; }

    private:
        unsigned int _id;
    };
}