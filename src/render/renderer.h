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
    static const int VERTEX_DATA = 0,COLOR_DATA = 1,TEX_COORD_DATA = 2,NORMAL_DATA = 3;
    std::vector<VBO*> data;
    GLuint id;
    GLuint typeRender;

    VAO(GLuint);
    ~VAO();
    void addData(int,float*,int);
    void bufferData();
    void render2D();
    void render3D();
};

class VBO{

    public:
    GLuint id;
    GLuint typeRender;
    std::vector<float> data;
    int size;

    VBO();
    VBO(GLuint);
    ~VBO();
    void addData(float*,int);
    void bufferData();
    void render2D();
    void render3D();
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