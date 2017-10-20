#ifndef CTRPLUGINFRAMEWORK_COLOR_HPP
#define CTRPLUGINFRAMEWORK_COLOR_HPP

#include "types.h"

namespace CTRPluginFramework
{
    class Color
    {
    public:

        enum class BlendMode
        {
            Alpha,
            Add,
            Sub,
            Mul,
            None
        };

        Color(void) : r(0), g(0), b(0), a(255) {}
        Color(u32 color);
        Color(u8 red, u8 green, u8 blue, u8 alpha = 255); 

        u32     ToU32(void) const;
        Color   &Fade(double fading);
        Color   Blend(const Color &color, BlendMode mode) const;

        bool    operator == (const Color &right) const;
        bool    operator != (const Color &right) const;
        bool    operator < (const Color &right) const;
        bool    operator <= (const Color &right) const;
        bool    operator > (const Color &right) const;
        bool    operator >= (const Color &right) const;
        Color   operator + (const Color &right) const;
        Color   operator - (const Color &right) const;
        Color   operator * (const Color &right) const;
        Color   &operator += (const Color &right);
        Color   &operator -= (const Color &right);
        Color   &operator *= (const Color &right); 

        u8      r;
        u8      g;
        u8      b;
        u8      a;

        static const Color  Black;
        static const Color  Blank;
        static const Color  BlackGrey;
        static const Color  Blue;
        static const Color  Brown;
        static const Color  DarkGrey;
        static const Color  DeepSkyBlue;
        static const Color  DimGrey;
        static const Color  DodgerBlue;
        static const Color  Gainsboro;
        static const Color  Green;
        static const Color  Grey;
        static const Color  LimeGreen;
        static const Color  Magenta;
        static const Color  Orange;
        static const Color  Red;
        static const Color  Silver;
        static const Color  SkyBlue;
        static const Color  Turquoise;
        static const Color  Yellow;
    };
}

#endif