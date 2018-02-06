#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

#include <GL/glew.h>
#ifdef _WIN32
    
#elif __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_OS_MAC
        #include <OpenGL/gl.h>
        #include <OpenGL/glu.h>
    #endif
#elif __linux__
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <chrono>

#define NTIME currentNanoTime()
#define UTIME currentMillisTime()

extern unsigned long deltaTime;
extern unsigned long updateTime;

unsigned long currentMillisTime();
unsigned long currentNanoTime();

class Window{

    public:
    static void initWindow(int,int,std::string);
    static void destroyWindow();
    static void pollEvent(void(*f)(SDL_Event));
    static void displayUpdate();
    static void setTitleSuffixe(const char*);

    static std::string title;
    static SDL_Window* pWindow;
    static SDL_Event event;
    static bool closeRequested;
    static SDL_GLContext context;

};

#endif