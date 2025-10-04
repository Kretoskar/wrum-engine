#pragma once

#include "WrumCore/Math/MathCore.h"
#include "WrumCore/Rendering/Mesh/Mesh.h"

namespace Wrum
{
    struct Sphere : public Mesh
    {
        void CreateSphereMesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, float radius, int segments, int rings, const Vec3& color)
        {
            vertices.clear();
            indices.clear();

            vertices.reserve((segments + 1) * (rings + 1));
            indices.reserve(segments * rings * 6); // 2 triangles per quad, 3 indices per triangle
            
            for (int y = 0; y <= rings; ++y)
            {
                float v = static_cast<float>(y) / rings;
                float theta = v * MathCore::PI;  // From 0 to PI

                for (int x = 0; x <= segments; ++x)
                {
                    float u = static_cast<float>(x) / segments;
                    float phi = u * 2.0f * MathCore::PI;  // From 0 to 2PI

                    float sinTheta = sinf(theta);
                    float cosTheta = cosf(theta);
                    float sinPhi = sinf(phi);
                    float cosPhi = cosf(phi);

                    Vec3 position = Vec3(
                        radius * sinTheta * cosPhi,
                        radius * cosTheta,
                        radius * sinTheta * sinPhi
                    );

                    Vec3 normal = position.Normalized();
                    Vec2 texUV = Vec2(u, v);

                    vertices.emplace_back(Vertex{ position, normal, color, texUV });
                }
            }

            // Generate indices
            for (int y = 0; y < rings; ++y)
            {
                for (int x = 0; x < segments; ++x)
                {
                    int i0 = y * (segments + 1) + x;
                    int i1 = i0 + segments + 1;

                    // Two triangles per quad
                    indices.push_back(i0);
                    indices.push_back(i1);
                    indices.push_back(i0 + 1);

                    indices.push_back(i0 + 1);
                    indices.push_back(i1);
                    indices.push_back(i1 + 1);
                }
            }
        }
        
        Sphere(Vec3 color, int32 segments, int32 rings)
        {
            std::vector<Vertex> vertices;
            std::vector<uint32_t> indices;

            CreateSphereMesh(vertices, indices, 0.5f, segments, rings, color);
            
            Init(
            {
                    vertices
            },
            {
                indices
            });
        }
    };
}
