#include "renderer.h"

Texture::Texture(GLuint id,double u3,double v3){
    this->id = new GLuint(id);
    this->ratioX = u3;
    this->ratioY = v3;
}

Texture::~Texture(){
    Texture::destroyTexture(this->id);
    delete this->id;
}

Texture* Texture::createTexture(const char* file){
    Image* img = Texture::loadTexture(file);
    if(img == NULL)return NULL;
    GLuint t;
    glGenTextures(1, &t);
    glBindTexture(GL_TEXTURE_2D, t);

        // Texture size must be power of two for the primitive OpenGL version this is written for. Find next power of two.
    size_t u2 = 1; while(u2 < img->width) u2 *= 2;
    size_t v2 = 1; while(v2 < img->height) v2 *= 2;
    // Ratio for power of two version compared to actual version, to render the non power of two image with proper size.
    double u3 = (double)img->width / u2;
    double v3 = (double)img->height / v2;

    // Make power of two version of the image.
    std::vector<unsigned char> image2(u2 * v2 * 4 * (img->width/48));
    for(size_t y = 0; y < img->height; y++)
    for(size_t x = 0; x < img->width; x++)
    for(size_t c = 0; c < 4; c++)
    {
        image2[4 * u2 * y + 4 * x + c] = img->data[4 * img->width * y + 4 * x + c];
    }
    
    // Enable the texture for OpenGL.
    glEnable(GL_TEXTURE_2D);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_NEAREST = no smoothing
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, u2, v2, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image2[0]);

    std::cout << "GL Texture created (" << file << ":" << img->width << "x" << img->height << ") #" << t << " !" << std::endl;
    image2.clear();
    delete img;
    
    return new Texture(t,u3,v3);
}

void Texture::bindTexture(GLuint* texture){
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glDisable(GL_ALPHA_TEST);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,*texture);
}

void Texture::unbindTexture(){
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,0);
}

void Texture::destroyTexture(GLuint* texture){
    glDeleteTextures(1,texture);
}

Image* Texture::loadTexture(const char* file){
    std::vector<unsigned char> image; //the raw pixels
    unsigned width, height;

    //decode
    unsigned error = lodepng::decode(image, width, height, file);

    //if there's an error, display it
    if(error){
        std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
        return NULL;
    } 

    //the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...

    std::cout << "Image loaded (" << file << ") ! : " << width << "x" << height << " with " << image.size() << " byte of data." << std::endl;

    unsigned char* p = (unsigned char*)malloc(sizeof(unsigned char) * image.size());
    for(int i = 0;i < image.size();i++)p[i] = image[i];
    image.clear();
    return new Image(p,width,height);
}