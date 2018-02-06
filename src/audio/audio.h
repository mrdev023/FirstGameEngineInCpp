#ifndef AUDIO_H
#define AUDIO_H

#ifdef _WIN32
    
#elif __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_OS_MAC
        #include <OpenAL/al.h>
        #include <OpenAL/alc.h>
    #endif
#elif __linux__
    #include <AL/al.h>
    #include <AL/alc.h>
#endif

#include <AL/alut.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sndfile.h>
#include <vector>

/*
Class created by MrDev023
*/
class Audio{

    public:
    /*
        Initialise le Device pour lire des pistes audio
    */
    static void initOpenAL();

    /*
        Permet de detruire le device
    */
    static void destroyOpenAL();

    /*
        Fonction permettant de lire un son puis de retourner l identifiant de la source
    */
    static ALuint loadSound(std::string);
    static ALuint createSource(ALuint*);
    static ALuint createSource(const std::string);
    static void destroySound(ALuint*);
    static void destroySource(ALuint*);
    static void playSource(ALuint*);
    static ALuint getSourceState(ALuint*);
    static ALfloat getSourceSecOffSet(ALuint*);
    static bool isSourcePlaying(ALuint*);
    static void setListenerPosition(float,float,float);
    static void setListenerVelocity(float,float,float);
    static void setListenerRotation(float,float,float,float,float,float);
    static void set3DSource(ALuint*,bool);
    static void setSourcePosition(ALuint*,float,float,float);
    static void setSourceVelocity(ALuint*,float,float,float);
    static void setSourceLooping(ALuint*,bool);
    static void setSourceGain(ALuint*,float);
    
    static ALCdevice* device;
    static ALCcontext* context;

};

#endif