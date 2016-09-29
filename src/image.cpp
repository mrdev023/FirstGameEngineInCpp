#include "renderer.h"

Image::Image(unsigned char* data,int width,int height){
    this->data = data;
    this->width = width;
    this->height = height;
}

Image::~Image(){
    delete this->data;
}