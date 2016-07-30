#include "math.h"

Quaternion::~Quaternion(){}

Quaternion::Quaternion(){
    this->x = 0;
	this->y = 0;
	this->z = 0;
    this->w = 1;
}

Quaternion::Quaternion(const Quaternion& v){
    this->x = v.x;
	this->y = v.y;
	this->z = v.z;
    this->w = v.w;
}

Quaternion::Quaternion(float x, float y, float z, float w){
    this->x = x;
	this->y = y;
	this->z = z;
    this->w = w;
}

Quaternion::Quaternion(Vector3f axis,float angle){
    float s = (float) sin(angle / 2);
	float c = (float) cos(angle / 2);

	this->x = axis.x * s;
	this->y = axis.y * s;
	this->z = axis.z * s;
    this->w = c;
}

Quaternion::Quaternion(const Quaternion& q,Vector3f axis,float angle){
    float s = (float) sin(angle / 2);
	float c = (float) cos(angle / 2);

	this->x = q.x + (axis.x * s);
	this->y = q.y + (axis.y * s);
	this->z = q.z + (axis.z * s);
    this->w = q.w + (c);
}

Quaternion::Quaternion(Vector3f euler){
    float c1 = (float) cos(euler.x / 2);
	float s1 = (float) sin(euler.x / 2);
		
	float c2 = (float) cos(euler.y / 2);
	float s2 = (float) sin(euler.y / 2);
		
	float c3 = (float) cos(euler.z / 2);
	float s3 = (float) sin(euler.z / 2);
		
	float c1c2 = c1 * c2;
	float s1s2 = s1 * s2;

	x = c1c2 * s3 + s1s2 * c3;
	y = s1 * c2 * c3 + c1 * s2 * s3;
	z = c1 * s2 * c3 - s1 * c2 * s3;
    w = c1c2 * c3 - s1s2 * s3;
}

Quaternion::Quaternion(Matrix4f rot){
    float trace = rot.m[0][0] + rot.m[1][1] + rot.m[2][2];
	if (trace > 0) {
		float s = 0.5f / (float) sqrt(trace + 1.0f);
		w = 0.25f / s;
		x = (rot.m[1][2] - rot.m[2][1]) * s;
		y = (rot.m[2][0] - rot.m[0][2]) * s;
		z = (rot.m[0][1] - rot.m[1][0]) * s;
	} else {
		if (rot.m[0][0] > rot.m[1][1] && rot.m[0][0] > rot.m[2][2]) {
			float s = 2.0f * (float) sqrt(1.0f + rot.m[0][0] - rot.m[1][1] - rot.m[2][2]);
			w = (rot.m[1][2] - rot.m[2][1]) / s;
			x = 0.25f * s;
			y = (rot.m[1][0] + rot.m[0][1]) / s;
			z = (rot.m[2][0] + rot.m[0][2]) / s;
		} else if (rot.m[1][1] > rot.m[2][2]) {
			float s = 2.0f * (float) sqrt(1.0f + rot.m[1][1] - rot.m[0][0] - rot.m[2][2]);
			w = (rot.m[2][0] - rot.m[0][2]) / s;
			x = (rot.m[1][0] + rot.m[0][1]) / s;
			y = 0.25f * s;
			z = (rot.m[2][1] + rot.m[1][2]) / s;
		} else {
			float s = 2.0f * (float) sqrt(1.0f + rot.m[2][2] - rot.m[0][0] - rot.m[1][1]);
			w = (rot.m[0][1] - rot.m[1][0]) / s;
			x = (rot.m[2][0] + rot.m[0][2]) / s;
			y = (rot.m[1][2] + rot.m[2][1]) / s;
			z = 0.25f * s;
		}
	}
	float length = (float) sqrt(x * x + y * y + z * z + w * w);
	x /= length;
	y /= length;
	z /= length;
    w /= length;
}

Quaternion Quaternion::Euler(float yaw, float pitch, float roll){
    float angle;
    float sinRoll, sinPitch, sinYaw, cosRoll, cosPitch, cosYaw;
        
    angle = pitch * 0.5f;
    sinPitch = sin(angle);
    cosPitch = cos(angle);
        
    angle = roll * 0.5f;
    sinRoll = sin(angle);
    cosRoll = cos(angle);
        
    angle = yaw * 0.5f;
    sinYaw = sin(angle);
    cosYaw = cos(angle);

    float cosRollXcosPitch = cosRoll * cosPitch;
    float sinRollXsinPitch = sinRoll * sinPitch;
    float cosRollXsinPitch = cosRoll * sinPitch;
    float sinRollXcosPitch = sinRoll * cosPitch;
        
    Quaternion r = Quaternion();
        
    r.w = (cosRollXcosPitch * cosYaw - sinRollXsinPitch * sinYaw);
    r.x = (cosRollXcosPitch * sinYaw + sinRollXsinPitch * cosYaw);
    r.y = (sinRollXcosPitch * cosYaw + cosRollXsinPitch * sinYaw);
    r.z = (cosRollXsinPitch * cosYaw - sinRollXcosPitch * sinYaw);

    return r.Normalize();
}

Quaternion Quaternion::Euler(Vector3f euler){
    return Quaternion::Euler(euler.x, euler.z, euler.y);
}

Quaternion Quaternion::LookAt(Vector3f sourcePoint, Vector3f destPoint){
    Vector3f forwardVector = Vector3f(destPoint).Sub(sourcePoint).Normalize();

	float dot = Vector3f(0, 0, 1).Dot(forwardVector);

	if (abs(dot - (-1.0f)) < 0.000001f){
		return Quaternion(Vector3f::UP.x, Vector3f::UP.y, Vector3f::UP.z, PI);
	}
	if (abs(dot - (1.0f)) < 0.000001f){
		return Quaternion();
	}

	float rotAngle = acos(dot);
	Vector3f rotAxis = Vector3f(0, 0, 1).Cross(forwardVector).Normalize();
    return CreateFromAxisAngle(rotAxis, rotAngle);
}

Quaternion Quaternion::CreateFromAxisAngle(Vector3f axis, float angle){
    float halfAngle = angle * 0.5f;
	float s = sin(halfAngle);
	Quaternion q = Quaternion();
	q.x = axis.x * s;
	q.y = axis.y * s;
	q.z = axis.z * s;
	q.w = cos(halfAngle);
    return q;
}

float Quaternion::Magnitude(){
    return (float)sqrt(x * x + y * y + z * z + w * w);
}

Quaternion Quaternion::Normalize(){
    float mag = Magnitude();
    return Quaternion(x / mag, y / mag, z / mag, w / mag);
}

Quaternion Quaternion::Conjugate(){
    return Quaternion(-x, -y, -z, w);
}

Quaternion Quaternion::Sub(Quaternion value){
    return Quaternion(x - value.x, y - value.y, z - value.z, w - value.w);
}

Quaternion Quaternion::Add(Quaternion value){
    return Quaternion(x + value.x, y + value.y, z + value.z, w + value.w);
}

Quaternion Quaternion::Add(float value){
    return Quaternion(x + value, y + value, z + value, w + value);
}

Quaternion Quaternion::Mul(float value){
    return Quaternion(x * value, y * value, z * value, w * value);
}

Quaternion Quaternion::Mul(Quaternion r){
    float nw = w * r.w - x * r.x - y * r.y - z * r.z;
	float nx = x * r.w + w * r.x + y * r.z - z * r.y;
	float ny = y * r.w + w * r.y + z * r.x - x * r.z;
	float nz = z * r.w + w * r.z + x * r.y - y * r.x;

    return Quaternion(nx, ny, nz, nw);
}

Quaternion Quaternion::Mul(Vector3f r){
    float nw = -x * r.x - y * r.y - z * r.z;
	float nx = 	w * r.x + y * r.z - z * r.y;
	float ny = 	w * r.y + z * r.x - x * r.z;
	float nz = 	w * r.z + x * r.y - y * r.x;

    return Quaternion(nx, ny, nz, nw);
}

float Quaternion::Dot(Quaternion r){
    return x * r.x + y * r.y + z * r.z + w * r.w;
}

Matrix4f Quaternion::ToMatrix(){
    Vector3f forward = Vector3f(2.0f * (x * z - w * y), 2.0f * (y * z + w * x), 1.0f - 2.0f * (x * x + y * y));
	Vector3f up = Vector3f(2.0f * (x * y + w * z), 1.0f - 2.0f * (x * x + z * z), 2.0f * (y * z - w * x));
	Vector3f right = Vector3f(1.0f - 2.0f * (y * y + z * z), 2.0f * (x * y - w * z), 2.0f * (x * z + w * y));
		
    return Matrix4f::Rotate(forward, up, right);
}

Quaternion Quaternion::NLerp(Quaternion dest, float lerpFactor, bool shortest){
    Quaternion correctedDest = dest;

	if(shortest && this->Dot(dest) < 0)
		correctedDest = Quaternion(-dest.x, -dest.y, -dest.z, -dest.w);

    return correctedDest.Sub(*this).Mul(lerpFactor).Add(*this).Normalize();
}

Quaternion Quaternion::SLerp(Quaternion dest, float lerpFactor, bool shortest){
    const float EPSILON = 1e3f;

	float c = this->Dot(dest);
	Quaternion correctedDest = dest;

	if(shortest && c < 0){
		c = -c;
		correctedDest = Quaternion(-dest.x, -dest.y, -dest.z, -dest.w);
	}

	if(abs(c) >= 1 - EPSILON)
		return NLerp(correctedDest, lerpFactor, false);

	float s = (float)sqrt(1.0f - c * c);
	float angle = (float)atan2(s, c);
	float invs =  1.0f/s;

	float srcFactor = (float)sin((1.0f - lerpFactor) * angle) * invs;
	float destFactor = (float)sin((lerpFactor) * angle) * invs;

    return this->Mul(srcFactor).Add(correctedDest.Mul(destFactor));
}

Vector3f Quaternion::GetForward(){
    return Vector3f(0, 0, 1).Rotate(*this);
}

Vector3f Quaternion::GetBackward(){
    return Vector3f(0, 0, -1).Rotate(*this);
}

Vector3f Quaternion::GetRight(){
    return Vector3f(1, 0, 0).Rotate(*this);
}

Vector3f Quaternion::GetLeft(){
    return Vector3f(-1, 0, 0).Rotate(*this);
}

Vector3f Quaternion::GetUp(){
    return Vector3f(0, 1, 0).Rotate(*this);
}

Vector3f Quaternion::GetDown(){
    return Vector3f(0, -1, 0).Rotate(*this);
}
