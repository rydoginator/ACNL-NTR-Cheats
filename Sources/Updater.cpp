#include "CTRPluginFramework.hpp"
#include <algorithm>
#include <inttypes.h>
#include "cheats.hpp"
#include "3ds.h"

//#define DEBUG 1

namespace CTRPluginFramework
{
    static char     *newVerString = nullptr;
    static char     *newChangelog = nullptr;
    static char     *urlDownload = nullptr;

    bool    CheckVersion(const char *releaseName)
    {
        int     major = 0;
        int     minor = 0;
        int     revision = 0;
        int     beta_ver = 0;
        char    *next = NULL;
        
        if (releaseName && *releaseName == 'v')
            releaseName++;
    
        major = strtol(releaseName, &next, 10); //Get major version
        #if DEBUG
        MessageBox(Format("Major: %d, Result: %d", major, major >= MAJOR_VERSION))();
        #endif

        if (next && *next == '.') //If minor version
            next++;
        else
            return major > MAJOR_VERSION;
    
        minor = strtol(next, &next, 10); //Get minor version
        #if DEBUG
        MessageBox(Format("Minor: %d, Result %d", minor, minor >= MINOR_VERSION))();
        #endif

        if (next && *next == '.') //If revision version
            next++;

        else if (next && *next == 'B') //If there's no revision ver but it's beta
        {
            next++;
            beta_ver = strtol(next, NULL, 10); //Get beta version
            #if DEBUG
            MessageBox(Format("Beta 1: %d, Result %d", beta_ver, beta_ver >= BETA_VERSION))();
            #endif
            return major >= MAJOR_VERSION && minor >= MINOR_VERSION && beta_ver > BETA_VERSION;
        }
            
        else //If there's no revision ver & beta ver
            return major >= MAJOR_VERSION && minor > MINOR_VERSION;
    
        revision = strtol(next,  &next, 10); //Get revision version
        #if DEBUG
        MessageBox(Format("Revision: %d, Result %d", revision, revision >= REVISION_VERSION))();
        #endif
        if (next && *next == 'B') //If there's a beta ver after revision ver
            next++;

        else
            return major >= MAJOR_VERSION && minor >= MINOR_VERSION && revision > REVISION_VERSION;
        
        beta_ver = strtol(next, NULL, 10); //Get beta version
        #if DEBUG
        MessageBox(Format("Beta 2: %d, Result %d", beta_ver, beta_ver >= BETA_VERSION))();
        #endif
        return major >= MAJOR_VERSION && minor >= MINOR_VERSION 
                && revision >= REVISION_VERSION && beta_ver > BETA_VERSION;
    }

    bool http_download(const char *src, u8 **output, u32 *outSize)
    {
        Result res = 0;
        bool fallback = false;
        httpcContext context;
        u32 responseCode = 0;
        u32 size=0;
        u32 bytesRead;
        u8 *buffer;
        char url[1024] = {0};
        bool resolved = false;
        bool ret = false;

        strncpy(url, src, 1023);
        while(R_SUCCEEDED(res) && !resolved)
        {
            if (R_SUCCEEDED(res = httpcOpenContext(&context, HTTPC_METHOD_GET, url, 1)))
            {
                httpcSetSSLOpt(&context, SSLCOPT_DisableVerify);
                httpcAddRequestHeaderField(&context, "User-Agent", "Mozilla/5.0 (Nintendo 3DS; Mobile; rv:10.0)");
                httpcAddRequestHeaderField(&context, "Connection", "Keep-Alive");
                httpcBeginRequest(&context);
                res = httpcGetResponseStatusCode(&context, &responseCode);

                if (responseCode >= 301 && responseCode <= 303)
                {
                    #if DEBUG
                        MessageBox("redirecting URL")();
                    #endif
                    memset(url, '\0', strlen(url));
                    if (R_SUCCEEDED(res = httpcGetResponseHeader(&context, "Location", url, 1024)))
                        httpcCloseContext(&context);
                }

                else
                {
                    if (responseCode != 200)
                    {
                    #if DEBUG
                        MessageBox(Format("URL returned status: %" PRId32 " ", responseCode))();
                    #endif
                        httpcCloseContext(&context);
                        return false;       
                    }

                    resolved = true;
                }
            }
            #if DEBUG
            else MessageBox("Could not open HTTP context!")();
            #endif
        }

        if (R_SUCCEEDED(res = httpcGetDownloadSizeState(&context, NULL, &size)))
        {
            buffer = static_cast<u8*>(calloc(1, size));
            if (buffer == NULL || output == NULL || outSize == NULL)
            {
                if (buffer!=NULL) free(buffer);

                buffer = static_cast<u8*>(calloc(1, 0x1000)); //fallback
                if (buffer == NULL)
                    return false;

                fallback = true;
            }

            File   tempfile;
            if (fallback)
            {
                File::Open(tempfile, "TempFile.bin", File::RWC);
                if (!tempfile.IsOpen())
                {
                    #if DEBUG
                        MessageBox("Temp File not open!")();
                    #endif
                    return false;
                }
            }
    
            u32 left = size;
            while (left > 0)
            {
                bytesRead = 0;
                if (fallback)
                    res = httpcDownloadData(&context, (u8 *)buffer, 0x1000, &bytesRead);
                else
                    res = httpcDownloadData(&context, (u8 *)buffer, size, &bytesRead);

                if (res == (s32)HTTPC_RESULTCODE_DOWNLOADPENDING || res == 0)
                {
                    left -= bytesRead;

                    if (fallback)
                    {
                        tempfile.Write(buffer, bytesRead);
                        tempfile.Flush();
                        if (left == 0)
                            tempfile.Close();
                    }

                    else if (left == 0 && !fallback)
                    {
                        *output = buffer;
                        *outSize = size;
                    }

                    ret = true;
                }
    
                else
                {
                    #if DEBUG
                        MessageBox(Format("Download Failed!\nLeft to download: %d", left))();
                    #endif
    
                    ret = false;
                    break;
                }
            }
            httpcCloseContext(&context);
        }

        #if DEBUG
        else MessageBox("Failed to get download size!")();
        #endif

        return ret;
    }

    bool checkUpdate(void)
    {
        char            *latest = NULL;
        u32             size = 0;
        Result          res;
        bool            updateavailable = false;


        if (http_download("https://raw.githubusercontent.com/rydoginator/ACNL-NTR-Cheats/master/latest.txt", (u8 **)&latest, &size)) //BootNTR Test
        {
                Sstrncpy(newVerString, latest, size);
                if (CheckVersion(newVerString))
                    updateavailable = true;

                else return false; //if no update


                Sstrncpy(urlDownload, "https://raw.githubusercontent.com/rydoginator/ACNL-NTR-Cheats/master/ACNL-NTR-Cheats.plg", 200);
                Sstrncpy(newChangelog, "The changelog cannot be viewed from the plugin.\nVisit < http://bit.ly/ACPLG-Change >\nto see the changelog on Github.", 200);

                return updateavailable;
        }

        return updateavailable;
    }

    bool installUpdate(void)
    {
        File   file;

        if (http_download(urlDownload, NULL, NULL))
        {
            #if DEBUG
                MessageBox("Update Downloaded!")();
            #endif

            if (!File::Exists("TempFile.bin"))
            {
                #if DEBUG
                MessageBox("The downloaded update does not exist on file!")();
                #endif
                return false;
            }

            if (System::IsLoaderNTR()) {
                File::Remove("ACNL-NTR-Cheats.plg");
                File::Rename("TempFile.bin", "ACNL-NTR-Cheats.plg");
            }

            else {
                File::Remove("plugin.plg");
                File::Rename("TempFile.bin", "plugin.plg");
            }

            return true;
        }

        #if DEBUG
        else MessageBox("Couldn't download the update!")();
        #endif

        return false;
    }

    bool launchUpdater(void)
    {
        bool ret = false;
        urlDownload = new char[1024];
        newChangelog = new char[2048];
        newVerString = new char[50];
        static const std::string ProceedUpdate = "Would you like to proceed with installing the update?";

        if (checkUpdate())
        {
            #if DEBUG
                MessageBox("Check Update: True!")();
            #endif

            MessageBox(Format("New Version: %s", newVerString), Format("Changelog:\n%s", newChangelog))();

            if (MessageBox(ProceedUpdate, DialogType::DialogYesNo)())
                ret = installUpdate();
        }

        else
        {
            #if DEBUG
                MessageBox("Check Update: False!")();
            #endif
        }

        delete[] urlDownload;
        delete[] newChangelog;
        delete[] newVerString;
        #if DEBUG
            MessageBox(Format("launchUpdater Ret: %d", ret))();
        #endif
        return ret;
    }

}