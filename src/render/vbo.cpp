#include "renderer.h"

VBO::VBO(){
    this->typeRender = GL_TRIANGLE_STRIP;
    glGenBuffers(1,&this->id);
    this->size = 0;
}

VBO::VBO(GLuint typeRender){
    this->typeRender = typeRender;
    glGenBuffers(1,&this->id);
    this->size = 0;
}

VBO::~VBO(){
    this->data.clear();
    glDeleteBuffers(1,&this->id);
}
    
void VBO::addData(float* data,int size){
    for(int i = 0;i < size;i++){
        this->data.push_back(data[i]);
    }
    this->size += size;
}
    
void VBO::bufferData(){
    glBindBuffer(GL_ARRAY_BUFFER,this->id);
    glBufferData(GL_ARRAY_BUFFER, this->size,&this->data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,0);
}

void VBO::bindBuffer(){
    glBindBuffer(GL_ARRAY_BUFFER,this->id);
}
    
void VBO::unBindBuffer(){
    glBindBuffer(GL_ARRAY_BUFFER,0);
}
    
void VBO::render2D(){
    // Plus tard pas besoin pour l instant
}

void VBO::render3D(){
    // Plus tard pas besoin pour l instant
}