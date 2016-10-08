#include "renderer.h"

VBO::VBO(){
    this->typeRender = GL_TRIANGLE_STRIP;
    glGenBuffers(1,&this->id);
    this->size = 0;
    this->isIn3DRender = true;
}

VBO::VBO(GLuint typeRender,bool isIn3DRender){
    this->typeRender = typeRender;
    glGenBuffers(1,&this->id);
    this->size = 0;
    this->isIn3DRender = isIn3DRender;
}

VBO::~VBO(){
    this->data.clear();
    glDeleteBuffers(1,&this->id);
}
    
// 2 ou 3 vertex + 4 color (RGBA) + TexCoords + Normal
void VBO::addData(float* data,int size){
    for(int i = 0;i < size;i++){
        this->data.push_back(data[i]);
    }
    this->size += size;
}
    
void VBO::bufferData(){
    if(this->isIn3DRender) bufferData3D();
    else bufferData2D();
}

void VBO::bufferData2D(){
    glBindBuffer(GL_ARRAY_BUFFER,this->id);
    glBufferData(GL_ARRAY_BUFFER, this->size,&this->data[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, (2 + 3 + 4 + 2) * sizeof(float), 0);
		
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, false, (2 + 3 + 4 + 2) * sizeof(float), (void*)(2 * sizeof(float)));
		
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, false, (2 + 3 + 4 + 2) * sizeof(float), (void*)((2 + 3) * sizeof(float)));
		
	glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, false, (2 + 3 + 4 + 2) * sizeof(float), (void*)((2 + 3 + 4) * sizeof(float)));

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);

    glBindBuffer(GL_ARRAY_BUFFER,0);
}

void VBO::bufferData3D(){
    glBindBuffer(GL_ARRAY_BUFFER,this->id);
    glBufferData(GL_ARRAY_BUFFER, this->size,&this->data[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, (3 + 3 + 4 + 2) * sizeof(float), 0);
		
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, false, (3 + 3 + 4 + 2) * sizeof(float), (void*)(3 * sizeof(float)));
		
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, false, (3 + 3 + 4 + 2) * sizeof(float), (void*)((3 + 3) * sizeof(float)));
		
	glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, false, (3 + 3 + 4 + 2) * sizeof(float), (void*)((3 + 3 + 4) * sizeof(float)));

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);

    glBindBuffer(GL_ARRAY_BUFFER,0);
}

void VBO::bindBuffer(){
    glBindBuffer(GL_ARRAY_BUFFER,this->id);
}
    
void VBO::unBindBuffer(){
    glBindBuffer(GL_ARRAY_BUFFER,0);
}

void VBO::render(){
    if(this->isIn3DRender) render3D();
    else render2D();
    
}
    
void VBO::render2D(){
    glBindBuffer(GL_ARRAY_BUFFER,this->id);

    glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    glDrawArrays(GL_QUADS, 0, size/(2 + 3 + 4 + 2));

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);

    glBindBuffer(GL_ARRAY_BUFFER,0);
}

void VBO::render3D(){
    glBindBuffer(GL_ARRAY_BUFFER,this->id);

    glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    glDrawArrays(GL_QUADS, 0, size/(3 + 3 + 4 + 2));

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);

    glBindBuffer(GL_ARRAY_BUFFER,0);
}