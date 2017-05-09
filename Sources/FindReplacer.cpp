#include "FindReplacer.hpp"
#include "CTRPluginFramework/System/Process.hpp"

namespace CTRPluginFramework
{
    template <typename T>
    FindReplacer<T>::FindReplacer(void): 
        _startAddress(0), _length(0)
    {
    }

    template <typename T>
    FindReplacer<T>::FindReplacer(u32 start, u32 size) :
        _startAddress(start), _length(size)
    {
    }

    template <typename T>
    FindReplacer<T>::FindReplacer(u32 start, u32 size, T find, T replace) :
        _startAddress(start), _length(size)
    {
        _finds.push_back(find);
        _replace.push_back(replace);
    }

    template <typename T>
    void    FindReplacer<T>::AddPair(T find, T replace)
    {
        _finds.push_back(find);
        _replace.push_back(replace);
    }

    template <typename T>
    void    FindReplacer<T>::operator()(void)
    {
        if (_startAddress == 0 || _length == 0)
            return;
        if (_finds.empty() || _replace.empty())
            return;

        // Check that the range is valid
        if (!Process::ProtectMemory(_startAddress, _length))
            return;

        u32     end = _startAddress + _length;
        T       *pointer = reinterpret_cast<T *>(_startAddress);

        while (static_cast<u32>(pointer) < end)
        {
            T   val = *pointer;

            for (int i = 0; i < _finds.size(); i++)
            {
                if (val == _finds[i])
                {
                    *pointer = _replace[i];
                    break;
                }                    
            }

            ++pointer;
        }
    }
}
