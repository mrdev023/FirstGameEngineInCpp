#include "renderer.h"

std::string Shader::LoadSource(const char* filename){
    std::string file("");
    std::ifstream in_stream;
    std::string line;
    std::vector<const char*> v;

    std::string* ff = new std::string(filename);
    std::string* path = new std::string("res/shaders/");
    *ff = *path + *ff;
    in_stream.open(ff->c_str());
    delete ff;
    delete path;

    int l = 1;
    for( std::string line; getline( in_stream, line ); )
    {
        if(line.substr(0,8) != "#include"){
            file += line + "\n";
        }else{
            std::string str = line;
            std::istringstream buf(str);
            std::istream_iterator<std::string> beg(buf), end;

            std::vector<std::string> tokens(beg, end); // done!
            if(tokens.size() == 2){
                std::string fileName = tokens.at(1).substr(1,tokens.at(1).size() - 2);
                bool a = fileExists(fileName);
                if (a){
                    if(std::find(v.begin(), v.end(), fileName.c_str()) == v.end()){
                        file = file + std::string(Shader::LoadSource(fileName.c_str()));
                        v.push_back(fileName.c_str());
                    }
                }else{printf("Syntax incorrect #%d : include file '%s' not exist",l,fileName.c_str());}
            }else{
                printf("Syntax incorrect #%d : expected identifier after ‘include’ token",l);
            }
        }
        l++;
    }
    in_stream.close();
    return file;
}

void Shader::destroyShader(GLuint* s){
    glDeleteProgram(*s);
}

GLuint Shader::createShader(const char* vertName,const char* fragName){
    std::string vert = Shader::LoadSource(vertName);
    std::string frag = Shader::LoadSource(fragName);
    GLuint vertShader;
    GLuint fragShader;

    vertShader = glCreateShader(GL_VERTEX_SHADER);
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    if(vertShader == 0 || fragShader == 0){
        printf("Shader not created !");
        if(vertShader != 0)glDeleteShader(vertShader);
        if(fragShader != 0)glDeleteShader(fragShader);
        return 0;
    }

    const char* a = ((const char*)vert.c_str());
    const char* b = ((const char*)frag.c_str());

    glShaderSource(vertShader,1,(const GLchar**)&a,NULL);
    glShaderSource(fragShader,1,(const GLchar**)&b,NULL);

    glCompileShader(vertShader);
    GLint compile_status = GL_TRUE;
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &compile_status);
    if(compile_status != GL_TRUE){
        char *log = NULL;
        GLsizei logsize = 0;
        glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logsize);
        log = (char*)malloc(logsize + 1);
        if(log == NULL)
        {
            fprintf(stderr, "impossible d'allouer de la memoire !\n");
            return 0;
        }
        memset(log, '\0', logsize + 1);
        glGetShaderInfoLog(vertShader, logsize, &logsize, log);
        fprintf(stderr, "impossible de compiler le shader '%s' :\n%s",vertName,log);
        free(log);
        glDeleteShader(vertShader);
        glDeleteShader(fragShader);
        return 0;
    }
    glCompileShader(fragShader);
    compile_status = GL_TRUE;
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &compile_status);
    if(compile_status != GL_TRUE){
        char *log = NULL;
        GLsizei logsize = 0;
        glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logsize);
        log = (char*)malloc(logsize + 1);
        if(log == NULL)
        {
            fprintf(stderr, "impossible d'allouer de la memoire !\n");
            return 0;
        }
        memset(log, '\0', logsize + 1);
        glGetShaderInfoLog(fragShader, logsize, &logsize, log);
        fprintf(stderr, "impossible de compiler le shader '%s' :\n%s",fragName,log);
        free(log);
        glDeleteShader(vertShader);
        glDeleteShader(fragShader);
        return 0;
    }
    GLuint program;
    program = glCreateProgram();
    glAttachShader(program,vertShader);
    glAttachShader(program,fragShader);
    glLinkProgram(program);
    GLint linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked)
    {
    	printf("Program not linked !");
        glDeleteShader(vertShader);
        glDeleteShader(fragShader);
        glDeleteProgram(program);
        return 0;
    }  
    glValidateProgram(program);
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    return program;
}

void Shader::bindShader(GLuint* s){
    glUseProgram(*s);
}

void Shader::unbindShader(){
    glUseProgram(0);
}

bool fileExists(const std::string& filename)
{
    struct stat buf;
    if (stat(filename.c_str(), &buf) != -1)
    {
        return true;
    }
    return false;
}

void Shader::setUniform(GLuint* program,const char* varName,float value){
    glUniform1f(glGetUniformLocation(*program,varName),value);
}

void Shader::setUniform(GLuint* program,const char* varName,Vector2f v){
    glUniform2f(glGetUniformLocation(*program,varName),v.x,v.y);
}

void Shader::setUniform(GLuint* program,const char* varName,Vector3f v){
    glUniform3f(glGetUniformLocation(*program,varName),v.x,v.y,v.z);
}

void Shader::setUniform(GLuint* program,const char* varName,Vector4f v){
    glUniform4f(glGetUniformLocation(*program,varName),v.x,v.y,v.z,v.w);
}

void Shader::setUniform(GLuint* program,const char* varName,Quaternion v){
    glUniform4f(glGetUniformLocation(*program,varName),v.x,v.y,v.z,v.w);
}

void Shader::setUniform(GLuint* program,const char* varName,Matrix4f ma){
    glUniformMatrix4fv(glGetUniformLocation(*program,varName),01,0,ma.GetComponents());
}