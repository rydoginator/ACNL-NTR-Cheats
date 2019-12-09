#include "RAddress.hpp"


namespace CTRPluginFramework
{
    enum Region
    {
        USA,
        EUR,
        JAP,
		KOR,
        w_USA,
        w_EUR,
        w_JAP,
		w_KOR,
    };

    // Global to keep the current region
    Region   g_region = USA;

    template <typename T>
    RAddress<T>::RAddress(T usa, T eur, T jap, T w_usa, T w_eur, T w_jap) :
    Usa(usa), Eur(eur), Jap(jap), w_Usa(w_usa), w_Eur(w_eur), w_Jap(w_jap)
    {
        
    }

    template <typename T>
    T   RAddress<T>::operator()(void)
    {
        if (g_region == EUR)
            return (Eur);
        if (g_region == JAP)
            return (Jap);
        if (g_region == w_USA)
            return (w_Usa);
        if (g_region == w_EUR)
            return (w_Eur);
        if (g_region == w_JAP)
            return (w_Jap);
        return (Usa);
    }

    template class  RAddress<u32>;
}
