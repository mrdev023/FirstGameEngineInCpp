#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdio.h>
#include <stdlib.h>
#include <string>

class Window{

    public:
    static void initWindow(int,int,std::string);
    static void destroyWindow();
    static void pollEvent(void(*f)(SDL_Event));
    static void displayUpdate();

    static SDL_Window* pWindow;
    static SDL_Event event;
    static bool closeRequested;
    static SDL_GLContext context;

};

#endif