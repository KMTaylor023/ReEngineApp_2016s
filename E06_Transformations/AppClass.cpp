#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("E06 - 3D Transformations");
	m_v4ClearColor = vector4(0.0f, 0.0f, 0.0f, 0.0f);
}

void AppClass::InitVariables(void)
{
	//Sets the camera
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 15.0f), vector3(0.0f, 0.0f, 0.0f), REAXISY);

	m_pCube = new PrimitiveClass();
	m_pCone = new PrimitiveClass();
	m_pCylinder = new PrimitiveClass();
	m_pTube = new PrimitiveClass();
	m_pSphere = new PrimitiveClass();
	m_pTorus = new PrimitiveClass();

	//Initializing the primitives

	m_pCube->GenerateCube(1, RERED);
	m_pCone->GenerateCone(0.5f, 0.5f, 10, REGREEN);
	m_pCylinder->GenerateCylinder(0.5f, 0.5f, 10, REBLUE);
	m_pTube->GenerateTube(0.5f, 0.25f, 0.5f, 10, REBROWN);
	m_pSphere->GenerateSphere(0.5f, 5, REWHITE);
	m_pTorus->GenerateTorus(0.5f, 0.25f, 10, 10, REYELLOW);
}

void AppClass::Update(void)
{
	m_m4Cube = glm::translate(IDENTITY_M4, vector3(2.0f, 0.0f, 0.0f));

	m_m4Cone = glm::translate(IDENTITY_M4, vector3(0.0f, 2.0f, 0.0f));
	m_m4Cone = glm::scale(m_m4Cone, vector3(2.0f, 2.0f, 2.0f));

	m_m4Cylinder = glm::translate(IDENTITY_M4, vector3(-2.0f, 0.0f, 0.0f));
	m_m4Cylinder = glm::scale(m_m4Cylinder, vector3(2.0f, 2.0f, 2.0f));

	m_m4Tube = glm::translate(IDENTITY_M4, vector3(0.0f, -2.0f, 0.0f));
	m_m4Tube = glm::scale(m_m4Tube, vector3(2.0f, 2.0f, 2.0f));

	m_m4Torus = glm::translate(IDENTITY_M4, vector3(0.0f, 0.0f, 0.0f));
	m_m4Torus = glm::scale(m_m4Torus, vector3(2.0f, 2.0f, 2.0f));



	//This matrices will just place the objects int the right spots
	m_m4Sphere = glm::translate(IDENTITY_M4, vector3(2.5f, 2.5f, 0.0f));

	//This matrices will scale them to the right size
	m_m4Sphere = glm::scale(m_m4Sphere, vector3(2.0f, 2.0f, 2.0f));

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//Print info on the screen
	m_pMeshMngr->PrintLine("");//Add a line on top
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	
	//Matrices from the camera
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();

	//Renders the meshes using the specified position given by the matrix and in the specified color
	m_pSphere->Render(m4Projection, m4View, m_m4Sphere);
	m_pCone->Render(m4Projection, m4View, m_m4Cone);
	m_pCylinder->Render(m4Projection, m4View, m_m4Cylinder);
	m_pTube->Render(m4Projection, m4View, m_m4Tube);
	m_pCube->Render(m4Projection, m4View, m_m4Cube);
	m_pTorus->Render(m4Projection, m4View, m_m4Torus);
	
	//Render the grid based on the camera's mode:
	m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	SafeDelete(m_pCube);
	SafeDelete(m_pCone);
	SafeDelete(m_pCylinder);
	SafeDelete(m_pTube);
	SafeDelete(m_pSphere);
	SafeDelete(m_pTorus);

	super::Release(); //release the memory of the inherited fields
}