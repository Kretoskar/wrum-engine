#pragma once

#include "WrumCore/Rendering/Mesh/Mesh.h"

namespace Wrum
{
    struct Plane : public Mesh
    {
        Plane(Vec3 color)
        {
            Init(Wrum::Vertices{
                {
                    Vec3(-0.5f, 0.0f,  0.5f),
                    Vec3(-0.5f, 0.0f, -0.5f),
                    Vec3(0.5f, 0.0f, -0.5f),
                    Vec3(0.5f, 0.0f,  0.5f),
                },
                {
                    Vec3(0.0f, 0.5f, 0.0f),
                    Vec3(0.0f, 0.5f, 0.0f),
                    Vec3(0.0f, 0.5f, 0.0f),
                    Vec3(0.0f, 0.5f, 0.0f),
                },
                std::vector<Vec3>(4, color),
                {
                    Vec2(0.0f, 0.0f),
                    Vec2(0.0f, 1.0f),
                    Vec2(1.0f, 1.0f),
                    Vec2(1.0f, 0.0f),
                }
            },
            {
                    0, 1, 2,
                    0, 2, 3
            });
        }
    };
}
