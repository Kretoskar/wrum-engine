#pragma once
#include "WrumCore/Rendering/Vertex.h"

namespace Wrum
{
    struct Mesh
    {
        std::vector<Vertex> Vertices;
        std::vector<unsigned> Indices;
    };
}
