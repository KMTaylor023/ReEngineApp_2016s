#include "A8CameraClass.h"

A8CameraClass::A8CameraClass() {
	k_v3Position = vector3(0.0f);
	k_v3Target = vector3(0.0f, 0.0f,-1.0f);
	k_v3Up = vector3(0.0f,1.0f,0.0f);
	k_v3Right = vector3(1.0f,0.0f,0.0f);
	k_v3Front = vector3(0.0f, 0.0f, -1.0f);

	k_v3FrontStart = k_v3Front;
	k_v3RightStart = k_v3Right;
	k_v3UpStart = k_v3Up;


	k_qOrientation = glm::quat();
}

matrix4 k_m4Ortho = glm::ortho(-10.80f, 10.80f, -7.68f, 7.68f, 0.01f, 1000.0f);
matrix4 k_m4Persp = glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 1000.0f);

matrix4 A8CameraClass::GetView(void){
	return  glm::lookAt(k_v3Position, k_v3Position + k_v3Front, k_v3Up);
}

matrix4 A8CameraClass::GetProjection(bool bOrtographic){
	if (bOrtographic) {
		return k_m4Ortho;
	}

	return k_m4Persp;
}

void A8CameraClass::SetPosition(vector3 v3Position) {
	k_v3Position = v3Position;
}

void A8CameraClass::SetTarget(vector3 v3Target){
	k_v3Target = v3Target;
}

void A8CameraClass::SetUp(vector3 v3Up){
	k_v3Up = glm::normalize(v3Up);
}

void A8CameraClass::MoveForward(float fIncrement){
	k_v3Position += fIncrement*k_v3Front;
}

void A8CameraClass::MoveSideways(float fIncrement){
	k_v3Position += fIncrement*k_v3Right;
}

void A8CameraClass::MoveVertical(float fIncrement){
	k_v3Position += fIncrement*k_v3Up;
}

static vector3 m_v3XRot = vector3(1.0f, 0.0f, 0.0f);
static vector3 m_v3YRot = vector3(0.0f, 1.0f, 0.0f);
static vector3 m_v3ZRot = vector3(0.0f, 0.0f, 1.0f);

void A8CameraClass::ChangePitch(float fIncrement){
	k_qOrientation = glm::rotate(k_qOrientation, fIncrement, m_v3XRot);
	UpdateDirectionVectorsFromQuat();
}

void A8CameraClass::ChangeRoll(float fIncrement){
	k_qOrientation = glm::rotate(k_qOrientation, fIncrement, m_v3ZRot);
	UpdateDirectionVectorsFromQuat();
}

void A8CameraClass::ChangeYaw(float fIncrement){
	k_qOrientation = glm::rotate(k_qOrientation, fIncrement, m_v3YRot);
	UpdateDirectionVectorsFromQuat();
}

void A8CameraClass::UpdateDirectionVectorsFromQuat(void) {
	k_v3Right = vector3(vector4(k_v3RightStart, 1.0f) *  glm::mat4_cast(k_qOrientation));
	k_v3Front = vector3(vector4(k_v3FrontStart,1.0f) *  glm::mat4_cast(k_qOrientation));
	k_v3Up = vector3(vector4(k_v3UpStart, 1.0f) *  glm::mat4_cast(k_qOrientation));
}

A8CameraClass::~A8CameraClass() {
	//clean up, wooooooooooo
}