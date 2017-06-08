#ifndef CTRPLUGINFRAMEWORK_FILE_HPP
#define CTRPLUGINFRAMEWORK_FILE_HPP

#include "types.h"
#include <string>
#include <vector>

namespace CTRPluginFramework
{
    class File
    {
    public:

        enum SeekPos
        {
            CUR,
            SET,
            END
        };

        enum Mode
        {
            READ = 1,           ///< Gives read permission
            WRITE = 1 << 1,     ///< Gives write permission
            CREATE = 1 << 2,    ///< The file will be created if it doesn't exist
            APPEND = 1 << 3,    ///< You'll be unable to overwrite the file, only append data to it
            TRUNCATE = 1 << 4,  ///< Will clear the file
            SYNC = 1 << 5       ///< Will flush and update time on each write
        };

        /*
        ** Create a file
        ** path = the path of the file to create
        ** return value:
        ** -1 : Invalid Path
        ** Other : result value by FS
        ** 0 : Success
        *************************************************/
        static int  Create(std::string path);
        /*
        ** Rename a file
        ** path = old name
        ** newpath = new name
        ** return value:
        ** -1 : Invalid Path
        ** Other : result value by FS
        ** 0 : Success
        *************************************************/
        static int  Rename(std::string path, std::string newpath);
        /*
        ** Remove a file
        ** path = the path of the file to remove
        ** return value:
        ** -1 : Invalid Path
        ** Other : result value by FS
        ** 0 : Success
        *************************************************/
        static int  Remove(std::string path);
        /*
        ** Check if a file exists
        ** path = the path of the file to check
        ** return value:
        ** -1 : Invalid Path
        ** 0 : File doesn't exists
        ** 1 : File exists
        ** Other : result value by FS
        *************************************************/
        static int  Exists(std::string path);
        /*
        ** Open a file
        ** output = resulting file object
        ** path = the path of the file to open
        ** mode = mode to open the file
        ** return value:
        ** -1 : Invalid Path
        ** 0 : Success        
        ** Other : result value by FS
        *************************************************/
        static int  Open(File &output, std::string path, int mode = READ | WRITE | SYNC);
        /*
        ** Close a file
        ** return value:     
        ** 0 : Success
        ** Other : result value by FS
        *************************************************/
        ~File(){ Close(); }


        int     Close(void);
        /*
        ** Read a file
        ** buffer = where to read the file data, ensure the buffer is large enough
        ** length = size to read
        ** return value:
        ** -1 : Invalid Path
        ** 0 : Success        
        ** Other : result value by FS
        *************************************************/
        int     Read(void *buffer, u32 length);
        /*
        ** Write into a  file
        ** data = data to write
        ** length = length to write
        ** return value:
        ** -1 : buffer invalid (null)
        ** 0 : Success        
        ** Other : result value by FS
        *************************************************/
        int     Write(const void *data, u32 length);
        /*
        ** Write a string to a file (auto append '\n')
        ** line = text to write
        ** return value:
        ** -1 : data is null || the file doesn't have WRITE mode
        ** 0 : Success        
        ** Other : result value by FS
        *************************************************/
        int     WriteLine(std::string line);
        /*
        ** Set the offset of the file (for further operation such as read / write)
        ** offset = offset value
        ** rel = start point of applying the offset to
        ** return value:
        ** -1 : Invalid Path
        ** 0 : Success        
        ** Other : result value by FS
        *************************************************/
        int     Seek(s64 offset, SeekPos rel = CUR);
        /*
        ** Return the current position in the file
        *************************************************/
        u64     Tell(void) const;
        /*
        **
        *************************************************/
        void    Rewind(void);

        /**
         * \brief Flushes a file's content
         * \return 0 if success, FS code error otherwise
         */
        int     Flush(void) const;
        /*
        ** Return the current size of the file
        ** return value:
        ** -1 : Error    
        ** Other : file size
        *************************************************/
        u64     GetSize(void) const;
        /*
        ** Dump memory into a file
        ** address to dump from
        ** length = length to dump
        ** return value:
        ** -1 : Invalid address
        ** 0 : Success        
        ** Other : result value by FS
        *************************************************/
        int     Dump(u32 address, u32 length);
        /*
        ** Inject a file into memory
        ** address to inject the file to
        ** length = length to inject
        ** return value:
        ** -1 : An error occured
        ** 0 : Success        
        ** Other : result value by FS
        *************************************************/
        int     Inject(u32 address, u32 length);
        
        File(void);

        /*
        ** Return if the File is open
        *************************************************/
        bool    IsOpen(void) const;

    private:
        std::string     _path;
        std::string     _name;
        Handle          _handle;
        u64             _offset;
        int             _mode;
        bool            _isOpen;
    };
}

#endif