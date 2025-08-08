#pragma once

#include <vector>

namespace Wrum
{
    class ElementBufferObject
    {
    public:
        ElementBufferObject(uint32* indices, long long size);
        ElementBufferObject(const std::vector<unsigned>& indices);
        void Init(const std::vector<unsigned>& indices);
        void Init(uint32* indices, long long size);

        void Bind() const;
        void Delete();

        uint32 GetId() const { return _id; }

    private:
        uint32 _id;
    };
}