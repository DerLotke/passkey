#pragma once

#include <Arduino.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <memory>

struct SdCardData;

class SDCard
{
    enum class OpenMode{
        FILE_READONLY,
        FILE_READWRITE
    };
    
    public:
        SDCard();
        ~SDCard();

        bool sdCardLoaded() const { return sdcardOk_; }

        std::shared_ptr<FILE> open(const String &filename, OpenMode const mode);
        std::shared_ptr<DIR> openDir(const String &pathName);

    private:
        SdCardData *card_;
        bool sdcardOk_;
};
