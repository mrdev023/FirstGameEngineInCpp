#ifndef MATH_H
#define MATH_H

#include <math.h> 
#include <cstddef>
#include <algorithm>

#define byte char

extern const float PI;
float lerp(float,float,float);
float cLerp(float,float,float);
float sLerp(float,float,float);
float bLerp(float,float,float,float,float,float);
float clamp(float,float,float);
float min(float,float);
float max(float,float);
float toRadians(float);
float toDegrees(float);
int norm(float);
float nearest(float,float,float);

class Vector4f;
class Vector3f;
class Vector2f;
class Matrix4f;
class Quaternion;
class Transform;

class Vector4f{
    public:
    float x;
    float y;
    float z;
    float w;

    ~Vector4f();
    Vector4f(float,float,float,float);
    Vector4f(const Vector4f&);
    Vector4f();
    float Sqrt();
    float Magnitude();
    Vector4f Normalize();
    float Max();
    float Min();
    float SquaredDistance(Vector4f v);
    float Distance(Vector4f v);
    static Vector4f Lerp(Vector4f,Vector4f,float);
    static Vector4f CLerp(Vector4f,Vector4f,float);
    static Vector4f SLerp(Vector4f,Vector4f,float);
    Vector4f Negate();
    Vector4f Add(Vector4f);
    Vector4f Sub(Vector4f);
    Vector4f Div(Vector4f);
    Vector4f Mul(Vector4f);
    Vector4f Add(float,float,float,float);
    Vector4f Sub(float,float,float,float);
    Vector4f Div(float,float,float,float);
    Vector4f Mul(float,float,float,float);
    Vector4f Add(float);
    Vector4f Sub(float);
    Vector4f Div(float);
    Vector4f Mul(float);
    Vector4f Copy();
    bool Equals(Vector4f);
};

class Vector3f{
    public:
    static Vector3f UP,FRONT,RIGHT;
    float x;
    float y;
    float z;

    ~Vector3f();
    Vector3f(float,float,float);
    Vector3f(const Vector3f&);
    Vector3f();
    float Sqrt();
    float Magnitude();
    Vector3f Normalize();
    Vector3f GtNorm(Vector3f);
    Vector3f CheckNormals();
    Vector3f Cross(Vector3f);
    float Dot(Vector3f);
    float Max();
    float Min();
    Vector3f Reflect(Vector3f);
    Vector3f Refract(Vector3f,float);
    static Vector3f Lerp(Vector3f,Vector3f,float);
    static Vector3f CLerp(Vector3f,Vector3f,float);
    static Vector3f CLerp(Vector3f,Vector3f,float,float,float);
    static Vector3f SLerp(Vector3f,Vector3f,float);
    Vector3f Negate();
    Vector3f Add(Vector3f);
    Vector3f Sub(Vector3f);
    Vector3f Div(Vector3f);
    Vector3f Mul(Vector3f);
    Vector3f Add(float,float,float);
    Vector3f Sub(float,float,float);
    Vector3f Div(float,float,float);
    Vector3f Mul(float,float,float);
    Vector3f Add(float);
    Vector3f Sub(float);
    Vector3f Div(float);
    Vector3f Mul(float);
    Vector3f Reo();
    Vector3f Abs();
    Vector3f Rotate(Quaternion);
    Vector3f Copy();
    bool Equals(Vector3f);
};

class Vector2f{
    public:
    static Vector2f UP,RIGHT;
    float x;
    float y;

    ~Vector2f();
    Vector2f(float,float);
    Vector2f(const Vector2f&);
    Vector2f();
    float Sqrt();
    float Magnitude();
    Vector2f Normalize();
    Vector2f Cross(Vector2f);
    float Dot(Vector2f);
    float Max();
    float Min();
    Vector2f Reflect(Vector2f);
    Vector2f Refract(Vector2f,float);
    static Vector2f Lerp(Vector3f,Vector3f,float);
    static Vector2f CLerp(Vector3f,Vector3f,float);
    static Vector2f SLerp(Vector3f,Vector3f,float);
    Vector2f Negate();
    Vector2f Add(Vector2f);
    Vector2f Sub(Vector2f);
    Vector2f Div(Vector2f);
    Vector2f Mul(Vector2f);
    Vector2f Add(float,float);
    Vector2f Sub(float,float);
    Vector2f Div(float,float);
    Vector2f Mul(float,float);
    Vector2f Add(float);
    Vector2f Sub(float);
    Vector2f Div(float);
    Vector2f Mul(float);
    Vector2f Copy();
    bool Equals(Vector2f);
};

class Matrix4f{
    public:
    float m[4][4];

    ~Matrix4f();
    Matrix4f();
    Matrix4f(const Matrix4f&);
    Matrix4f(float*);
    static Matrix4f Identity();
    void SetIdentity();
    Matrix4f Mul(Matrix4f);
    static Matrix4f Translate(Vector3f);
    static Matrix4f Translate(float,float,float);
    static Matrix4f Rotate(float,float,float);
    static Matrix4f Rotate(Vector3f,Vector3f,Vector3f);
    static Matrix4f Rotate(Vector3f,Vector3f);
    static Matrix4f Scale(float,float,float);
    static Matrix4f Scale(Vector3f);
    static Matrix4f Perspective(float,float,float,float);
    static Matrix4f Orthographic(float,float,float,float,float,float);
    static Vector3f Transform(Matrix4f,Vector3f);
    float* GetComponents();
};

class Quaternion{
    public:
    float x,y,z,w;

    ~Quaternion();
    Quaternion();
    Quaternion(const Quaternion&);
    Quaternion(float,float,float,float);
    Quaternion(Vector3f,float);
    Quaternion(const Quaternion&,Vector3f,float);
    Quaternion(Vector3f);
    Quaternion(Matrix4f);
    static Quaternion Euler(float,float,float);
    static Quaternion Euler(Vector3f);
    static Quaternion LookAt(Vector3f,Vector3f);
    static Quaternion CreateFromAxisAngle(Vector3f,float);
    float Magnitude();
    Quaternion Normalize();
    Quaternion Conjugate();
    Quaternion Sub(Quaternion);
    Quaternion Add(Quaternion);
    Quaternion Add(float);
    Quaternion Mul(float);
    Quaternion Mul(Quaternion);
    Quaternion Mul(Vector3f);
    float Dot(Quaternion);
    Matrix4f ToMatrix();
    Quaternion NLerp(Quaternion,float,bool);
    Quaternion SLerp(Quaternion,float,bool);
    Vector3f EulerAngles();
    Vector3f GetForward();
    Vector3f GetBackward();
    Vector3f GetRight();
    Vector3f GetLeft();
    Vector3f GetUp();
    Vector3f GetDown();
};

class Transform{
    public:
    Vector3f pos;
    Quaternion rot;
    Vector3f scale;
    Transform *parent;

    ~Transform();
    Transform();
    Transform(Vector3f);
    Transform(const Transform&);
    Transform(Vector3f,Vector3f);
    Transform(Vector3f,Quaternion);
    Transform(Vector3f,Quaternion,Vector3f);
    Matrix4f ToMatrix();
    void Rotate(Vector3f,float);
    void SetParent(Transform*);
    void Add(Transform);
    Vector3f GetPosition();
    Quaternion GetRotation();
    void LookAt(Vector3f,Vector3f);
    Vector3f GetLocalPosition();
    void SetLocalPosition(Vector3f);
    Quaternion GetLocalRotation();
    void SetLocalRotation(Quaternion);
    Vector3f GetLocalScale();
    void SetLocalScale(Vector3f);
    void Translate(Vector3f,float);
    Vector3f GetForward();
    Vector3f GetBackward();
    Vector3f GetLeft();
    Vector3f GetRight();
    Vector3f GetUp();
    Vector3f GetDown();
};

#endif