#pragma once

#include "WrumCore/Math/Vec3.h"
#include "WrumCore/Math/Vec2.h"

namespace Wrum
{
    struct Vertex
    {
        Vec3 Position;
        Vec3 Normal;
        Vec3 Color;
        Vec2 TexUV;
    };

    struct SimpleVertex
    {
        SimpleVertex() = default;

        SimpleVertex(Vec3 pos, Vec3 color)
            : X(pos.x), Y(pos.y), Z(pos.z), R(color.r), G(color.g), B(color.b) {}
        SimpleVertex(float x, float y, float z, float r, float g, float b)
            : X(x), Y(y), Z(z), R(r), G(g), B(b) {}

        float X{}, Y{}, Z{};
        float R{}, G{}, B{};
    };
}