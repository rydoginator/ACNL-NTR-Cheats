#include "CTRPluginFramework.hpp"
#include "plgldr.h"
#include <algorithm>
#include <inttypes.h>
#include "cheats.hpp"
#include "3ds.h"

#define PLG_URL "https://raw.githubusercontent.com/Slattz/ACNL-Multi-Cheat/master/ACNL-Multi-Cheat.3gx"
#define PLG_VER_URL "https://raw.githubusercontent.com/Slattz/ACNL-Multi-Cheat/master/latest.txt"

namespace CTRPluginFramework
{
    static char *newVerString = nullptr;
    static const char *newChangelog = "Changelog:\nThe changelog cannot be viewed from the plugin.\nVisit < https://bit.ly/ACNL_3GX >\nto see the changelog on Github.";

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
        MessageBox(Utils::Format("Major: %d, Result: %d", major, major >= MAJOR_VERSION))();
        #endif

        if (next && *next == '.') //If minor version
            next++;
        else
            return major > MAJOR_VERSION;

        minor = strtol(next, &next, 10); //Get minor version
        #if DEBUG
        MessageBox(Utils::Format("Minor: %d, Result %d", minor, minor >= MINOR_VERSION))();
        #endif

        if (next && *next == '.') //If revision version
            next++;

        else if (next && *next == 'B') //If there's no revision ver but it's beta
        {
            next++;
            beta_ver = strtol(next, NULL, 10); //Get beta version
            #if DEBUG
            MessageBox(Utils::Format("Beta 1: %d, Result %d", beta_ver, beta_ver >= BETA_VERSION))();
            #endif
            return major >= MAJOR_VERSION && minor >= MINOR_VERSION && beta_ver > BETA_VERSION;
        }

        else //If there's no revision ver & beta ver
            return major >= MAJOR_VERSION && minor > MINOR_VERSION;

        revision = strtol(next,  &next, 10); //Get revision version
        #if DEBUG
        MessageBox(Utils::Format("Revision: %d, Result %d", revision, revision >= REVISION_VERSION))();
        #endif
        if (next && *next == 'B') //If there's a beta ver after revision ver
            next++;

        else
            return major >= MAJOR_VERSION && minor >= MINOR_VERSION && revision > REVISION_VERSION;

        beta_ver = strtol(next, NULL, 10); //Get beta version
        #if DEBUG
        MessageBox(Utils::Format("Beta 2: %d, Result %d", beta_ver, beta_ver >= BETA_VERSION))();
        #endif
        return major >= MAJOR_VERSION && minor >= MINOR_VERSION
                && revision >= REVISION_VERSION && beta_ver > BETA_VERSION;
    }

    bool http_download(const char *src, u8 **output, u32 *outSize)
    {
        Result res = 0;
        httpcContext context;
        u32 responseCode = 0;
        u32 downloadSize = 0;
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
                        MessageBox(Utils::Format("URL returned status: %" PRId32 " ", responseCode))();
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

        if (R_SUCCEEDED(res = httpcGetDownloadSizeState(&context, NULL, &downloadSize)))
        {
            bool fallback = false;
            
            buffer = static_cast<u8*>(calloc(1, downloadSize));
            if (buffer == NULL || output == NULL || outSize == NULL)
            {
                if (buffer!=NULL) free(buffer);

                buffer = static_cast<u8*>(calloc(1, 0x10000)); //fallback
                if (buffer == NULL)
                    return false;

                fallback = true;
            }

            File   tempfile;
            if (fallback)
            {
                File::Open(tempfile, "TempFile.bin", File::RWC|File::TRUNCATE);
                if (!tempfile.IsOpen())
                {
                    #if DEBUG
                        MessageBox("Temp File not open!")();
                    #endif
                    return false;
                }
            }

            u32 left = downloadSize;
            while (left > 0)
            {
                bytesRead = 0;
                if (fallback)
                    res = httpcDownloadData(&context, (u8 *)buffer, 0x10000, &bytesRead);
                else
                    res = httpcDownloadData(&context, (u8 *)buffer, downloadSize, &bytesRead);

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
                        *outSize = downloadSize;
                    }
                    ret = true;
                }

                else
                {
                    #if DEBUG
                        MessageBox(Utils::Format("Download Failed!\nLeft to download: %d", left))();
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

        if (http_download(PLG_VER_URL, (u8 **)&latest, &size))
        {
            Sstrncpy(newVerString, latest, size);
            if (CheckVersion(newVerString))
                return true; //if update

            else return false; //if no update
        }

        return false;
    }

    bool installUpdate(void)
    {
        //Having NULL for output and outSize args makes function fallback to creating TempFile.bin
        if (http_download(PLG_URL, NULL, NULL))
        {
            #if DEBUG
                MessageBox("Update Downloaded!")();
            #endif

            if (!File::Exists("TempFile.bin")) //has to have been made as fallback method used
            {
                #if DEBUG
                MessageBox("The downloaded update does not exist on file!")();
                #endif
                return false;
            }

            char path[255] = {0};
            if (R_FAILED(PLGLDR__GetPluginPath(path)))
                return false;

            File::Remove(path);
            File::Rename("TempFile.bin", path);

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
        newVerString = new char[50];
        static const std::string ProceedUpdate = "Would you like to proceed with installing the update?";

        if (checkUpdate())
        {
            #if DEBUG
                MessageBox("Check Update: True!")();
            #endif

            MessageBox(Utils::Format("New Version: %s", newVerString), newChangelog).SetClear(ClearScreen::Both)();

            if (MessageBox(ProceedUpdate, DialogType::DialogYesNo).SetClear(ClearScreen::Both)())
                ret = installUpdate();
        }

        #if DEBUG
        else MessageBox("Check Update: False!")();
        #endif

        delete[] newVerString;
        #if DEBUG
            MessageBox(Utils::Format("launchUpdater Ret: %d", ret))();
        #endif
        return ret;
    }

}