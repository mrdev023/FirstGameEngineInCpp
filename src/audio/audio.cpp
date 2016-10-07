#include "audio.h"

ALCdevice* Audio::device;
ALCcontext* Audio::context;

ALuint Audio::loadSound(std::string Filename){
    // Ouverture du fichier audio avec libsndfile
    std::string* path = new std::string("res/sounds/");
    Filename = *path + Filename;
    delete path;
    SF_INFO FileInfos;
    SNDFILE* File = sf_open(Filename.c_str(), SFM_READ, &FileInfos);
    if (File == NULL){
        printf("%s\n",sf_strerror(File));
        return 0;
    }

    // Lecture du nombre d'échantillons et du taux d'échantillonnage (nombre d'échantillons à lire par seconde)
    ALsizei NbSamples  = static_cast<ALsizei>(FileInfos.channels * FileInfos.frames);
    ALsizei SampleRate = static_cast<ALsizei>(FileInfos.samplerate);

    // Lecture des échantillons audio au format entier 16 bits signé (le plus commun)
    std::vector<ALshort> Samples(NbSamples);
    if (sf_read_short(File, &Samples[0], NbSamples) < NbSamples){
        printf("Error during load file data !\n");
        return 0;
    }

    // Fermeture du fichier
    sf_close(File);


    // Détermination du format en fonction du nombre de canaux
    ALenum Format;
    switch (FileInfos.channels)
    {
        case 1 :  Format = AL_FORMAT_MONO16;   break;
        case 2 :  Format = AL_FORMAT_STEREO16; break;
        case 4 : Format = alGetEnumValue("AL_FORMAT_QUAD16");  break;
        case 6 : Format = alGetEnumValue("AL_FORMAT_51CHN16"); break;
        case 7 : Format = alGetEnumValue("AL_FORMAT_61CHN16"); break;
        case 8 : Format = alGetEnumValue("AL_FORMAT_71CHN16"); break;
        default : return 0;
    }

    // Création du tampon OpenAL
    ALuint Buffer;
    alGenBuffers(1, &Buffer);
    int sec = NbSamples/FileInfos.channels/SampleRate;
    int min = sec/60;
    sec -= min * 60;

    // Remplissage avec les échantillons lus
    alBufferData(Buffer, Format, &Samples[0], NbSamples * sizeof(ALushort), SampleRate);
 
    // Vérification des erreurs
    if (alGetError() != AL_NO_ERROR){
        printf("OPENAL ERROR DURING LOAD FILE !\n");
        return 0;
    }

    printf("Audio ressource %s loaded ! (channels: %d,SampleRate: %d,Time: %d:%d)\n",Filename.c_str(),FileInfos.channels,SampleRate,min,sec);
    return Buffer;
}

ALuint Audio::createSource(ALuint* Buffer){
    // Création d'une source
    ALuint Source;
    alGenSources(1, &Source);

    // On attache le tampon contenant les échantillons audio à la source
    alSourcei(Source, AL_BUFFER, *Buffer);

    alSourcef(Source, AL_ROLLOFF_FACTOR, 1);
    alSourcef(Source, AL_REFERENCE_DISTANCE, 5);
    alSourcef(Source, AL_MAX_DISTANCE, 25);

    return Source;
}

ALuint Audio::createSource(const std::string f){
    ALuint Buffer = Audio::loadSound(f);
    ALuint a = Audio::createSource(&Buffer);
    Audio::destroySound(&Buffer);
    return a;
}

void Audio::playSource(ALuint* Source){
    // Lecture du son
    alSourcePlay(*Source);
}

void Audio::destroySound(ALuint* Buffer){
    // Destruction du tampon
    alDeleteBuffers(1, Buffer);
}

void Audio::destroySource(ALuint* Source){
    // Destruction de la source
    alSourcei(*Source, AL_BUFFER, 0);
    alDeleteSources(1, Source);
}

ALuint Audio::getSourceState(ALuint* Source){
    // Récupération de l'état du son
    ALint Status;
    alGetSourcei(*Source, AL_SOURCE_STATE, &Status);
    return Status;
}

ALfloat Audio::getSourceSecOffSet(ALuint* Source){
    // Récupération de l'état du son
    ALfloat s = 0.f;
    alGetSourcef(*Source, AL_SEC_OFFSET, &s);
    return s;
}

void Audio::initOpenAL(){
    if(Audio::device && Audio::context){
        printf("Audio already init");
        return;
    }

    // Ouverture du device
    Audio::device = alcOpenDevice(NULL);
    if(!Audio::device){
        printf("Device not Open");
        exit(-1);
    }

    // Création du contexte
    Audio::context = alcCreateContext(Audio::device,NULL);
    if(!Audio::context){
        printf("Context not created !");
        exit(-1);
    }

    // Activation du contexte
    if(!alcMakeContextCurrent(Audio::context)){
        printf("Context not activated !");
        exit(-1);
    }

    printf("----------------------------------------------------------------\n");
    printf("Audio Successfully Initialized\n");
    printf("OpenAL Info\n");
    printf("    Version: %s\n", alGetString(AL_VERSION));
    printf("     Vendor: %s\n", alGetString(AL_VENDOR));
    printf("   Renderer: %s\n", alGetString(AL_RENDERER));
    printf("OpenAL Extensions:\n");
    std::string s(alGetString(AL_EXTENSIONS));
    std::string delimiter = " ";
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        printf("             %s\n", token.c_str());
        s.erase(0, pos + delimiter.length());
    }
    printf("----------------------------------------------------------------\n");

    alDistanceModel(AL_LINEAR_DISTANCE_CLAMPED);

    // Définition de la position de l'écouteur (ici l'origine)
    alListener3f(AL_POSITION, 0.f, 0.f, 0.f);
    
    // Définition de la vitesse de l'écouteur (ici nulle)
    alListener3f(AL_VELOCITY, 0.f, 0.f, 0.f);
    
    // Définition de l'orientation de l'écouteur (ici il regarde vers l'axe des Z)
    ALfloat Orientation[] = {0.f, 0.f, 1.f, 0.f, 1.f, 0.f};
    alListenerfv(AL_ORIENTATION, Orientation);
}

void Audio::destroyOpenAL(){
    if(!Audio::device && !Audio::context){
        printf("Audio not init");
        return;
    }
    // Désactivation du contexte
    alcMakeContextCurrent(NULL);

    // Destruction du contexte
    alcDestroyContext(Audio::context);

    // Fermeture du device
    alcCloseDevice(Audio::device);
}

bool Audio::isSourcePlaying(ALuint* Source){
    return AL_PLAYING == Audio::getSourceState(Source);
}

void Audio::setListenerPosition(float x,float y,float z){
    // Définition de la position de l'écouteur (ici l'origine)
    alListener3f(AL_POSITION, x, y, z);
}

void Audio::setListenerVelocity(float x,float y,float z){
    // Définition de la vitesse de l'écouteur (ici nulle)
    alListener3f(AL_VELOCITY, x, y, z);
}

void Audio::setListenerRotation(float forwardx,float forwardy,float forwardz,float upx,float upy,float upz){
    // Définition de l'orientation de l'écouteur
    float a[6];
    a[0] = forwardx;
    a[1] = forwardy;
    a[2] = forwardz;
    a[3] = upx;
    a[4] = upy;
    a[5] = upz;
    alListenerfv(AL_ORIENTATION, a);
}

void Audio::set3DSource(ALuint* Source,bool sur){
    if(sur){
        alSourcei(*Source, AL_SOURCE_RELATIVE, AL_FALSE);
    }else{
        alSourcei(*Source, AL_SOURCE_RELATIVE, AL_TRUE);
    }
}

void Audio::setSourcePosition(ALuint* Source,float x,float y,float z){
    alSource3f(*Source, AL_POSITION, x, y, z);
}

void Audio::setSourceVelocity(ALuint* Source,float x,float y,float z){
    alSource3f(*Source, AL_VELOCITY, x, y, z);
}


void Audio::setSourceLooping(ALuint* Source,bool loop){
    alSourcei(*Source, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
}

void Audio::setSourceGain(ALuint* Source,float gain){
    alSourcef(*Source, AL_GAIN, gain);
}