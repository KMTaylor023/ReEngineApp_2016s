#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	//Using Base InitWindow method
	super::InitWindow("E12 - Instance Rendering");
	m_v4ClearColor = vector4(REBLACK, 1.0f);
}

void AppClass::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 15.0f), vector3(0.0f, 0.0f, 0.0f), REAXISY);

	m_pMesh = new MyMesh();
	
	//Creating the Mesh points
	//return;

	m_fMatrixArray = new float[m_nObjects * 16];

	int numberIterations = 3;
	int m_nObjects = pow(3, numberIterations);
	int numberRows = pow(2, numberIterations);


	float angle = glm::radians(90.0f);
	float size = (numberIterations == 0) ? 2.0f : 1.5f/numberIterations;
	for (int i = 0; i < 3; i++) {
		m_pMesh->AddVertexPosition(vector3(cos(angle) * size, sin(angle) * size, 0.0f));
		angle += glm::radians(120.0f);
	}

	m_pMesh->AddVertexColor(REGREEN);
	m_pMesh->AddVertexColor(RERED);
	m_pMesh->AddVertexColor(REBLUE);

	//Compiling the mesh
	m_pMesh->CompileOpenGL3X();

	float yStart = 5.0f;
	float xStart = 0.0f;
	float yPos = yStart;
	float xPos = xStart;
	
	float xDist = size / 2.0f * sqrt(3.0f);
	float yDist = 1.5 * size;

	int cols = 1;
	int prev = 1;
	int tris = 0;
	for (int i = 0; i < numberRows; i++) {

		xPos = xStart;
		yPos -= yDist;

		xStart -= xDist;

		prev = 1;

		//the first thing in the row is always a triangle
		const float* m4MVP = glm::value_ptr(
			glm::translate(vector3(xPos, yPos, 0.0f))
		);
		memcpy(&m_fMatrixArray[tris * 16], m4MVP, 16 * sizeof(float));

		tris++;

		for (int j = 1; j < cols; j++) {
			int cur = (int)(prev * ((float)(i + 1 - j)) / ((float)j));

			xPos += 2*xDist;

			if ( cur % 2 == 1) {
				printf(" " + ((int)(prev * ((float)(i + 1 - j)) / ((float)j))));
				const float* m4MVP = glm::value_ptr(
					glm::translate(vector3(xPos, yPos, 0.0f))
				);
				memcpy(&m_fMatrixArray[tris * 16], m4MVP, 16 * sizeof(float));
				tris++;
				
			}

			prev = cur;
		}
		cols++;
	}


}

void AppClass::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->UpdateTime();

	//Is the arcball active?
	if (m_bArcBall == true)
		ArcBall();

	//Is the first person camera active?
	if (m_bFPC == true)
		CameraRotation();

	//Calculate Camera
	m_pCameraMngr->CalculateView();

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	printf("FPS: %d            \r", nFPS);//print the Frames per Second
										  //Print info on the screen
	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	ClearScreen();
	
	//Matrices from the camera
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();

	m_pMesh->RenderList(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), m_fMatrixArray, m_nObjects);//Rendering nObjects

	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	SafeDelete(m_fMatrixArray);
	if (m_pMesh != nullptr)
	{
		delete m_pMesh;
		m_pMesh = nullptr;
	}
	super::Release();
}