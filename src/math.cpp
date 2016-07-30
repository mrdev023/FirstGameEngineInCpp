#include "math.h"

const float PI = 3.14159265358979323846264338327950288419716939937510582f;

float lerp(float s,float e,float t){
    return s + (e - s) * t;
}

float cLerp(float s, float e, float t){
    float t2 = (1 - (float) cos(t * PI)) / 2;
    return (s * (1 - t2) + e * t2);
}

float sLerp(float s, float e, float t){
    float t2 = (1 - (float) sin(t * PI)) / 2;
    return (s * (1 - t2) + e * t2);
}

float bLerp(float c00, float c10, float c01, float c11, float tx, float ty){
    return cLerp(cLerp(c00, c10, tx), cLerp(c01, c11, tx), ty);
}

float clamp(float min, float max, float value){
    if (value < min)value = min;
    if (value > max)value = max;
    return value;
}

float min(float a, float b){
    if(a==b)return a;
    return (a < b)?a:b;
}

float max(float a, float b){
    if(a==b)return a;
    return (a > b)?a:b;
}

int norm(float v){
    return (v>=0)?1:-1;
}

float abs(float a){
    return (a<0)?-a:a;
}

float nearest(float a, float b, float v){
    float absA = abs(a);
    float absB = abs(b);
    float absV = abs(v);
    float tempA = abs(absV - absA);
    float tempB = abs(absV - absB);
    if (tempA < tempB)return a;
    return b;
}

float toRadians(float d){
    return d * 2.0f * PI /360.0f;
}

float toDegrees(float r){
    return r * 360.0f / (2.0f * PI);
}
