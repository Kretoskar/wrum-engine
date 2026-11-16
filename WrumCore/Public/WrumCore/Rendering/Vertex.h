#pragma once

#include <cstddef>
#include <vector>

#include "WrumCore/Math/Vec3.h"
#include "WrumCore/Math/Vec2.h"

namespace Wrum
{
    struct Vertices
    {
        std::vector<Vec3> Positions;
        std::vector<Vec3> Normals;
        std::vector<Vec3> Colors;
        std::vector<Vec2> TexUVs;

        void Clear()
        {
            Positions.clear();
            Normals.clear();
            Colors.clear();
            TexUVs.clear();
        }

        void Reserve(std::size_t count)
        {
            Positions.reserve(count);
            Normals.reserve(count);
            Colors.reserve(count);
            TexUVs.reserve(count);
        }

        void Add(Vec3 position, Vec3 normal, Vec3 color, Vec2 texUV)
        {
            Positions.push_back(position);
            Normals.push_back(normal);
            Colors.push_back(color);
            TexUVs.push_back(texUV);
        }
    };

    struct SimpleVertices
    {
        std::vector<Vec3> Positions;
        std::vector<Vec3> Colors;
    };
}
