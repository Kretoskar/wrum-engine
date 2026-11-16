#pragma once

#include "WrumCore/Rendering/Mesh/Mesh.h"

namespace Wrum
{
    struct Cube : public Mesh
    {
        Cube(Vec3 color)
        {
            Init(Wrum::Vertices{
                {
                    Vec3(-0.5f, -0.5f,  0.5f),
                    Vec3(-0.5f,  0.5f,  0.5f),
                    Vec3( 0.5f,  0.5f,  0.5f),
                    Vec3( 0.5f, -0.5f,  0.5f),
                    Vec3( 0.5f, -0.5f, -0.5f),
                    Vec3( 0.5f,  0.5f, -0.5f),
                    Vec3(-0.5f,  0.5f, -0.5f),
                    Vec3(-0.5f, -0.5f, -0.5f),
                    Vec3(-0.5f, -0.5f, -0.5f),
                    Vec3(-0.5f,  0.5f, -0.5f),
                    Vec3(-0.5f,  0.5f,  0.5f),
                    Vec3(-0.5f, -0.5f,  0.5f),
                    Vec3(0.5f, -0.5f,  0.5f),
                    Vec3(0.5f,  0.5f,  0.5f),
                    Vec3(0.5f,  0.5f, -0.5f),
                    Vec3(0.5f, -0.5f, -0.5f),
                    Vec3(-0.5f, 0.5f,  0.5f),
                    Vec3(-0.5f, 0.5f, -0.5f),
                    Vec3( 0.5f, 0.5f, -0.5f),
                    Vec3( 0.5f, 0.5f,  0.5f),
                    Vec3(-0.5f, -0.5f, -0.5f),
                    Vec3(-0.5f, -0.5f,  0.5f),
                    Vec3( 0.5f, -0.5f,  0.5f),
                    Vec3( 0.5f, -0.5f, -0.5f),
                },
                {
                    Vec3(0.0f, 0.0f, 0.5f),
                    Vec3(0.0f, 0.0f, 0.5f),
                    Vec3(0.0f, 0.0f, 0.5f),
                    Vec3(0.0f, 0.0f, 0.5f),
                    Vec3(0.0f, 0.0f, -0.5f),
                    Vec3(0.0f, 0.0f, -0.5f),
                    Vec3(0.0f, 0.0f, -0.5f),
                    Vec3(0.0f, 0.0f, -0.5f),
                    Vec3(-0.5f, 0.0f, 0.0f),
                    Vec3(-0.5f, 0.0f, 0.0f),
                    Vec3(-0.5f, 0.0f, 0.0f),
                    Vec3(-0.5f, 0.0f, 0.0f),
                    Vec3(0.5f, 0.0f, 0.0f),
                    Vec3(0.5f, 0.0f, 0.0f),
                    Vec3(0.5f, 0.0f, 0.0f),
                    Vec3(0.5f, 0.0f, 0.0f),
                    Vec3(0.0f, 0.5f, 0.0f),
                    Vec3(0.0f, 0.5f, 0.0f),
                    Vec3(0.0f, 0.5f, 0.0f),
                    Vec3(0.0f, 0.5f, 0.0f),
                    Vec3(0.0f, -0.5f, 0.0f),
                    Vec3(0.0f, -0.5f, 0.0f),
                    Vec3(0.0f, -0.5f, 0.0f),
                    Vec3(0.0f, -0.5f, 0.0f),
                },
                std::vector<Vec3>(24, color),
                {
                    Vec2(0.0f, 1.0f),
                    Vec2(0.0f, 0.0f),
                    Vec2(1.0f, 0.0f),
                    Vec2(1.0f, 1.0f),
                    Vec2(0.0f, 1.0f),
                    Vec2(0.0f, 0.0f),
                    Vec2(1.0f, 0.0f),
                    Vec2(1.0f, 1.0f),
                    Vec2(0.0f, 1.0f),
                    Vec2(0.0f, 0.0f),
                    Vec2(1.0f, 0.0f),
                    Vec2(1.0f, 1.0f),
                    Vec2(0.0f, 1.0f),
                    Vec2(0.0f, 0.0f),
                    Vec2(1.0f, 0.0f),
                    Vec2(1.0f, 1.0f),
                    Vec2(0.0f, 1.0f),
                    Vec2(0.0f, 0.0f),
                    Vec2(1.0f, 0.0f),
                    Vec2(1.0f, 1.0f),
                    Vec2(0.0f, 1.0f),
                    Vec2(0.0f, 0.0f),
                    Vec2(1.0f, 0.0f),
                    Vec2(1.0f, 1.0f),
                }
            },
            {
                 // Front face
                 0, 1, 2, 0, 2, 3,
                 // Back face
                 4, 5, 6, 4, 6, 7,
                 // Left face
                 8, 9,10, 8,10,11,
                 // Right face
                12,13,14,12,14,15,
                 // Top face
                16,17,18,16,18,19,
                 // Bottom face
                20,21,22,20,22,23
            });
        }};
}
