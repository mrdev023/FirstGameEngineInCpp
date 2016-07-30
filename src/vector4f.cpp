#include "math.h"

Vector4f::~Vector4f(){}

Vector4f::Vector4f(float vx,float vy,float vz,float vw) : x(vx),y(vy),z(vz),w(vw){}

Vector4f::Vector4f(const Vector4f& vec) : x(vec.x),y(vec.y),z(vec.z),w(vec.w){}

Vector4f::Vector4f() : x(0),y(0),z(0),w(0){}

float Vector4f::Sqrt(){
    return x * x + y * y + z * z + w * w;
}

float Vector4f::Magnitude(){
    return sqrt(Sqrt());
}

Vector4f Vector4f::Normalize(){
    return Vector4f(x/Magnitude(),y/Magnitude(),z/Magnitude(),w/Magnitude());
}


float Vector4f::Max(){
    if(x==y && y==z && z==w)return x;
    return (x > y)?((x>z)?((x>w)?x:w):z):y;
}

float Vector4f::Min(){
    if(x==y && y==z && z==w)return x;
    return (x < y)?((x<z)?((x<w)?x:w):z):y;
}

float Vector4f::SquaredDistance(Vector4f v){
    return (x-v.x)*(x-v.x) + (y-v.y)*(y-v.y) + (z-v.z)*(z-v.z) + (w-v.w)*(w-v.w);
}

float Vector4f::Distance(Vector4f v){
    return (float) sqrt(SquaredDistance(v));
}

Vector4f Vector4f::Lerp(Vector4f a,Vector4f b,float t){
    float x = lerp(a.x, b.x, t);
	float y = lerp(a.y, b.y, t);
    float z = lerp(a.z, b.z, t);
    float w = lerp(a.w, b.w, t);
    return Vector4f(x,y,z,w);
}

Vector4f Vector4f::CLerp(Vector4f a,Vector4f b,float t){
    float x = cLerp(a.x, b.x, t);
	float y = cLerp(a.y, b.y, t);
    float z = cLerp(a.z, b.z, t);
    float w = cLerp(a.w, b.w, t);
    return Vector4f(x,y,z,w);
}

Vector4f Vector4f::SLerp(Vector4f a,Vector4f b,float t){
    float x = sLerp(a.x, b.x, t);
	float y = sLerp(a.y, b.y, t);
    float z = sLerp(a.z, b.z, t);
    float w = sLerp(a.w, b.w, t);
    return Vector4f(x,y,z,w);
}

Vector4f Vector4f::Negate(){
    return Vector4f(-x,-y,-z,-w);
}

Vector4f Vector4f::Add(Vector4f v){
    return Vector4f(x + v.x,y + v.y,z + v.z,w + v.w);
}

Vector4f Vector4f::Sub(Vector4f v){
    return Vector4f(x - v.x,y - v.y,z - v.z,w - v.w);
}

Vector4f Vector4f::Div(Vector4f v){
    return Vector4f(x / v.x,y / v.y,z / v.z,w / v.w);
}

Vector4f Vector4f::Mul(Vector4f v){
    return Vector4f(x * v.x,y * v.y,z * v.z,w * v.w);
}

Vector4f Vector4f::Add(float a,float b,float c,float d){
    return Vector4f(x+a,y+b,z+c,w+d);
}

Vector4f Vector4f::Sub(float a,float b,float c,float d){
    return Vector4f(x-a,y-b,z-c,w-d);
}

Vector4f Vector4f::Div(float a,float b,float c,float d){
    return Vector4f(x/a,y/b,z/c,w/d);
}

Vector4f Vector4f::Mul(float a,float b,float c,float d){
    return Vector4f(x*a,y*b,z*c,w*d);
}

Vector4f Vector4f::Add(float a){
    return Vector4f(x+a,y+a,z+a,w+a);
}

Vector4f Vector4f::Sub(float a){
    return Vector4f(x-a,y-a,y-a,w-a);
}

Vector4f Vector4f::Div(float a){
    return Vector4f(x/a,y/a,z/a,w/a);
}

Vector4f Vector4f::Mul(float a){
    return Vector4f(x*a,y*a,z*a,w*a);
}

Vector4f Vector4f::Copy(){
    return Vector4f(x,y,z,w);
}

bool Vector4f::Equals(Vector4f v){
    return x == v.x && y == v.y && z == v.z && w == v.w;
}