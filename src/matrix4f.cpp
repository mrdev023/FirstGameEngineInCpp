#include "math.h"

Matrix4f::~Matrix4f(){}

Matrix4f::Matrix4f(){
    for(int i = 0;i < 4;i++){
        for(int j = 0;j < 4;j++){
            if(i == j)m[i][j] = 1;
            else m[i][j] = 0;
        }
    }
}

Matrix4f::Matrix4f(const Matrix4f& ma){
    for(int i = 0;i < 4;i++){
        for(int j = 0;j < 4;j++){
            m[i][j] = ma.m[i][j];
        }
    }
}

Matrix4f::Matrix4f(float* matrix){
    for(int i = 0;i < 4;i++){
        for(int j = 0;j < 4;j++){
            m[i][j] = matrix[i*4+j];
        }
    }
}

Matrix4f Matrix4f::Identity(){
    return Matrix4f();
}

void Matrix4f::SetIdentity(){
    for(int i = 0;i < 4;i++){
        for(int j = 0;j < 4;j++){
            if(i == j)m[i][j] = 1;
            else m[i][j] = 0;
        }
    }
}

Matrix4f Matrix4f::Mul(Matrix4f ma){
    Matrix4f result = Matrix4f();
		
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			result.m[x][y] = (m[x][0] * ma.m[0][y]) +
								 (m[x][1] * ma.m[1][y]) +
								 (m[x][2] * ma.m[2][y]) +
								 (m[x][3] * ma.m[3][y]);
		}	
	}
		
    return result;
}

Matrix4f Matrix4f::Translate(Vector3f pos){
    Matrix4f result = Identity();
		
	result.m[0][3] = pos.x;
	result.m[1][3] = pos.y;
	result.m[2][3] = pos.z;
		
    return result;
}

Matrix4f Matrix4f::Translate(float x,float y,float z){
	Matrix4f result = Identity();
		
	result.m[0][3] = x;
	result.m[1][3] = y;
	result.m[2][3] = z;
		
    return result;
}

Matrix4f Matrix4f::Rotate(float x,float y,float z){
    Matrix4f rx = Identity();
	Matrix4f ry = Identity();
	Matrix4f rz = Identity();

	x = toRadians(x);
	y = toRadians(y);
	z = toRadians(z);
		
	float xcos = cos(x);
	float xsin = sin(x);

	float ycos = cos(y);
	float ysin = sin(y);

	float zcos = cos(z);
	float zsin = sin(z);
		
	rx.m[1][1] = xcos;		
	rx.m[1][2] = -xsin;
	rx.m[2][1] = xsin;		
	rx.m[2][2] = xcos;
		
	ry.m[0][0] = ycos;		
	ry.m[0][2] = -ysin;
	ry.m[2][0] = ysin;		
	ry.m[2][2] = ycos;
		
	rz.m[0][0] = zcos;		
	rz.m[0][1] = -zsin;
	rz.m[1][0] = zsin;		
	rz.m[1][1] = zcos;

    return rz.Mul(ry.Mul(rx));
}

Matrix4f Matrix4f::Rotate(Vector3f forward,Vector3f up,Vector3f right){
    Matrix4f result = Identity();
		
	Vector3f f = Vector3f(forward).Normalize();
	Vector3f r = Vector3f(right).Normalize();
	Vector3f u = Vector3f(up).Normalize();
		
	result.m[0][0] = r.x;	
	result.m[0][1] = r.y;	
	result.m[0][2] = r.z;
		
	result.m[1][0] = u.x;
	result.m[1][1] = u.y;	
	result.m[1][2] = u.z;
		
	result.m[2][0] = f.x;
	result.m[2][1] = f.y;	
	result.m[2][2] = f.z;
		
    return result;
}

Matrix4f Matrix4f::Rotate(Vector3f forward,Vector3f up){
	Matrix4f ma = Identity();
		
	Vector3f f = Vector3f(forward).Normalize();
	Vector3f r = Vector3f(up).Normalize();
	r = r.Cross(f);
	Vector3f u = f.Cross(r);
		
	ma.m[0][0] = r.x;	
	ma.m[0][1] = r.y;	
	ma.m[0][2] = r.z;
		
	ma.m[1][0] = u.x;
	ma.m[1][1] = u.y;	
	ma.m[1][2] = u.z;
		
	ma.m[2][0] = f.x;
	ma.m[2][1] = f.y;	
	ma.m[2][2] = f.z;
		
	return ma;
}

Matrix4f Matrix4f::Scale(float x,float y,float z){
    Matrix4f result = Identity();
		
	result.m[0][0] = x;
	result.m[1][1] = y;
	result.m[2][2] = z;
		
    return result;
}

Matrix4f Matrix4f::Scale(Vector3f vec){
    return Scale(vec.x, vec.y, vec.z);
}

Matrix4f Matrix4f::Perspective(float fov, float aspect, float zNear, float zFar){
    Matrix4f result = Identity();

	float FOV = (float) tan(toRadians(fov / 2));
	float dist = zNear - zFar;
		
	result.m[0][0] = 1.0f / (FOV * aspect);
	result.m[1][1] = 1.0f / FOV;

	result.m[2][2] = (-zNear - zFar) / dist;
	result.m[2][3] = 2 * zFar * zNear / dist;

	result.m[3][2] = 1;
	result.m[3][3] = 0;

    return result;
}

Matrix4f Matrix4f::Orthographic(float right, float left, float top, float bottom, float zNear, float zFar){
    Matrix4f ma = Identity();
		
	ma.m[0][0] = 2/(right - left);
	ma.m[0][3] = -(right + left) / (right - left);
		
	ma.m[1][1] = 2/(top - bottom);
	ma.m[1][3] = -(top + bottom) / (top - bottom);
		
	ma.m[2][2] = -2/(zFar - zNear);
	ma.m[2][3] = -(zFar + zNear) / (zFar - zNear);
		
    return ma;
}

Vector3f Matrix4f::Transform(Matrix4f ma,Vector3f v){
    return Vector3f(
        ma.m[0][0] * v.x + ma.m[0][1] * v.y + ma.m[0][2] * v.z + ma.m[0][3],
		ma.m[1][0] * v.x + ma.m[1][1] * v.y + ma.m[1][2] * v.z + ma.m[1][3],
        ma.m[2][0] * v.x + ma.m[2][1] * v.y + ma.m[2][2] * v.z + ma.m[2][3]
    );
}

float* Matrix4f::GetComponents(){
    float* result = new float[16];
	for (int x = 0; x < 4; x++){
		for (int y = 0; y < 4; y++){
			result[x + y * 4] = m[x][y];
		}	
	}
    return result;
}
