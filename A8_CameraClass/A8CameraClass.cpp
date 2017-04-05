#include "A8CameraClass.h"

A8CameraClass::A8CameraClass() {
	k_v3Position = vector3(0.0f);
	k_v3Target = vector3(0.0f);
	k_v3Up = vector3(0.0f,1.0f,0.0f);
	k_v3Right = vector3(0.0f,0.0f,1.0f);
}


matrix4 A8CameraClass::GetView(void){
	return  glm::lookAt(k_v3Position, k_v3Target, k_v3Up);
}

matrix4 A8CameraClass::GetProjection(bool bOrtographic){
	if (bOrtographic) {
		return glm::ortho(-10.80f, 10.80f, -7.68f, 7.68f, 0.01f, 1000.0f);
	}

	return glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 1000.0f);
}

void A8CameraClass::SetPosition(vector3 v3Position) {
	k_v3Position = glm::normalize(v3Position);
}

void A8CameraClass::SetTarget(vector3 v3Target){
	k_v3Target = glm::normalize(v3Target);
}

void A8CameraClass::SetUp(vector3 v3Up){
	k_v3Up = glm::normalize(v3Up);
}

void A8CameraClass::MoveForward(float fIncrement){
	k_v3Position += fIncrement*(glm::dot(k_v3Up, k_v3Right));
}

void A8CameraClass::MoveSideways(float fIncrement){
	k_v3Position += fIncrement*k_v3Right;
}

void A8CameraClass::MoveVertical(float fIncrement){
	k_v3Position += fIncrement*k_v3Up;
}

void A8CameraClass::ChangePitch(float fIncrement){
	//glm::rotate(k_v3Right,fIncrement,k_v)
}

void A8CameraClass::ChangeRoll(float fIncrement){}

void A8CameraClass::ChangeYaw(float fIncrement){}

A8CameraClass::~A8CameraClass() {

}