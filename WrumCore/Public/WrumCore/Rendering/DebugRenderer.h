#pragma once

#include <memory>

#include "WrumCore/Core/Time.h"
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
        bool Init(ArenaAllocator& arena);
        void Update(float deltaTime);
        void Render(const Camera& camera);
        
        void DrawLine(Vec3 start, Vec3 end, Vec3 color);
        void DrawLine(Vec3 start, Vec3 end, Vec3 color, float lifetime, TimeUnit timeUnit = TimeUnit::Seconds);
        
        void DrawNet(unsigned count, float stride, float size, Vec3 color);
        
        void DrawCoordinateSystem();

        void DrawLightBulb(Vec3 position, Vec3 color, float size = 0.15f);

    private:
        struct LightBulbGizmo
        {
            Vec3 Position;
            Vec3 Color;
            float Size;
        };

        void DrawLightBulbLines(const Camera& camera, const LightBulbGizmo& gizmo);
        std::vector<LightBulbGizmo> _lightBulbs;

        Shader* _shader = nullptr;
        VertexBufferObject* _lineVbo = nullptr;
        ElementBufferObject* _lineEbo = nullptr;
        VertexArrayObject* _lineVao = nullptr;

        u32 _lineCount = 0;
        
        static constexpr unsigned MAX_LINE_COUNT = 4096;
        SimpleVertex _lineVertices[MAX_LINE_COUNT * 2];
        u32 _lineIndices[MAX_LINE_COUNT * 2] = {};

        struct DebugVertexLifetime
        {
            u32 Index{};
            float TimeLeft{};
        };
        
        std::vector<DebugVertexLifetime> _lifetimesLeft;
    };

}
