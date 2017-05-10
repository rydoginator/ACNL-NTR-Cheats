#include "RAddress.hpp"


namespace CTRPluginFramework
{
    enum Region
    {
        USA,
        EUR,
        JAP
    };

    // Global to keep the current region
    Region   g_region = USA;

    template <typename T>
    RAddress<T>::RAddress(T usa, T eur, T jap) :
    Usa(usa), Eur(eur), Jap(jap)
    {
        
    }

    template <typename T>
    T   RAddress<T>::operator()(void)
    {
        if (g_region == EUR)
            return (Eur);
        if (g_region == JAP)
            return (Jap);
        return (Usa);
    }

    template class  RAddress<u32>;
}
