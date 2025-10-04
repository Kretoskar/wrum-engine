#pragma once
#include "WrumCore/Math/Vec3.h"

namespace Wrum
{
    class Color
    {
    public:
        static inline Vec3 WHITE = Vec3(1.0f, 1.0f, 1.0f);
        static inline Vec3 BLACK = Vec3(0.0f, 0.0f, 0.0f);
        static inline Vec3 RED = Vec3(1.0f, 0.0f, 0.0f);
        static inline Vec3 GREEN = Vec3(0.0f, 1.0f, 0.0f);
        static inline Vec3 BLUE = Vec3(0.0f, 0.0f, 1.0f);

        static inline Vec3 YELLOW     = Vec3(1.0f, 1.0f, 0.0f);
        static inline Vec3 CYAN       = Vec3(0.0f, 1.0f, 1.0f);
        static inline Vec3 MAGENTA    = Vec3(1.0f, 0.0f, 1.0f);
        static inline Vec3 ORANGE     = Vec3(1.0f, 0.5f, 0.0f);
        static inline Vec3 PURPLE     = Vec3(0.5f, 0.0f, 0.5f);
        static inline Vec3 PINK       = Vec3(1.0f, 0.75f, 0.8f);
        static inline Vec3 BROWN      = Vec3(0.6f, 0.3f, 0.0f);
        static inline Vec3 GRAY       = Vec3(0.5f, 0.5f, 0.5f);
        static inline Vec3 DARK_GRAY  = Vec3(0.25f, 0.25f, 0.25f);
        static inline Vec3 LIGHT_GRAY = Vec3(0.75f, 0.75f, 0.75f);
        static inline Vec3 LIME       = Vec3(0.75f, 1.0f, 0.0f);
        static inline Vec3 TEAL       = Vec3(0.0f, 0.5f, 0.5f);
        static inline Vec3 NAVY       = Vec3(0.0f, 0.0f, 0.5f);
        static inline Vec3 MAROON     = Vec3(0.5f, 0.0f, 0.0f);

        static inline Vec3 PASTEL_RED     = Vec3(1.0f, 0.6f, 0.6f);
        static inline Vec3 PASTEL_GREEN   = Vec3(0.6f, 1.0f, 0.6f);
        static inline Vec3 PASTEL_BLUE    = Vec3(0.6f, 0.8f, 1.0f);
        static inline Vec3 PASTEL_YELLOW  = Vec3(1.0f, 1.0f, 0.6f);
        static inline Vec3 PASTEL_ORANGE  = Vec3(1.0f, 0.8f, 0.6f);
        static inline Vec3 PASTEL_PURPLE  = Vec3(0.8f, 0.6f, 1.0f);
        static inline Vec3 PASTEL_PINK    = Vec3(1.0f, 0.75f, 0.8f);
        static inline Vec3 PASTEL_CYAN    = Vec3(0.6f, 1.0f, 1.0f);
        static inline Vec3 PASTEL_LIME    = Vec3(0.8f, 1.0f, 0.6f);
        static inline Vec3 PASTEL_PEACH   = Vec3(1.0f, 0.85f, 0.7f);
        static inline Vec3 PASTEL_MINT    = Vec3(0.7f, 1.0f, 0.9f);
        static inline Vec3 PASTEL_LAVENDER= Vec3(0.9f, 0.8f, 1.0f);
    };
}
