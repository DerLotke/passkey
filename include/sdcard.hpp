#pragma once

#include <Arduino.h>
#include <stdio.h>
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

    private:
        SdCardData *card_;
        bool sdcardOk_;
};
