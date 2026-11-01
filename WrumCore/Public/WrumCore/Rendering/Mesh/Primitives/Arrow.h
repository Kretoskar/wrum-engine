#pragma once

#include <cmath>

#include "WrumCore/Math/MathCore.h"
#include "WrumCore/Rendering/Mesh/Mesh.h"

namespace Wrum
{
    // Arrow pointing along +Y, with its base at the origin
    struct Arrow : public Mesh
    {
        void CreateArrowMesh(std::vector<Vertex>& vertices, std::vector<u32>& indices, float length, float arrowheadAlpha, i32 segments, const Vec3& color)
        {
            vertices.clear();
            indices.clear();
            if (length <= 0.0f)
            {
                return;
            }

            arrowheadAlpha = MathCore::Clamp(arrowheadAlpha, 0.0f, 1.0f);
            if (segments < 3)
            {
                segments = 3;
            }

            constexpr f32 shaftRadius = 0.035f;
            f32 shaftLength = length * arrowheadAlpha;
            f32 headLength = length - shaftLength;
            bool hasShaft = shaftLength > 0.0f;
            bool hasHead = headLength > 0.0f;
            f32 headRadius = hasHead ? 0.1f : shaftRadius;
            constexpr u32 verticesPerRing = 7;

            vertices.reserve((static_cast<size_t>(segments) + 1) * verticesPerRing + 1);
            indices.reserve(static_cast<size_t>(segments) * 18);

            for (i32 i = 0; i <= segments; ++i)
            {
                f32 u = static_cast<f32>(i) / segments;
                f32 angle = i == segments ? 0.0f : u * 2.0f * MathCore::PI;
                f32 c = std::cos(angle);
                f32 s = std::sin(angle);
                
                Vec3 radialNormal(c, 0.0f, s);
                Vec3 down(0.0f, -1.0f, 0.0f);
                Vec3 headCapNormal(0.0f, hasHead ? -1.0f : 1.0f, 0.0f);
                Vec3 bottom(shaftRadius * c, 0.0f, shaftRadius * s);
                Vec3 shaftTop(shaftRadius * c, shaftLength, shaftRadius * s);
                Vec3 headBase(headRadius * c, shaftLength, headRadius * s);

                // Shaft sides (0, 1); separate cap vertices keep the edges sharp
                vertices.push_back(Vertex{bottom, radialNormal, color, Vec2(u, 0.0f)});
                vertices.push_back(Vertex{shaftTop, radialNormal, color, Vec2(u, arrowheadAlpha)});

                // Bottom cap (2) and the head underside or shaft top cap (3, 4).
                Vec2 capUV(0.5f + 0.5f * c, 0.5f + 0.5f * s);
                Vec2 innerUV(0.5f + 0.5f * shaftRadius / headRadius * c, 0.5f + 0.5f * shaftRadius / headRadius * s);
                vertices.push_back(Vertex{hasShaft ? bottom : headBase, down, color, capUV});
                vertices.push_back(Vertex{shaftTop, headCapNormal, color, innerUV});
                vertices.push_back(Vertex{headBase, headCapNormal, color, capUV});

                // Cone side (5) and a tip normal for this segment (6).
                Vec3 coneNormal = Vec3(headLength * c, headRadius, headLength * s).Normalized();
                f32 tipU = i == segments ? 1.0f : (static_cast<f32>(i) + 0.5f) / segments;
                f32 tipAngle = tipU * 2.0f * MathCore::PI;
                Vec3 tipNormal = Vec3(headLength * std::cos(tipAngle), headRadius, headLength * std::sin(tipAngle)).Normalized();
                vertices.push_back(Vertex{headBase, coneNormal, color, Vec2(u, arrowheadAlpha)});
                vertices.push_back(Vertex{Vec3(0.0f, length, 0.0f), tipNormal, color, Vec2(tipU, 1.0f)});
            }

            u32 bottomCenter = static_cast<u32>(vertices.size());
            vertices.push_back(Vertex{Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, -1.0f, 0.0f), color, Vec2(0.5f, 0.5f)});

            for (i32 i = 0; i < segments; ++i)
            {
                u32 current = static_cast<u32>(i) * verticesPerRing;
                u32 next = current + verticesPerRing;

                // Counter-clockwise triangles viewed from outside each surface.
                if (hasShaft)
                {
                    indices.insert(indices.end(), {
                        current, current + 1, next,
                        next, current + 1, next + 1
                    });
                }

                indices.insert(indices.end(), {bottomCenter, current + 2, next + 2});

                if (hasHead)
                {
                    if (hasShaft)
                    {
                        indices.insert(indices.end(), {
                            current + 3, current + 4, next + 4,
                            current + 3, next + 4, next + 3
                        });
                    }
                    indices.insert(indices.end(), {current + 5, current + 6, next + 5});
                }
                else
                {
                    // With no head, close the shaft with an upward-facing disk.
                    indices.insert(indices.end(), {current + 6, next + 3, current + 3});
                }
            }
        }
        
        Arrow(Vec3 color, float length = 1.0f, float arrowheadAlpha = 0.75f, i32 segments = 32)
        {
            std::vector<Vertex> vertices;
            std::vector<u32> indices;
            CreateArrowMesh(vertices, indices, length, arrowheadAlpha, segments, color);
            Init(vertices, indices);
        }
    };
}
