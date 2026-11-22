#pragma once

#include "WrumCore/Math/Mat4.h"
#include "WrumCore/ResourceHandling/ResourceID.h"

namespace Wrum
{
    struct Entity
    {
        Mat4 Transform;
        ResourceID MeshID;
        ResourceID MaterialID;
    };
}