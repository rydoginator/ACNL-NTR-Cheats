#ifndef CTRPLUGINFRAMEWORK_UTILS_LINEREADER_HPP
#define CTRPLUGINFRAMEWORK_UTILS_LINEREADER_HPP

#include "types.h"
#include <string>

namespace CTRPluginFramework
{
    class File;
    class LineReader
    {
    public:
        LineReader(File &file);
        ~LineReader(void);

        // Return true if a line was read
        bool    operator()(std::string &line);

    private:
        File            &_file;
        u32             _offsetInBuffer;
        u32             _dataInBuffer;
        char            *_buffer;
    };
}

#endif