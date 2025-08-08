#pragma once

#include <memory>

#include "WrumCore/Rendering/Camera.h"
#include "WrumCore/Rendering/ElementBufferObject.h"
#include "WrumCore/Rendering/VertexArrayObject.h"
#include "WrumCore/Rendering/VertexBufferObject.h"
#include "WrumCore/Rendering/Shader.h"
#include "WrumCore/Rendering/Vertex.h"
#include "WrumCore/Math/Vec3.h"

namespace Wrum
{
    class DebugRenderer
    {
    public:
        bool Init();
        void Render(const Camera& camera);
        void AddLine(Vec3 start, Vec3 end, Vec3 color);
        void DrawNet(unsigned count, float stride, float size, Vec3 color);

    private:
        ArenaAllocator _arena = ArenaAllocator(2048 * 2048);
        
        Shader* _shader = nullptr;
        VertexBufferObject* _lineVbo = nullptr;
        ElementBufferObject* _lineEbo = nullptr;
        VertexArrayObject* _lineVao = nullptr;

        static constexpr unsigned MAX_LINE_COUNT = 4096;
        uint32_t _lineCount = 0;
        SimpleVertex* _lineVertices = nullptr;

        uint32* _lineIndices = nullptr;
    };

}