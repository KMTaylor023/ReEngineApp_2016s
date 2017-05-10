#pragma once
#include "RE\ReEng.h"

class MyBoundingObjectClass
{
private:
	float m_fRadius = 0.0f; //radius of the sphere
	vector3 m_v3CenterLocal = vector3(0.0f); //center of the sphere in local space
	vector3 m_v3CenterGlobal = vector3(0.0f); //center of the sphere in global space
	matrix4 m_m4ToWorld = IDENTITY_M4; //matrix that takes you from local to global space
	MeshManagerSingleton* m_pMeshMngr = nullptr; //for drawing the sphere
	bool m_bColliding = false;

	vector3 boxCorners[8];

	vector3 m_v3Color = REGREEN;

	vector3 m_v3Max;
	vector3 m_v3Min;
	vector3 m_v3Size;

	vector3 m_sphereSize;

	vector3 m_v3MaxG;
	vector3 m_v3MinG;
	vector3 m_v3SizeG;

	vector3 m_v3MinGAABB;
	vector3 m_v3MaxGAABB;

	bool m_bsvis = true;
	bool m_bbvis = true;
	bool m_rebbvis = true;

public:

	MyBoundingObjectClass(std::vector<vector3> vertexList);

	void SetColliding(bool input);
	void SetCenterLocal(vector3 input);
	void SetCenterGlobal(vector3 input);
	void SetRadius(float input);
	void SetModelMatrix(matrix4 a_m4ToWorld);
	void SetColor(vector3 color);
	void SetBoundingSphereVis(bool vis);
	void SetBoundingBoxVis(bool vis);
	void SetReAlignedBoundingBoxVis(bool vis);

	bool GetColliding(void);
	vector3 GetCenterLocal(void);
	vector3 GetCenterGlobal(void);
	matrix4 GetModelMatrix(void);
	float GetRadius(void);
	vector3 GetMin();
	vector3 GetMax();
	
	void Render();
	bool IsColliding(MyBoundingObjectClass* a_other);
	bool SpherePreCheck(MyBoundingObjectClass* a_other);

	bool SATCheck(MyBoundingObjectClass* a_other);
};

