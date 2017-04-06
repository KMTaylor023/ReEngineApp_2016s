#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Sandbox"); // Window Name

								  // Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
								  //if this line is in Init Application it will depend on the .cfg file, if it
								  //is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
	m_pSystem->SetWindowResolution(RESOLUTIONS::C_1280x720_16x9_HD);
	//m_pSystem->SetWindowFullscreen(); //Sets the window to be fullscreen
	//m_pSystem->SetWindowBorderless(true); //Sets the window to not have borders
}

void AppClass::InitVariables(void)
{


	cube1 = new MyPrimitive();
	cube2 = new MyPrimitive();
	cube3 = new MyPrimitive();

	sphere = new MyPrimitive();
	cone = new MyPrimitive();
	cylinder = new MyPrimitive();

	cube1->GenerateCube(1.0f, RERED);
	cube2->GenerateCube(1.0f, RERED);
	cube3->GenerateCube(1.0f, RERED);

	k_m4Cube1 = glm::translate(vector3(2.0f));
	k_m4Cube2 = glm::translate(vector3(-3.0f));
	k_m4Cube3 = glm::translate(vector3(0.0f));


	a8Camera = new A8CameraClass();
	//Reset the selection to -1, -1
	m_selection = std::pair<int, int>(-1, -1);
	//Set the camera position
	
	m_pCameraMngr->SetPositionTargetAndView(
		vector3(0.0f, 2.5f, 15.0f),//Camera position
		vector3(0.0f, 2.5f, 0.0f),//What Im looking at
		REAXISY);//What is up

	a8Camera->SetPosition(vector3(0.0f, 2.5f, 15.0f));
	a8Camera->SetTarget(vector3(0.0f, 2.5f, 0.0f));
	a8Camera->SetUp(REAXISY);


}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	/*
	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	//Call the arcball method
	ArcBall();

	//Set the model matrix for the first model to be the arcball
	m_pMeshMngr->SetModelMatrix(ToMatrix4(m_qArcBall), 0);

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddSkyboxToRenderList();
	m_pMeshMngr->AddInstanceToRenderList("ALL");
	*/


	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	//printf("FPS: %d            \r", nFPS);//print the Frames per Second
	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);

	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	//Render the grid based on the camera's mode:
	//m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());

	cube1->Render(a8Camera->GetProjection(false), a8Camera->GetView(), k_m4Cube1);
	cube2->Render(a8Camera->GetProjection(false), a8Camera->GetView(), k_m4Cube2);
	cube3->Render(a8Camera->GetProjection(false), a8Camera->GetView(), k_m4Cube3);

	sphere->Render(a8Camera->GetProjection(false), a8Camera->GetView(), k_m4Sphere);
	cone->Render(a8Camera->GetProjection(false), a8Camera->GetView(), k_m4Cone);
	cylinder->Render(a8Camera->GetProjection(false), a8Camera->GetView(), k_m4Cylinder);



	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
	delete cube1;
	delete cube2;
	delete cube3;

}