#ifndef AUDIO_H
#define AUDIO_H

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sndfile.h>
#include <vector>

class Audio{

    public:
    static void initOpenAL();
    static void destroyOpenAL();
    static ALuint loadSound(const std::string);
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