#pragma once
#include "Mat4.h"
#include "Quat.h"
#include "Vec3.h"

namespace Wrum
{
    struct Transform
    {
        Vec3 Position;
        Quat Rotation;
        Vec3 Scale = {1,1,1};
        
        Mat4 ToMat4() const;
    };
}
