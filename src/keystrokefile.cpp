#include "keystrokefile.hpp"

KeyStrokeFile::KeyStrokeFile(SDCard::SdCardFile file):
    keyStrokeFile_(file)
{

}

KeyStrokeFile::~KeyStrokeFile()
{

}

KeyStrokeFile::KeyStrokeData KeyStrokeFile::getNextCommand()
{
    /* Setup the default return value */
    KeyStrokeData result = {.type = KeyStrokeFile::CommandTypes::EndOfFile, .parameter = 0};

    /*Check for valid file*/
    if(keyStrokeFile_ && !feof(keyStrokeFile_.get()))
    {
        uint8_t data[2];
        /* Check if we were able to read the actual data*/
        if(fread(data, sizeof(data[0]), 2, keyStrokeFile_.get()) == sizeof(data[0]) * 2)
        {
            result.parameter = data[1];

            /*Convert the saved values into the enum we use in the rest of the program*/
            switch (data[0])
            {
            case 0x80: result.type = CommandTypes::KeyPress; break;
            case 0x40: result.type = CommandTypes::TypeDelay; break;
            case 0x0: /*fall through*/
            default:
                result.type = CommandTypes::KeyRelease; break;
            }
        }
    }

    return result;
}
