#pragma once

#include "sdcard.hpp"

class KeyStrokeFile
{
    public:
    
    /** This is the available command types that can be withn a KeyStrokeData structure */
    enum class CommandTypes {
        KeyPress, /*< This denotes a Key press command */
        KeyRelease, /*< This denotes a Key releas command */
        TypeDelay, /*< This is a delay in ms, that can be used between keystrokes */
        EndOfFile /*< This denotes the end of the keystroke file */
    };
    
    /** This is the key stroke data structure returned by the read function */
    struct KeyStrokeData
    {
        CommandTypes type;
        unsigned parameter;
    };
    
    KeyStrokeFile(SDCard::SdCardFile file);
    ~KeyStrokeFile();

    /**
     * This function reads the next KeyStroke Command from the given file
     * If no more keystrokes can be read or an error while reading occures
     * it will return the EndOfFile Type.
     * 
     * @return KeyStrokeData is returned
    */
    KeyStrokeData getNextCommand();

    private:
    SDCard::SdCardFile keyStrokeFile_;
};
