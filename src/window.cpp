#include "window.h"

SDL_Window* Window::pWindow = NULL;
SDL_Event Window::event;
SDL_GLContext Window::context;
bool Window::closeRequested = false;


void Window::initWindow(int width,int height,std::string title){
    /* Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO) != 0 ){
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        exit(-1);
    }

    Window::pWindow = SDL_CreateWindow(title.c_str(),SDL_WINDOWPOS_UNDEFINED,
                                                                  SDL_WINDOWPOS_UNDEFINED,
                                                                  width,
                                                                  height,
                                                                  SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if(!Window::pWindow){
        fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
        exit(-1);
    }

    context = SDL_GL_CreateContext(pWindow);

    glewExperimental = true; 
    GLenum err = glewInit(); 

    printf("----------------------------------------------------------------\n");
    printf("Graphics Successfully Initialized\n");
    printf("OpenGL Info\n");
    printf("    Version: %s\n", glGetString(GL_VERSION));
    printf("     Vendor: %s\n", glGetString(GL_VENDOR));
    printf("   Renderer: %s\n", glGetString(GL_RENDERER));
    printf("    Shading: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    GLint n, i;
    glGetIntegerv(GL_NUM_EXTENSIONS, &n);
    printf("OpenGL Extensions:\n");
    for (i = 0; i < n; i++) {
        printf("             %s\n", glGetStringi(GL_EXTENSIONS, i));
    }
    printf("----------------------------------------------------------------\n");

}

void Window::destroyWindow(){
    SDL_GL_DeleteContext ( context ) ; 
    SDL_DestroyWindow(pWindow);
    SDL_Quit();
    exit(0);
}

void Window::displayUpdate(){
    SDL_GL_SwapWindow(Window::pWindow);
}

void Window::pollEvent(void(*f)(SDL_Event)){
    while (SDL_PollEvent(&Window::event)){
        switch(Window::event.type){
            case SDL_QUIT:
            Window::closeRequested = true;
            break;
        }
        f(Window::event);
    }
}
