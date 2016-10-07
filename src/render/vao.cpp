#include "renderer.h"

VAO::VAO(GLuint typeRender){
    this->typeRender = typeRender;
    this->data.push_back(new VBO(typeRender));
    this->data.push_back(new VBO(typeRender));
    this->data.push_back(new VBO(typeRender));
    this->data.push_back(new VBO(typeRender));
}

VAO::~VAO(){
    for(int i = 0;i < 4;i++){
        delete this->data[i];
    }
    this->data.clear();
}

void VAO::addData(int type,float* data,int size){
    this->data[type]->addData(data,size);
}

void VAO::bufferData(){
    for(int i = 0;i < 4;i++){
        this->data[i]->bufferData();
    }
}
    
void VAO::render2D(){
    
}
    
void VAO::render3D(){

}