#ifndef RENDERER_H
#define RENDERER_H

#include "../math/math.h"


#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
#include <fstream>
#include <malloc.h>
#include <string>
#include <sys/stat.h>
#include <algorithm>

#include "lodepng.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

bool fileExists(const std::string&);

class Shader;
class Texture;
class Image;
class VBO;
class VAO;


class VAO{
    public:
    std::vector<VBO*> data;
    unsigned int n;
    bool isIn3DRender;
    GLuint id;
    GLuint typeRender;

    VAO(GLuint,unsigned int,bool);
    ~VAO();
    void addData(int,float*,int);
    void bufferData();
    void render();
};

class VBO{

    private:
    void render2D();
    void render3D();
    void bufferData2D();
    void bufferData3D();

    public:
    GLuint id;
    GLuint typeRender;
    bool isIn3DRender;
    std::vector<float> data;
    int size;

    VBO();
    VBO(GLuint,bool);
    ~VBO();
    void addData(float*,int);
    void bufferData();
    void render();
    void bindBuffer();
    void unBindBuffer();
};

class Image{
    public:
    unsigned char* data;
    int width;
    int height;

    Image(unsigned char*,int,int);
    ~Image();
};

class Texture{
    public:
    static Texture* createTexture(const char*);
    static void destroyTexture(GLuint*);
    static void bindTexture(GLuint*);
    static void unbindTexture();

    double ratioX;
    double ratioY;
    GLuint* id;

    Texture(GLuint,double,double);
    ~Texture();

    private:
    static Image* loadTexture(const char*);
};

class Shader{
    public:
    static std::string LoadSource(const char*);
    static GLuint createShader(const char*,const char*);
    static void destroyShader(GLuint*);
    static void bindShader(GLuint*);
    static void unbindShader();
    static void setUniform(GLuint*,const char*,float);
    static void setUniform(GLuint*,const char*,Vector3f);
    static void setUniform(GLuint*,const char*,Vector2f);
    static void setUniform(GLuint*,const char*,Vector4f);
    static void setUniform(GLuint*,const char*,Quaternion);
    static void setUniform(GLuint*,const char*,Matrix4f);
};

#endif