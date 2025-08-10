#include "PCH.h"
#include "WrumCore/Math/Transform.h"

namespace Wrum
{
    Mat4 Transform::ToMat4() const
    {
        // First, extract the rotation basis of the transform
        Vec3 x = Rotation * Vec3(1, 0, 0);
        Vec3 y = Rotation * Vec3(0, 1, 0);
        Vec3 z = Rotation * Vec3(0, 0, 1);

        // Next, scale the basis vectors
        x = x * Scale.x;
        y = y * Scale.y;
        z = z * Scale.z;

        // Extract the position of the transform
        Vec3 p = Position;

        // Create matrix
        return
        {
        x.x, x.y, x.z, 0, // X basis (& Scale)
        y.x, y.y, y.z, 0, // Y basis (& scale)
        z.x, z.y, z.z, 0, // Z basis (& scale)
        p.x, p.y, p.z, 1 // Position
        };
    }
}
