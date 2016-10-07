#include "math.h"

Vector2f Vector2f::UP(0,1);
Vector2f Vector2f::RIGHT(1,0);

Vector2f::~Vector2f(){}

Vector2f::Vector2f(float vx,float vy) : x(vx),y(vy){}

Vector2f::Vector2f(const Vector2f& vec) : x(vec.x),y(vec.y){}

Vector2f::Vector2f() : x(0),y(0){}

float Vector2f::Sqrt(){
    return x * x + y * y;
}

float Vector2f::Magnitude(){
    return sqrt(Sqrt());
}

Vector2f Vector2f::Normalize(){
    return Vector2f(x/Magnitude(),y/Magnitude());
}

Vector2f Vector2f::Cross(Vector2f v){
    return Vector2f(v.x,-v.y);
}

float Vector2f::Dot(Vector2f v){
    return x * v.x + y * v.y;
}

float Vector2f::Max(){
    if(x==y)return x;
    return (x > y)?x:y;
}

float Vector2f::Min(){
    if(x==y)return x;
    return (x < y)?x:y;
}

Vector2f Vector2f::Reflect(Vector2f v){
    return this->Sub(v.Mul(this->Dot(v) * 2.0f));
}

Vector2f Vector2f::Refract(Vector2f v,float a){
    float dot = v.Dot(*this);
    float k = 1.f - a * a * (1.f - dot * dot);
    Vector2f res = v.Mul(this->Mul(a).Sub((float)(a * dot + sqrt(k))));
    return (k < 0.f)?Vector2f():res;
}

Vector2f Vector2f::Lerp(Vector3f v,Vector3f v2,float t){
    float x = lerp(v.x,v2.x,t);
    float y = lerp(v.y,v2.y,t);
    return Vector2f(x,y);
}

Vector2f Vector2f::CLerp(Vector3f v,Vector3f v2,float t){
    float x = cLerp(v.x,v2.x,t);
    float y = cLerp(v.y,v2.y,t);
    return Vector2f(x,y);
}

Vector2f Vector2f::SLerp(Vector3f v,Vector3f v2,float t){
    float x = sLerp(v.x,v2.x,t);
    float y = sLerp(v.y,v2.y,t);
    return Vector2f(x,y);
}

Vector2f Vector2f::Negate(){
    return Vector2f(-x,-y);
}

Vector2f Vector2f::Add(Vector2f v){
    return Vector2f(x + v.x,y + v.y);
}

Vector2f Vector2f::Sub(Vector2f v){
    return Vector2f(x - v.x,y - v.y);
}

Vector2f Vector2f::Div(Vector2f v){
    return Vector2f(x / v.x,y / v.y);
}

Vector2f Vector2f::Mul(Vector2f v){
    return Vector2f(x * v.x,y * v.y);
}

Vector2f Vector2f::Add(float a,float b){
    return Vector2f(x+a,y+b);
}

Vector2f Vector2f::Sub(float a,float b){
    return Vector2f(x-a,y-b);
}

Vector2f Vector2f::Div(float a,float b){
    return Vector2f(x/a,y/b);
}

Vector2f Vector2f::Mul(float a,float b){
    return Vector2f(x*a,y*b);
}

Vector2f Vector2f::Add(float a){
    return Vector2f(x+a,y+a);
}

Vector2f Vector2f::Sub(float a){
    return Vector2f(x-a,y-a);
}

Vector2f Vector2f::Div(float a){
    return Vector2f(x/a,y/a);
}

Vector2f Vector2f::Mul(float a){
    return Vector2f(x*a,y*a);
}

Vector2f Vector2f::Copy(){
    return Vector2f(x,y);
}

bool Vector2f::Equals(Vector2f v){
    return x == v.x && y == v.y;
}
