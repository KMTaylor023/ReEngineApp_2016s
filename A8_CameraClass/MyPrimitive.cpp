#include "MyPrimitive.h"
MyPrimitive::MyPrimitive() { }
MyPrimitive::MyPrimitive(const MyPrimitive& other) { }
MyPrimitive& MyPrimitive::operator=(const MyPrimitive& other) { return *this; }
MyPrimitive::~MyPrimitive(void) { super::Release(); }
void MyPrimitive::CompileObject(vector3 a_v3Color)
{
	m_uVertexCount = static_cast<int> (m_lVertexPos.size());
	for (uint i = 0; i < m_uVertexCount; i++)
	{
		AddVertexColor(a_v3Color);
	}
	
	CompleteTriangleInfo(true);
	CompileOpenGL3X();

}
//C--D
//|\ |
//| \|
//A--B
//This will make the triang A->B->C and then the triang C->B->D
void MyPrimitive::AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
{
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);

	AddVertexPosition(a_vTopLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopRight);
}

void MyPrimitive::AddTri(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft)
{
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);
}
void MyPrimitive::GeneratePlane(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;

	vector3 pointA(-fValue, -fValue, 0.0f); //0
	vector3 pointB(fValue, -fValue, 0.0f); //1
	vector3 pointC(fValue, fValue, 0.0f); //2
	vector3 pointD(-fValue, fValue, 0.0f); //3

	vector3 pointE(fValue, -fValue, -0.001f); //1
	vector3 pointF(-fValue, -fValue, -0.001f); //0
	vector3 pointG(fValue, fValue, -0.001f); //2
	vector3 pointH(-fValue, fValue, -0.001f); //3

											  //F
	AddQuad(pointA, pointB, pointD, pointC);
	//Double sided
	AddQuad(pointE, pointF, pointG, pointH);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCube(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;
	//3--2
	//|  |
	//0--1
	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	vector3 point4(-fValue, -fValue, -fValue); //4
	vector3 point5(fValue, -fValue, -fValue); //5
	vector3 point6(fValue, fValue, -fValue); //6
	vector3 point7(-fValue, fValue, -fValue); //7

											  //F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	float hheight = a_fHeight / 2;
	std::vector<vector3> point;

	vector3 top = vector3(0.0f,0.0f, hheight);//the tip of the cone
	vector3 bottom = vector3(0.0f, 0.0f, -hheight);//the center of the bottom of the cone
	
	point.push_back(vector3(a_fRadius,0.0f,-hheight));//the first point in the cone base

	float subsize = PI * 2.0 / static_cast<float>(a_nSubdivisions);
	float angle = subsize;
	for (int i = 1; i <= a_nSubdivisions; i++) {
		point.push_back(vector3(cos(angle)*a_fRadius, sin(angle)*a_fRadius, -hheight));

		AddTri(bottom, point[i], point[i - 1]);
		AddTri(point[i - 1], point[i],top);
		angle += subsize;
	}
	
	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	float hheight = a_fHeight/2;

	vector3 top(0.0f,0.0f,hheight); //top center of cylinder
	vector3 bottom(0.0f, 0.0f, -hheight); //bottom center of cylinder

	std::vector<vector3> point;

	point.push_back(vector3(a_fRadius, 0.0f, -hheight));//the first point in the cylinder bottom
	point.push_back(vector3(a_fRadius, 0.0f, hheight));//the first point in the cylinder top 
	

	float subsize = PI * 2.0 / static_cast<float>(a_nSubdivisions);
	float angle = subsize;
	for (int i = 2; i <= a_nSubdivisions*2; i+=2) {
		point.push_back(vector3(cos(angle)*a_fRadius, sin(angle)*a_fRadius, -hheight));
		point.push_back(vector3(cos(angle)*a_fRadius, sin(angle)*a_fRadius, hheight));

		AddQuad(point[i - 2], point[i], point[i - 1], point[i + 1]);

		AddTri(bottom, point[i], point[i - 2]);
		AddTri(top, point[i-1], point[i + 1]);
		angle += subsize;
	}

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	float hheight = a_fHeight / 2;

	std::vector<vector3> point;

	point.push_back(vector3(a_fInnerRadius, 0.0f, -hheight));//the first point in the tube inner bottom
	point.push_back(vector3(a_fInnerRadius, 0.0f, hheight));//the first point in the tube inner top 

	point.push_back(vector3(a_fOuterRadius, 0.0f, -hheight));//the first point in the tube outer bottom
	point.push_back(vector3(a_fOuterRadius, 0.0f, hheight));//the first point in the tube outer top 


	float subsize = PI * 2.0 / static_cast<float>(a_nSubdivisions);
	float angle = subsize;
	for (int i = 4; i <= a_nSubdivisions * 4; i += 4) {
		point.push_back(vector3(cos(angle)*a_fInnerRadius, sin(angle)*a_fInnerRadius, -hheight));
		point.push_back(vector3(cos(angle)*a_fInnerRadius, sin(angle)*a_fInnerRadius, hheight));

		point.push_back(vector3(cos(angle)*a_fOuterRadius, sin(angle)*a_fOuterRadius, -hheight));
		point.push_back(vector3(cos(angle)*a_fOuterRadius, sin(angle)*a_fOuterRadius, hheight));

		AddQuad(point[i], point[i - 4], point[i + 1], point[i - 3]);
		AddQuad(point[i - 2], point[i+2], point[i - 1], point[i + 3]);

		AddQuad(point[i - 1], point[i+3], point[i - 3], point[i + 1]);
		AddQuad(point[i - 4], point[i], point[i - 2], point[i + 2]);
		angle += subsize;
	}

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionsA, int a_nSubdivisionsB, vector3 a_v3Color)
{
	if (a_fOuterRadius <= a_fInnerRadius + 0.1f)
		return;

	if (a_nSubdivisionsA < 3)
		a_nSubdivisionsA = 3;
	if (a_nSubdivisionsA > 25)
		a_nSubdivisionsA = 25;

	if (a_nSubdivisionsB < 3)
		a_nSubdivisionsB = 3;
	if (a_nSubdivisionsB > 25)
		a_nSubdivisionsB = 25;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f;
	//3--2
	//|  |
	//0--1
	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	AddQuad(point0, point1, point3, point2);

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color)
{
	//Sets minimum and maximum of subdivisions
	if (a_nSubdivisions < 1)
	{
		GenerateCube(a_fRadius * 2, a_v3Color);
		return;
	}
	if (a_nSubdivisions > 10)
		a_nSubdivisions = 10;

	Release();
	Init();


	std::vector<vector3> point;

	vector3 top(0.0f, 0.0f, a_fRadius);//top of sphere
	vector3 bottom(0.0f, 0.0f, -a_fRadius);//bottom of sphere

	float h_subs = PI * 2.0f / static_cast<float>(a_nSubdivisions);
	float v_subs = PI / static_cast<float>(a_nSubdivisions);
	float h_angle = 0.0f;
	float v_angle = (PI / 2.0) - v_subs;


	float h_height = 0.0f;
	float v_rad = 0.0f;

	int vdiff = 0;

	for (int v = 0; v < a_nSubdivisions; v++) {
		h_height = sin(v_angle)*a_fRadius;
		v_rad = cos(v_angle)*a_fRadius;



		h_angle = h_subs;

		vdiff = v * a_nSubdivisions;

		point.push_back(vector3(v_rad, 0.0f, h_height));
		for (int h = 1; h <= a_nSubdivisions; h++) {
			point.push_back(vector3(cos(h_angle)*v_rad, sin(h_angle)*v_rad, h_height));

			if (v == 0) {
				AddTri(point[h - 1], point[h], top);
			}
			else {
				AddQuad(point[vdiff + h - 1], point[vdiff + h], point[vdiff - a_nSubdivisions + h - 1], point[vdiff - a_nSubdivisions + h]);

				if (v == a_nSubdivisions - 1) {
					AddTri(bottom, point[vdiff + h], point[vdiff + h - 1]);
				}
			}

			h_angle += h_subs;
		}

		v_angle -= v_subs;
	}

	//Your code ends here
	CompileObject(a_v3Color);
}