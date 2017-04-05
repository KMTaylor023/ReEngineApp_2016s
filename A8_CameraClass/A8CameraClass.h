#pragma once

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>

class A8CameraClass
{
public:
	A8CameraClass();

	/*
	USAGE: ---
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	matrix4 GetView(void);

	/*
	USAGE: ---
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	matrix4 GetProjection(bool bOrtographic);

	/*
	USAGE: ---
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void SetPosition(vector3 v3Position);

	/*
	USAGE: ---
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void SetTarget(vector3 v3Target);

	/*
	USAGE: ---
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void SetUp(vector3 v3Up);

	/*
	USAGE: ---
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void MoveForward(float fIncrement);

	/*
	USAGE: ---
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void MoveSideways(float fIncrement);

	/*
	USAGE: ---
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void MoveVertical(float fIncrement);

	/*
	USAGE: ---
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ChangePitch(float fIncrement);

	/*
	USAGE: ---
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ChangeRoll(float fIncrement);

	/*
	USAGE: ---
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ChangeYaw(float fIncrement);

	~A8CameraClass();

private:
	vector3 k_v3Position;
	vector3 k_v3Target;
	vector3 k_v3Up;
	vector3 k_v3Right;
};