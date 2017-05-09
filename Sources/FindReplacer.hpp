#ifndef FINDREPLACER_HPP
#define FINDREPLACER_HPP

#include "types.h"

#include <vector>

namespace CTRPluginFramework
{
    template <typename T>
    class FindReplacer
    {
    public:
        FindReplacer(void);
        FindReplacer(u32 startAddress, u32 length);
        FindReplacer(u32 startAddress, u32 length, T find, T replace);
        ~FindReplacer(void) {};

        // Add a new search c

        /**
         * \brief Add a new search criteria
         * \param find the value to search for
         * \param replace the value to replace with
         */
        void    AddPair(T find, T replace);


        /**
         * \brief Do the Find & Replace
         */
        void    operator()(void);

    private:
        std::vector<T>  _finds;
        std::vector<T>  _replace;

        u32             _startAddress;
        u32             _length;
    };
}

#endif