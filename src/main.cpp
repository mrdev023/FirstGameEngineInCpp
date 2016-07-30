#include "window.h"
#include "audio.h"

#include <iostream>
#include <fstream>

void event(SDL_Event e){
    
}

int main(int argc, char** argv){
    Window::initWindow(800,600,"Test");
    Audio::initOpenAL();
    float i = 0;
    ALuint s = Audio::createSource("a.wav");
    Audio::set3DSource(&s,true);
    Audio::playSource(&s);
    float x,y,dis = 10.0f;
    while(!Window::closeRequested){//main loop
        x = cosf(i) * dis;
        y = sinf(i) * dis;

        Window::pollEvent(&event);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glLoadIdentity();
        glPointSize(12);
        glBegin(GL_POINTS);
        glColor3f(1,0,0);
        glVertex2f(x/dis,y/dis);
        glEnd();

        Window::displayUpdate();

        i+=1.0f/5000.0f;
        Audio::setSourcePosition(&s,-x,0.0f,-y);
        
    }
    Audio::destroySource(&s);
    Audio::destroyOpenAL();
    Window::destroyWindow();
    return 0;
}
