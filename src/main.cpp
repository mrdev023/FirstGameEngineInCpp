#include "window.h"
#include "audio.h"
#include "renderer.h"

#include <iostream>
#include <fstream>

void event(SDL_Event e){
    
}

int main(int argc, char** argv){
    Window::initWindow(800,600,"Test");
    Audio::initOpenAL();
    GLuint s = Shader::createShader("test.vert","test.frag");
    float i = 0;
    Shader::bindShader(&s);
    while(!Window::closeRequested){//main loop
        Shader::setUniform(&s,"a",cos(i));
        Window::pollEvent(&event);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glLoadIdentity();
        glBegin(GL_QUADS);
        glVertex2f(-1,-1);
        glVertex2f(-1,1);
        glVertex2f(1,1);
        glVertex2f(1,-1);
        glEnd();

        Window::displayUpdate();
        i+=1/5000.0f;
    }
    Shader::destroyShader(&s);
    Audio::destroyOpenAL();
    Window::destroyWindow();

    return 0;
}
