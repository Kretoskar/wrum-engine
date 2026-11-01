#pragma once

#include "WrumCore/Math/Vec3.h"

namespace Wrum
{
    struct PointLight
    {
        Vec3 Position = {0.0f, 0.0f, 0.0f};
        Vec3 Color = {1.0f, 1.0f, 1.0f};
        f32 Intensity = 1.0f;
    };
}
