#include "CTRPluginFramework.hpp"
#include <algorithm>
#include "Helpers/jsmn.h"
#include "cheats.hpp"
#include "3ds.h"

namespace CTRPluginFramework
{
    static char     *newVerString = nullptr;
    static char     *newChangelog = nullptr;
    static char     *urlDownload = nullptr;
    static int      urlDownloadSize;

    static int jsoneq(const char *json, jsmntok_t *tok, const char *s)
    {
        if (tok->type == JSMN_STRING && (int) strlen(s) == tok->end - tok->start &&
                strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
            return 0;
        }
        return -1;
    }

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
            return major >= MAJOR_VERSION && minor >= MINOR_VERSION;
    
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
    
    void    DeleteString(std::string &str, const std::string &pattern)
    {
        size_t pos = 0;
        while ((pos = str.find(pattern, pos)) != std::string::npos)
            str.erase(pos, pattern.length());
    }

    void ReplaceString(std::string &str, const std::string &pattern, const std::string &replace)
    {
        size_t pos = 0;
        while ((pos = str.find(pattern, pos)) != std::string::npos)
        {
            str.replace(pos, pattern.length(), replace);
            pos += replace.length();
        }
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
                    resolved = true;

                    if (responseCode != 200)
                    {
                    #if DEBUG
                        MessageBox(Format("URL returned status: %ld", responseCode))();
                    #endif
                        httpcCloseContext(&context);
                        return false;       
                    }
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
        }

        return ret;
    }

    bool checkUpdate(void)
    {
        char            *json = NULL;
        u32             size = 0;
        Result          res;
        bool            ret = false;
        jsmn_parser     jParser;
        jsmntok_t       tokens[500];
        jsmntok_t       obj_key;
        jsmntok_t       obj_val;
        jsmntok_t       assetName;
        jsmntok_t       assetUrl;
        bool            updateavailable = false;
        int             value_length;
        int             i; //Loop
        int             j; //Loop 2
        int             tok = 0;
        int             tokoffset = 0;
        int             objnum = 0;
        int             objoffset = 0;
        int             assetNameLoopVal = -1;
        int             assetUrlLoopVal = -2; //Start value different to assetNameLoopVal

        if (http_download("https://api.github.com/repos/RyDog199/ACNL-NTR-Cheats/releases/latest", (u8 **)&json, &size)) //BootNTR Test
        {
            jsmn_init(&jParser);
            res = jsmn_parse(&jParser, json, size, tokens, sizeof(tokens)/sizeof(tokens[0]));

            /* Check if the parse was a success */
            if (res < 0) 
            {
                #if DEBUG
                MessageBox(Format("Failed to parse JSON: %ld", res))();
                #endif

                return 0;
            }

            /* Assume the top-level element is an object */
            if (res < 1 || tokens[0].type != JSMN_OBJECT)
            {
                #if DEBUG
                MessageBox("Object expected")();
                #endif

                return 0;
            }

            /* Loop over all keys of the root object */
            for (i = 1; i < res; i++)
            {
                jsmntok_t json_key = tokens[i];
                jsmntok_t json_value = tokens[i+1];
                value_length = json_value.end - json_value.start;

                if (jsoneq(json, &json_key, "tag_name") == 0 && json_value.type == JSMN_STRING)
                {
                    Sstrncpy(newVerString, json + json_value.start, value_length);
                    if (CheckVersion(newVerString))
                        updateavailable = true;

                    else return 0; //if no update
                }

                else if (jsoneq(json, &json_key, "assets") == 0 && updateavailable && json_value.type == JSMN_ARRAY)
                {
                    u32 tempsize = json_value.size; //store size of assets so it can be added to i later
                    for (j = 0; j < json_value.size; j++) //Loop for amount of assets found
                    {
                    /*
                    i = position in orig loop
                    2 = to bring to start of first object of array
                    j = which array
                    tokoffset = calculated to get to start of next array
                    */
                        tok = i+2+j+tokoffset;
                        jsmntok_t val = tokens[tok]; //Use tok to determine the token in the json
                        if (val.type == JSMN_OBJECT) //If an object is found
                        {
                            /* Increment tokoffset by how big the obj is * 2 to include keys & values */
                            tokoffset += val.size*2;
                            for (int k = 1; k < (val.size*2)+1; k++) //start at 1 to skip original object
                            {
                                objnum = tok+k+objoffset;
                                obj_key = tokens[objnum]; //object keys
                                obj_val = tokens[objnum+1]; //object values

                                /* skip uploader object */
                                if (jsoneq(json, &obj_key, "uploader") == 0 && obj_val.type == JSMN_OBJECT)
                                {
                                    objoffset += 1+(obj_val.size*2); //+1 to get to proper end of object
                                    tokoffset += (obj_val.size*2);
                                }

                                if (jsoneq(json, &obj_key, "name") == 0 && obj_val.type == JSMN_STRING)
                                {
                                    assetName = obj_val;
                                    assetNameLoopVal = j; //Ensure name is from same asset as url
                                }

                                else if (jsoneq(json, &obj_key, "browser_download_url") == 0 && obj_val.type == JSMN_STRING)
                                {
                                    assetUrl = obj_val;
                                    assetUrlLoopVal = j; //Ensure url is from same asset as name
                                }

                                if (jsoneq(json, &assetName, "ACNL-NTR-Cheats.plg") == 0
                                    && assetUrl.type == JSMN_STRING
                                    && assetNameLoopVal == assetUrlLoopVal)
                                {
                                    urlDownloadSize = assetUrl.end - assetUrl.start;
                                    Sstrncpy(urlDownload, json + assetUrl.start, urlDownloadSize);
                                    ret = true;
                                }
                            }
                            objoffset = 0; //Reset objoffset for the next object
                        }
                    }
                    i += tempsize; //Add size of assets array to loop to skip it
                }

                else if (jsoneq(json, &json_key, "body") == 0 && updateavailable && json_value.type == JSMN_STRING)
                {
                    /* For use when MessageBoxes have scrolling support
                    Sstrncpy(newChangelog, json + json_value.start, value_length);
                    std::string temp(newChangelog);
                    DeleteString(temp, "\\r");
                    ReplaceString(temp, "\\n", "\n");
                    strcpy(newChangelog, temp.c_str());*/
                    char Nochange[200];
                    snprintf(Nochange, sizeof(Nochange), "Displaying the changelog is currently\nnot supported.\nVisit < http://bit.ly/ACPLG-Change >\nto see the changelog on Github.");
                    Sstrncpy(newChangelog, Nochange, 200);
                }
            }
        }
        return ret;
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
                MessageBox("The downloaded update does not exist!")();
                return false;
            }

            File::Remove("ACNL-NTR-Cheats.plg");
            File::Rename("TempFile.bin", "ACNL-NTR-Cheats.plg");
            return true;
        }
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