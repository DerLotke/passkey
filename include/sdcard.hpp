#pragma once

#include <Arduino.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <memory>

struct SdCardData;

class SDCard
{
    public:
        enum class OpenMode{
            FILE_READONLY,
            FILE_READWRITE
        };
        
        typedef std::shared_ptr<FILE> SdCardFile;
        typedef std::shared_ptr<DIR> SdCardDirectory;

        SDCard();
        ~SDCard();

        bool sdCardLoaded() const { return sdcardOk_; }

        SdCardFile open(const String &filename, OpenMode const mode);
        SdCardDirectory openDir(const String &pathName);

    private:
        SdCardData *card_;
        bool sdcardOk_;
};
