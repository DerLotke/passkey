#pragma once

#include <Arduino.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <memory>
#include <utility>
#include <mutex>
#include <functional>

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

	/**
	 * @brief Open a filestream and perform an operation with it
	 *
	 * The filestream is valid only during the duration of the call of op.
	 * If the file does not exist the stream will be empty.
	 *
	 * @tparam FileStreamType Type of stream to open (either std::istream or std::iostream)
	 * @param filename File to open
	 * @param op Functionial containing operation that shall be performed using the filestream
	 */
	template<class FileStreamType>
	void openFileStream(String const& filename, std::function<void(FileStreamType&)> op);

	static std::shared_ptr<SDCard> load();
	static void unload();

    private:
        SDCard();

        SdCardData *card_;
        bool sdcardOk_;
	static std::mutex mutex_;
};
