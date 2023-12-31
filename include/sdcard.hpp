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

        ~SDCard();

        bool sdCardLoaded() const { return sdcardOk_; }

        SdCardFile open(const String &filename, OpenMode const mode) const;
        SdCardDirectory openDir(const String &pathName);

	static SDCard& load();
	static void unload();

    private:
        SDCard();

        SdCardData *card_;
        bool sdcardOk_;
};
