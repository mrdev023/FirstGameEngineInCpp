#include "renderer.h"

VAO::VAO(GLuint typeRender,unsigned int nm,bool isIn3DRender){
    glGenVertexArrays(1,&id);
    glBindVertexArray(id);
    this->typeRender = typeRender;
    for(int i = 0;i < 4;i++){
        data.push_back(new VBO(typeRender,isIn3DRender));
    }
    glBindVertexArray(0);
    this->n = nm;
    this->isIn3DRender = isIn3DRender;
}

VAO::~VAO(){
    glBindVertexArray(id);
    for(int i = 0;i < this->n;i++){
        delete this->data[i];
    }
    this->data.clear();
    glBindVertexArray(0);
    glDeleteVertexArrays(1,&id);
}

void VAO::addData(int i,float* data,int size){
    glBindVertexArray(id);
    this->data[i]->addData(data,size);
    glBindVertexArray(0);
}

void VAO::bufferData(){
    glBindVertexArray(id);
    for(int i = 0;i < 4;i++){
        this->data[i]->bufferData();
    }
    glBindVertexArray(0);
}
    
void VAO::render(){
    glBindVertexArray(id);
    for(int i = 0;i < 4;i++){
        this->data[i]->render();
    }
    glBindVertexArray(0);
}
