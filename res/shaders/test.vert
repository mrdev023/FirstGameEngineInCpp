#version 330

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec4 in_color;
layout (location = 2) in vec2 in_coord_texture;
layout (location = 3) in vec3 in_normal;

out vec4 color;
out vec3 normal;
out vec2 out_coord_texture;

void main(void){
    gl_FrontColor = gl_Color;
    gl_Position = gl_ModelViewProjectionMatrix *  vec4(in_position,1.0f);
}
