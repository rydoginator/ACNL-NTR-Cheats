#ifndef REGIONADDRESS_HPP
#define REGIONADDRESS_HPP

#include "types.h"

namespace CTRPluginFramework
{
    template <typename T>
    class RAddress
    {
    public:

        // Constructor
        RAddress(T usa, T eur, T jap);
        ~RAddress(){}

        // Return the value according to the current region
        T   operator()(void);

        // Properties
        const T Usa;
        const T Eur;
        const T Jap;
    };

    using AutoRegion = RAddress<u32>;
}

#endif
