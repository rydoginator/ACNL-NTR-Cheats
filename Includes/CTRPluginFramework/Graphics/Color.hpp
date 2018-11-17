#ifndef CTRPLUGINFRAMEWORK_COLOR_HPP
#define CTRPLUGINFRAMEWORK_COLOR_HPP

#include "types.h"
#include <algorithm>
#include <string>

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

        operator std::string() const
        {
            char  strColor[5] = { 0 };

            strColor[0] = 0x1B;
            strColor[1] = std::max((u8)1, r);
            strColor[2] = std::max((u8)1, g);
            strColor[3] = std::max((u8)1, b);

            return strColor;
        }

        union
        {
            u32     raw;
            struct
            {
                u8      r;
                u8      g;
                u8      b;
                u8      a;
            };
        };

        // All those colors are from https://www.rapidtables.com/web/color/RGB_Color.html
        // Some basic colors constants
        static const Color  Black;
        static const Color  White;
        static const Color  Red;
        static const Color  Lime;
        static const Color  Blue;
        static const Color  Yellow;
        static const Color  Cyan;
        static const Color  Magenta;
        static const Color  Silver;
        static const Color  Gray;
        static const Color  Maroon;
        static const Color  Olive;
        static const Color  Green;
        static const Color  Purple;
        static const Color  Teal;
        static const Color  Navy;

        static const Color  BlackGrey;
        static const Color  Brown;
        static const Color  DarkGrey;
        static const Color  DeepSkyBlue;
        static const Color  DimGrey;
        static const Color  DodgerBlue;
        static const Color  Gainsboro;
        static const Color  ForestGreen;
        static const Color  LimeGreen;
        static const Color  Orange;
        static const Color  SkyBlue;
        static const Color  Turquoise;
    };
}

#endif