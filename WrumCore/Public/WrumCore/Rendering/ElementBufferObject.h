#pragma once

#include <vector>

namespace Wrum
{
    class ElementBufferObject
    {
    public:
        ElementBufferObject() = default;
        ElementBufferObject(u32* indices, long long size);
        ElementBufferObject(const std::vector<unsigned>& indices);
        void Init(const std::vector<unsigned>& indices);
        void Init(u32* indices, long long size);

        void Bind() const;
        void Delete();

        u32 GetId() const { return _id; }

    private:
        u32 _id{};
    };
}