#ifndef CTRPLUGINFRAMEWORK_DIRECTORY_HPP
#define CTRPLUGINFRAMEWORK_DIRECTORY_HPP

#include "types.h"
#include <string>
#include <vector>

#include "ctrulib/services/fs.h"
#include "CTRPluginFramework/System/File.hpp"

namespace CTRPluginFramework
{
    class File;
    class Directory
    {
    public:

        /*
        ** Change the working directory
        ** path = the path to set as working directory
        ** return value:
        ** -1 : Invalid Path
        ** Other : result value by FS
        ** 0 : Success
        *************************************************/
        static  int     ChangeWorkingDirectory(std::string path);
        
        /*
        ** Create a folder
        ** path = the path and name of the folder to create
        ** return value:
        ** -1 : Invalid path
        ** 0 : Success
        ** 1 : Already exists
        ** Other: Result value by FS
        *************************************************/
        static  int     Create(std::string path);
        /*
        ** Remove a directory
        ** path = path of the folder to remove
        ** return value:
        ** -1 : Invalid path
        ** 0 : Success
        ** Other: Result value by FS
        ************************************************/
        static  int     Remove(std::string path);
        /*
        ** Rename a folder
        ** path = path of the folder to remove
        ** return value:
        ** -1 : Invalid path
        ** 0 : Sucess
        ** Other : Result value by FS
        ***********************************************/
        static  int     Rename(std::string oldPath, std::string newPath);
        /*
        ** Check if a folder exists
        ** path = path of the folder to check
        ** return value:
        ** -1 : Invalid Path
        ** 0 : Doesn't Exist
        ** 1 : Exist
        ***********************************************/
        static  int     IsExists(std::string path);

        /*
        ** Open a folder
        ** &output = refernce to output the Folder object
        ** path = path of the folder to open
        ** create = if the folder must be created
        ** return value:
        ** -1 : Invalid Path
        ** 0 : Success
        ** Other : Result value by FS
        **********************************************/
        static int     Open(Directory &output, std::string path, bool create = false);
        Directory() : _path(""), _handle(0), _isListed(false), _isInit(false){}
        ~Directory() { Close(); }

        int     Close(void);

        /*
        ** Open a file in the current directory
        **  &output = reference to output the File object
        ** path = path of the file to open (from the current folder)
        ** Return value:
        ** -1 : Invalid Path
        ** 0 : Success
        ** Other Result value by FS
        *********************************************/
        int     OpenFile(File &output, std::string path, bool create = true);

        /*
        ** List the files in the current directory
        ** &files = reference to a std::vector to output the filenames
        ** pattern = if specified, the function will only return the files 
        ** which contain the pattern in their name (extension included)
        ** Return value:
        ** -1: the current Directory isn't properly opened
        ** >=0 : the total of files found (that matched the pattern if specified)
        *********************************************/
        int     ListFiles(std::vector<std::string> &files, std::string pattern = "");

        /*
        ** List the folders in the current directory
        ** &folders = reference to a std::vector to output the foldernames
        ** pattern = if specified, the function will only return the folders
        ** which contain the pattern in their name
        ** Return value:
        ** -1: the current Directory isn't properly opened
        ** >=0 : the total of folders found (that matched the pattern if specified)
        *********************************************/
        int     ListFolders(std::vector<std::string> &folders, std::string pattern = "");

        std::string &GetPath(void);
    private:

        friend class File;
        static  std::string     _workingDirectory;
        static  int             _SdmcFixPath(std::string &path);
        static  FS_Path         _SdmcUtf16Path(std::string path);
        int                     _List(void);

        Directory  (std::string &path, Handle &handle);

        std::string     _path;
        Handle          _handle;
        std::vector<FS_DirectoryEntry>    _list;
        bool                              _isListed;
        bool                              _isInit;
    };
}

#endif