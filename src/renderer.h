#ifndef RENDERER_H
#define RENDERER_H

#include "math.h"

#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
#include <fstream>
#include <malloc.h>
#include <string>
#include <sys/stat.h>
#include <algorithm>

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

bool fileExists(const std::string&);

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