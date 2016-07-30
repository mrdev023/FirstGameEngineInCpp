#include "math.h"

Transform::~Transform(){

}

Transform::Transform(){
    this->pos = Vector3f(0,0,0);
	this->rot = Quaternion();
    this->scale = Vector3f(1,1,1);
}

Transform::Transform(Vector3f pos){
    this->pos = pos;
	this->rot = Quaternion();
    this->scale = Vector3f(1,1,1);
}

Transform::Transform(const Transform& transform){
    this->pos = Vector3f(transform.pos);
	this->rot = Quaternion(transform.rot);
    this->scale = Vector3f(1,1,1);
}

Transform::Transform(Vector3f pos,Vector3f scale){
    this->pos = pos;
	this->rot = Quaternion();
    this->scale = scale;
}

Transform::Transform(Vector3f pos,Quaternion rot){
    this->pos = pos;
	this->rot = rot;
    this->scale = Vector3f(1,1,1);
}

Transform::Transform(Vector3f pos,Quaternion rot,Vector3f size){
    this->pos = pos;
	this->rot = rot;
    this->scale = size;
}

Matrix4f Transform::ToMatrix(){
    Matrix4f translationMatrix = Matrix4f::Translate(pos.x, pos.y, pos.z);
	Matrix4f rotationMatrix = rot.ToMatrix();
	Matrix4f scaleMatrix = Matrix4f::Scale(scale.x, scale.y, scale.z);
	Matrix4f parentMatrix = Matrix4f::Identity();
	if (parent != NULL) {
		parentMatrix = parent->ToMatrix();
	}

	Matrix4f transformationMatrix = parentMatrix.Mul(translationMatrix.Mul(rotationMatrix.Mul(scaleMatrix)));
		
    return transformationMatrix;
}

void Transform::Rotate(Vector3f axis,float angle){
    rot = Quaternion(axis, (float) toRadians(angle)).Mul(rot).Normalize();
}

void Transform::SetParent(Transform* parent){
    this->parent = parent;
}

void Transform::Add(Transform transform){
    pos.Add(transform.pos);
	rot.Add(transform.rot);
    scale.Add(transform.scale);
}

Vector3f Transform::GetPosition(){
    if (parent == NULL) {
		return pos;
	}
    return Matrix4f::Transform(parent->ToMatrix(), pos);
}

Quaternion Transform::GetRotation(){
    Quaternion parentRotation = Quaternion();
		
	if (parent != NULL) {
		parentRotation = parent->GetRotation();
	}

    return parentRotation.Mul(rot);
}

void Transform::LookAt(Vector3f source,Vector3f look){
    rot = Quaternion::LookAt(source, look);
}

Vector3f Transform::GetLocalPosition(){
    return this->pos;
}

void Transform::SetLocalPosition(Vector3f pos){
    this->pos = pos;
}

Quaternion Transform::GetLocalRotation(){
    return this->rot;
}

void Transform::SetLocalRotation(Quaternion r){
    this->rot = r;
}

Vector3f Transform::GetLocalScale(){
    return this->scale;
}

void Transform::SetLocalScale(Vector3f scale){
    this->scale = scale;
}

void Transform::Translate(Vector3f axis,float speed){
    pos.Add(axis.Mul(speed));
}

Vector3f Transform::GetForward(){
    return rot.GetForward();
}

Vector3f Transform::GetBackward(){
    return rot.GetBackward();
}

Vector3f Transform::GetLeft(){
    return rot.GetLeft();
}

Vector3f Transform::GetRight(){
    return rot.GetRight();
}

Vector3f Transform::GetUp(){
    return rot.GetUp();
}

Vector3f Transform::GetDown(){
    return rot.GetDown();
}
