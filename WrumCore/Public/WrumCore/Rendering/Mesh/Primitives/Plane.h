#pragma once

#include "WrumCore/Rendering/Mesh/Mesh.h"

namespace Wrum
{
    struct Plane : public Mesh
    {
        Plane(Vec3 color)
        {
            Init(
            {
                    // position normal color texuv
                    Vertex{Vec3(-1.0f, 0.0f,  1.0f), Vec3(0.0f, 1.0f, 0.0f), color, Vec2(0.0f, 0.0f)},
                    Vertex{Vec3(-1.0f, 0.0f, -1.0f), Vec3(0.0f, 1.0f, 0.0f), color, Vec2(0.0f, 1.0f)},
                    Vertex{Vec3(1.0f, 0.0f, -1.0f), Vec3(0.0f, 1.0f, 0.0f), color, Vec2(1.0f, 1.0f)},
                    Vertex{Vec3(1.0f, 0.0f,  1.0f), Vec3(0.0f, 1.0f, 0.0f), color, Vec2(1.0f, 0.0f)}
            },
            {
                    0, 1, 2,
                    0, 2, 3
            });
        }
    };
}
