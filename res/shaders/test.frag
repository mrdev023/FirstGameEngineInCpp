#version 150

uniform float y;

void main(void){
    gl_FragColor= vec4(1, 1 - abs(y)/50,1 - abs(y)/50,1);
}