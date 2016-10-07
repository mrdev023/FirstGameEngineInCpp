#include "math.h"

Vector3f Vector3f::UP(0,1,0);
Vector3f Vector3f::FRONT(0,0,1);
Vector3f Vector3f::RIGHT(1,0,0);

Vector3f::~Vector3f(){}

Vector3f::Vector3f(float vx,float vy,float vz) : x(vx),y(vy),z(vz){}

Vector3f::Vector3f(const Vector3f& vec) : x(vec.x),y(vec.y),z(vec.z){}

Vector3f::Vector3f() : x(0),y(0),z(0){}

float Vector3f::Sqrt(){
    return x * x + y * y + z * z;
}

float Vector3f::Magnitude(){
    return sqrt(Sqrt());
}

Vector3f Vector3f::Normalize(){
    return Vector3f(x/Magnitude(),y/Magnitude(),z/Magnitude());
}

Vector3f Vector3f::GtNorm(Vector3f ref){
    Vector3f result = Vector3f();
	Vector3f d = Vector3f(x - ref.x, y - ref.y, z - ref.z);
	float abx = abs(d.x);
	float aby = abs(d.y);
	float abz = abs(d.z);
	float good = max(max(abx, aby), abz);
	if (abx == good)
	{
		result.Add(1.0f, 0.0f, 0.0f);
		if (d.x < 0)
		    result.x *= -1;
	}
	if (aby == good)
	{
		result.Add(0.0f, 1.0f, 0.0f);
		if (d.y < 0)
			result.y *= -1;
	}
	if (abz == good)
	{
		result.Add(0.0f, 0.0f, 1.0f);
		if (d.z < 0)
			result.z *= -1;
	}

    return result;
}

Vector3f Vector3f::CheckNormals(){
    float m = max(max(x, y), z);
	float mi = min(min(x, y), z);
		
	float absMax = abs(m - 1);
	float absMin = abs(mi);
		
	float v = 0;
	if (absMax > absMin) v = mi;
	else v = m;
	int rv = 1;
		
	if (v < 0.5f) rv = -1;

    return Vector3f(v == x ? rv : 0, v == y ? rv : 0, v == z ? rv : 0);
}

Vector3f Vector3f::Cross(Vector3f r){
    float nx = y * r.z - z * r.y;
	float ny = z * r.x - x * r.z;
    float nz = x * r.y - y * r.x;
    return Vector3f(nx, ny, nz);
}

float Vector3f::Dot(Vector3f r){
    return x * r.x + y * r.y + z * r.z;
}

float Vector3f::Max(){
    if(x==y && y==z)return x;
    return (x > y)?((x>z)?x:z):y;
}

float Vector3f::Min(){
    if(x==y && y==z)return x;
    return (x < y)?((x<z)?x:z):y;
}

Vector3f Vector3f::Reflect(Vector3f normal){
    return Sub(normal.Copy().Mul(Dot(normal) * 2.0f));
}

Vector3f Vector3f::Refract(Vector3f v,float a){
    float dot = v.Dot(*this);
    float k = 1.f - a * a * (1.f - dot * dot);
    Vector3f res = v.Mul(this->Mul(a).Sub((float)(a * dot + sqrt(k))));
    return (k < 0.f)?Vector3f():res;
}

Vector3f Vector3f::Lerp(Vector3f a,Vector3f b,float t){
    float x = lerp(a.x, b.x, t);
	float y = lerp(a.y, b.y, t);
    float z = lerp(a.z, b.z, t);
    return Vector3f(x,y,z);
}

Vector3f Vector3f::CLerp(Vector3f a,Vector3f b,float t){
    float x = cLerp(a.x, b.x, t);
	float y = cLerp(a.y, b.y, t);
    float z = cLerp(a.z, b.z, t);
    return Vector3f(x,y,z);
}

Vector3f Vector3f::CLerp(Vector3f a, Vector3f b, float t1, float t2, float t3) {
		float ft1 = (float) (t1 * PI);
		float f1 = (float) ((1.f - cos(ft1)) * 0.5f);
		float ft2 = (float) (t2 * PI);
		float f2 = (float) ((1.f - cos(ft2)) * 0.5f);
		float ft3 = (float) (t3 * PI);
		float f3 = (float) ((1.f - cos(ft3)) * 0.5f);
		
		float x = a.x * (1.f - f1) + b.x * f1;
		float y = a.y * (1.f - f2) + b.y * f2;
		float z = a.z * (1.f - f3) + b.z * f3;
		
		return Vector3f(x, y, z);
}

Vector3f Vector3f::SLerp(Vector3f a,Vector3f b,float t){
    float x = sLerp(a.x, b.x, t);
	float y = sLerp(a.y, b.y, t);
    float z = sLerp(a.z, b.z, t);
    return Vector3f(x,y,z);
}

Vector3f Vector3f::Negate(){
    return Vector3f(-x,-y,-z);
}

Vector3f Vector3f::Add(Vector3f v){
    return Vector3f(x + v.x,y + v.y,z + v.z);
}

Vector3f Vector3f::Sub(Vector3f v){
    return Vector3f(x - v.x,y - v.y,z - v.z);
}

Vector3f Vector3f::Div(Vector3f v){
    return Vector3f(x / v.x,y / v.y,z / v.z);
}

Vector3f Vector3f::Mul(Vector3f v){
    return Vector3f(x * v.x,y * v.y,z * v.z);
}

Vector3f Vector3f::Add(float a,float b,float c){
    return Vector3f(x+a,y+b,z+c);
}

Vector3f Vector3f::Sub(float a,float b,float c){
    return Vector3f(x-a,y-b,z-c);
}

Vector3f Vector3f::Div(float a,float b,float c){
    return Vector3f(x/a,y/b,z/c);
}

Vector3f Vector3f::Mul(float a,float b,float c){
    return Vector3f(x*a,y*b,z*c);
}

Vector3f Vector3f::Add(float a){
    return Vector3f(x+a,y+a,z+a);
}

Vector3f Vector3f::Sub(float a){
    return Vector3f(x-a,y-a,y-a);
}

Vector3f Vector3f::Div(float a){
    return Vector3f(x/a,y/a,z/a);
}

Vector3f Vector3f::Mul(float a){
    return Vector3f(x*a,y*a,z*a);
}

Vector3f Vector3f::Reo(){
	Vector3f result = Vector3f();
		
	result.x = 1 - x;
	result.y = 1 - y;
	result.z = 1 - z;
				
	return result;
}

Vector3f Vector3f::Abs(){
	float lx = x;
	float ly = y;
	float lz = z;
		if (lx < 0)
			lx = -lx;
		if (ly < 0)
			ly = -ly;
		if (lz < 0)
			lz = -lz;		
	return Vector3f(lx,ly,lz);
}

Vector3f Vector3f::Rotate(Quaternion rot){
	Quaternion w = rot.Mul(*this).Mul(rot.Conjugate());
	return Vector3f(w.x, w.y, w.z);
}

Vector3f Vector3f::Copy(){
    return Vector3f(x,y,z);
}

bool Vector3f::Equals(Vector3f v){
    return x == v.x && y == v.y && z == v.z;
}