#include "window.h"
#include "audio.h"
#include "renderer.h"

void event(SDL_Event e){
    switch( e.type ){
        case SDL_KEYDOWN:
            switch( e.key.keysym.sym ){
                
            }
            break;
        case SDL_KEYUP:
            switch( e.key.keysym.sym ){
                
            }
            break;
    }
}

int main(int argc, char** argv){
    Window::initWindow(800,800,"Title");
    //Texture* t = Texture::createTexture("res/images/2x2_grid.png");
    Texture* t = Texture::createTexture("res/images/pearl-0003.png");
    while(!Window::closeRequested){
        Window::pollEvent(event);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Texture::bindTexture(t->id);
        glBegin(GL_QUADS);
            glColor3f(1,1,1);
            glTexCoord2f(0,0);
            glVertex2i(-1,-1);
            glTexCoord2f(0,t->ratioY);
            glVertex2i(-1,1);
            glTexCoord2f(t->ratioX,t->ratioY);
            glVertex2i(1,1);
            glTexCoord2f(t->ratioX,0);
            glVertex2i(1,-1);
        glEnd();
        Window::displayUpdate();
    }
    delete t;
    Window::destroyWindow();
    return 0;
}

