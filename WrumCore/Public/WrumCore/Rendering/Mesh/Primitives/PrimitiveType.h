#pragma once

namespace Wrum
{
    enum class PrimitiveType : u16
    {
        Sphere = MAKE_TAG16('S', 'P'),
        Cube  = MAKE_TAG16('C', 'U'),
        Plane = MAKE_TAG16('P', 'L'),
        Arrow = MAKE_TAG16('A', 'R')
    };
}
