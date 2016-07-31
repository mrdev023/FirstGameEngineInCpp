uniform float a;

void main(void){
    if(a >= 0)gl_FragColor = vec4(a,0,0,1);
    else gl_FragColor = vec4(0,-a,0,1);
}