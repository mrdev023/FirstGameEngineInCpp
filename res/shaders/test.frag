#version 330

in vec4 color;
in vec3 normal;
in vec2 out_coord_texture;
uniform sampler2D myTexture;

void main(void){
    gl_FragColor = color * texture2D(myTexture,out_coord_texture);
}
