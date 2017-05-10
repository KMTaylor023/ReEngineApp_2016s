#include "MyBoundingObjectClass.h"


MyBoundingObjectClass::MyBoundingObjectClass(std::vector<vector3> vertexList)
{
	m_bColliding = false;
	m_fRadius = 0.0f;
	m_v3CenterGlobal = vector3(0.0f);

	if (vertexList.size() < 1)
		return;

	m_v3Min = vertexList[0];
	m_v3Max = vertexList[0];

	for (int i = 1; i < vertexList.size(); i++)
	{
		if (m_v3Min.x > vertexList[i].x)
		{
			m_v3Min.x = vertexList[i].x;
		}
		else if (m_v3Max.x < vertexList[i].x)
		{
			m_v3Max.x = vertexList[i].x;
		}

		if (m_v3Min.y > vertexList[i].y)
		{
			m_v3Min.y = vertexList[i].y;
		}
		else if (m_v3Max.y < vertexList[i].y)
		{
			m_v3Max.y = vertexList[i].y;
		}

		if (m_v3Min.z > vertexList[i].z)
		{
			m_v3Min.z = vertexList[i].z;
		}
		else if (m_v3Max.z < vertexList[i].z)
		{
			m_v3Max.z = vertexList[i].z;
		}
	}

	m_v3CenterLocal = m_v3CenterGlobal = (m_v3Max + m_v3Min) / 2.0f;
	m_fRadius = glm::distance(m_v3CenterGlobal, m_v3Max);
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
	m_v3Size = m_v3Max - m_v3Min;
	m_sphereSize = vector3(2.0f * m_fRadius);

	m_v3MinG = m_v3Min;
	m_v3MaxG = m_v3Max;

	m_v3MaxGAABB = m_v3Max;
	m_v3MinGAABB = m_v3Min;

	m_v3SizeG = m_v3Size;

	vector3 newPoints[8] = { vector3(m_v3Min.x,m_v3Min.y,m_v3Max.z),
		vector3(m_v3Min.x,m_v3Max.y,m_v3Max.z),
		vector3(m_v3Max.x,m_v3Min.y,m_v3Max.z),
		vector3(m_v3Max.x,m_v3Max.y,m_v3Min.z),
		vector3(m_v3Min.x,m_v3Max.y,m_v3Min.z),
		vector3(m_v3Max.x,m_v3Min.y,m_v3Min.z)
		, m_v3MinG , m_v3MaxG };

	for (int i = 0; i < 8; i++) {
		boxCorners[i] = newPoints[i];
	}

}

void MyBoundingObjectClass::Render()
{
	vector3 tempColor = m_v3Color;

	if (m_bsvis)
	{
		m_pMeshMngr->AddSphereToRenderList(
			glm::translate(m_v3CenterGlobal) *
			glm::scale(m_sphereSize),
			tempColor, WIRE);
	}

	if (m_rebbvis)
	{
		m_pMeshMngr->AddCubeToRenderList(
			glm::translate(m_v3CenterGlobal) *
			glm::scale(m_v3SizeG),
			tempColor, WIRE);
	}

	if (m_bbvis)
	{
		m_pMeshMngr->AddCubeToRenderList(
			m_m4ToWorld *
			glm::translate(m_v3CenterLocal) *
			glm::scale(m_v3Size),
			tempColor, WIRE);
	}
}

void MyBoundingObjectClass::SetModelMatrix(matrix4 a_m4ToWorld)
{
	if (m_m4ToWorld == a_m4ToWorld)
		return;

	m_m4ToWorld = a_m4ToWorld;
	m_v3CenterGlobal = vector3(m_m4ToWorld * vector4(m_v3CenterLocal, 1.0f));

	m_v3MinG = vector3(m_m4ToWorld * vector4(m_v3Min, 1.0f));
	m_v3MaxG = vector3(m_m4ToWorld * vector4(m_v3Max, 1.0f));

	vector3 newPoints[8] = { vector3(m_m4ToWorld * vector4(m_v3Min.x,m_v3Min.y,m_v3Max.z, 1.0f)),
		vector3(m_m4ToWorld * vector4(m_v3Min.x,m_v3Max.y,m_v3Max.z, 1.0f)),
		vector3(m_m4ToWorld * vector4(m_v3Max.x,m_v3Min.y,m_v3Max.z, 1.0f)),
		vector3(m_m4ToWorld * vector4(m_v3Max.x,m_v3Max.y,m_v3Min.z, 1.0f)),
		vector3(m_m4ToWorld * vector4(m_v3Min.x,m_v3Max.y,m_v3Min.z, 1.0f)),
		vector3(m_m4ToWorld * vector4(m_v3Max.x,m_v3Min.y,m_v3Min.z, 1.0f))
		, m_v3MinG , m_v3MaxG };

	for (int i = 0; i < 8; i++) {
		boxCorners[i] = newPoints[i];
	}

	m_v3MinGAABB = newPoints[0];
	m_v3MaxGAABB = newPoints[0];

	for (int i = 0; i < 8; i++) {
		if (m_v3MinGAABB.x > newPoints[i].x)
		{
			m_v3MinGAABB.x = newPoints[i].x;
		}
		else if (m_v3MaxGAABB.x < newPoints[i].x)
		{
			m_v3MaxGAABB.x = newPoints[i].x;
		}

		if (m_v3MinGAABB.y > newPoints[i].y)
		{
			m_v3MinGAABB.y = newPoints[i].y;
		}
		else if (m_v3MaxGAABB.y < newPoints[i].y)
		{
			m_v3MaxGAABB.y = newPoints[i].y;
		}

		if (m_v3MinGAABB.z > newPoints[i].z)
		{
			m_v3MinGAABB.z = newPoints[i].z;
		}
		else if (m_v3MaxGAABB.z < newPoints[i].z)
		{
			m_v3MaxGAABB.z = newPoints[i].z;
		}
	}

	m_v3SizeG = m_v3MaxGAABB - m_v3MinGAABB;
	m_fRadius = glm::distance(m_v3CenterGlobal, m_v3MaxGAABB);
	m_sphereSize = vector3(2.0f * m_fRadius);
}

bool MyBoundingObjectClass::IsColliding(MyBoundingObjectClass * a_other)
{
	if (SpherePreCheck(a_other))
	{
		if (this->m_v3MaxGAABB.x < a_other->m_v3MinGAABB.x)
			return false;
		if (this->m_v3MinGAABB.x > a_other->m_v3MaxGAABB.x)
			return false;

		if (this->m_v3MaxGAABB.y < a_other->m_v3MinGAABB.y)
			return false;
		if (this->m_v3MinGAABB.y > a_other->m_v3MaxGAABB.y)
			return false;

		if (this->m_v3MaxGAABB.z < a_other->m_v3MinGAABB.z)
			return false;
		if (this->m_v3MinGAABB.z > a_other->m_v3MaxGAABB.z)
			return false;

		return SATCheck(a_other);
	}

	return false;
}

bool MyBoundingObjectClass::SpherePreCheck(MyBoundingObjectClass * a_other)
{
	float dist = glm::distance(m_v3CenterGlobal, a_other->m_v3CenterGlobal);
	return dist < (m_fRadius + a_other->m_fRadius);
}

bool MyBoundingObjectClass::SATCheck(MyBoundingObjectClass * a_other)
{

	vector3 centers = m_v3CenterGlobal - a_other->m_v3CenterGlobal;

	//creates the first few axis to check, the normals to the faces of each bounding box
	vector3 axis[15] = { glm::normalize(boxCorners[7] - boxCorners[3]),
		glm::normalize(boxCorners[7] - boxCorners[2]),
		glm::normalize(boxCorners[7] - boxCorners[1]),
		glm::normalize(a_other->boxCorners[7] - a_other->boxCorners[3]),
		glm::normalize(a_other->boxCorners[7] - a_other->boxCorners[2]),
		glm::normalize(a_other->boxCorners[7] - a_other->boxCorners[1]) };

	//crosses each normal with each other normal to get the remaining axis to check
	int pos = 6;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			axis[pos] = glm::cross(axis[i], axis[3 + j]);
			pos++;
		}
	}



	//check for each axis

	float aMax = 0.0f;
	float bMax = 0.0f;

	float centerDist = 0.0f;
	for (int ax = 0; ax < 15; ax++) {

		aMax = 0.0f;
		bMax = 0.0F;
		centerDist = glm::abs(glm::dot(axis[ax], centers));
		for (int i = 0; i < 8; i++) {
			aMax = glm::max(aMax, glm::abs(glm::dot(axis[ax], (boxCorners[i] - m_v3CenterGlobal))));
			bMax = glm::max(bMax, glm::abs(glm::dot(axis[ax], a_other->boxCorners[i] - a_other->m_v3CenterGlobal)));
		}


		if (aMax + bMax < centerDist) {
			return false;
		}


	}

	return true;

}

void MyBoundingObjectClass::SetColor(vector3 color) { m_v3Color = color; }

void MyBoundingObjectClass::SetBoundingSphereVis(bool vis) { m_bsvis = vis; };
void MyBoundingObjectClass::SetBoundingBoxVis(bool vis) { m_bbvis = vis; };
void MyBoundingObjectClass::SetReAlignedBoundingBoxVis(bool vis) { m_rebbvis = vis; };
void MyBoundingObjectClass::SetColliding(bool input) { m_bColliding = input; }
void MyBoundingObjectClass::SetCenterLocal(vector3 input) { m_v3CenterLocal = input; }
void MyBoundingObjectClass::SetCenterGlobal(vector3 input) { m_v3CenterGlobal = input; }
void MyBoundingObjectClass::SetRadius(float input) { m_fRadius = input; }
bool MyBoundingObjectClass::GetColliding(void) { return m_bColliding; }
vector3 MyBoundingObjectClass::GetCenterLocal(void) { return m_v3CenterLocal; }
vector3 MyBoundingObjectClass::GetCenterGlobal(void) { return m_v3CenterGlobal; }
float MyBoundingObjectClass::GetRadius(void) { return m_fRadius; }
vector3 MyBoundingObjectClass::GetMin() { return m_v3MinGAABB; }
vector3 MyBoundingObjectClass::GetMax() { return m_v3MaxGAABB; }
matrix4 MyBoundingObjectClass::GetModelMatrix(void) { return m_m4ToWorld; }