#include "window.h"
#include "audio.h"

#include <iostream>
#include <fstream>

//43,2ko

void event(SDL_Event e){
    
}

int main(int argc, char** argv){
    Window::initWindow(800,600,"Test");
    Audio::initOpenAL();
    while(!Window::closeRequested){//main loop

        Window::pollEvent(&event);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glLoadIdentity();
        glBegin(GL_POINTS);
        glVertex2f(-1,-1);
        glVertex2f(-1,1);
        glVertex2f(1,-1);
        glVertex2f(1,-1);
        glEnd();

        Window::displayUpdate();
        
    }
    Audio::destroyOpenAL();
    Window::destroyWindow();
    return 0;
}
