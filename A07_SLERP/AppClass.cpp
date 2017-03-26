#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("SLERP - YOUR USER NAME GOES HERE"); // Window Name

	//Setting the color to black
	m_v4ClearColor = vector4(0.0f);
}

void AppClass::InitVariables(void)
{
	//Setting the position in which the camera is looking and its interest point
	m_pCameraMngr->SetPositionTargetAndView(vector3(12.12f, 28.52f, 11.34f), ZERO_V3, REAXISY);

	//Setting the color to black
	m_v4ClearColor = vector4(0.0f);

	//Loading the models
	m_pMeshMngr->LoadModel("Planets\\00_Sun.obj", "Sun");
	m_pMeshMngr->LoadModel("Planets\\03_Earth.obj", "Earth");
	m_pMeshMngr->LoadModel("Planets\\03A_Moon.obj", "Moon");

	//Setting the days duration
	m_fDay = 1.0f;
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	//Getting the time between calls
	double fCallTime = m_pSystem->LapClock();
	//Counting the cumulative time
	static double fRunTime = 0.0f;
	fRunTime += fCallTime;

	//Earth Orbit
	static double fEarthHalfOrbTime = 182.5f * m_fDay; //Earths orbit around the sun lasts 365 days / half the time for 2 stops
	static float fEarthHalfRevTime = 0.5f * m_fDay; // Move for Half a day
	static float fMoonHalfOrbTime = 14.0f * m_fDay; //Moon's orbit is 28 earth days, so half the time for half a route

	//the current time of the revolution, used for the lerp percentage
	static double earthRevTime = 0.0f;
	static double earthOrbitTime = 0.0f;
	static double moonOrbitTime = 0.0f;
	

	earthRevTime += fCallTime;
	earthOrbitTime += fCallTime;
	moonOrbitTime += fCallTime;



	//the quations used for the slerp
	static glm::quat m_qStart = glm::quat(vector3(0.0f));
	static glm::quat m_qEnd = glm::quat(vector3(0.0f,glm::radians(359.5f),0.0f));



	//the matrices for the earth and moon and sun basic transformations
	static matrix4 m_m4EarthScale = glm::scale(vector3(0.524f));
	static matrix4 m_m4EarthTranslate = glm::translate(11.0f, 0.0f, 0.0f);

	static matrix4 m_m4MoonScale = glm::scale(m_m4EarthScale,vector3(0.27f));
	static matrix4 m_m4MoonTranslate = glm::translate(2.0f, 0.0f, 0.0f);

	static matrix4 m_m4SunScale = glm::scale(vector3(5.936f));


	//a float for the percentage of slerp, for some reason the mix method doesn't like doubles
	float percentRev = earthRevTime / ( 2 * fEarthHalfRevTime);
	float percentOrb = earthOrbitTime / (2 * fEarthHalfOrbTime);
	float percentMoonOrb = moonOrbitTime / (2 * fMoonHalfOrbTime);


	//the three rotation matrices, created from quat slerp with mix method
	matrix4 m_m4EarthRevolutionRotation = glm::mat4_cast(glm::mix(m_qStart, m_qEnd, percentRev));
	matrix4 m_m4EarthOrbitRotation = glm::mat4_cast(glm::mix(m_qStart, m_qEnd, percentOrb));

	matrix4 m_m4MoonOrbitRotation = glm::mat4_cast(glm::mix(m_qStart, m_qEnd, percentMoonOrb));

	//Setting the matrices
	m_pMeshMngr->SetModelMatrix(m_m4SunScale, "Sun");
	m_pMeshMngr->SetModelMatrix(m_m4EarthOrbitRotation * m_m4EarthTranslate * m_m4EarthRevolutionRotation * m_m4EarthScale, "Earth");
	m_pMeshMngr->SetModelMatrix( m_m4EarthOrbitRotation * m_m4EarthTranslate * m_m4MoonOrbitRotation * m_m4MoonTranslate * m_m4MoonScale, "Moon");

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	static int nEarthOrbits = 0;
	static int nEarthRevolutions = 0;
	static int nMoonOrbits = 0;
	

	//if the rotation time reaches the max roation time, subtract max rotation time and add a rotation to the appropriate variables
	//note, subtracting the max time instead of setting to zero, as setting to zero would cause time to be "lost"

	if(earthRevTime > fEarthHalfRevTime * 2) {
		earthRevTime -= fEarthHalfRevTime * 2;
		nEarthRevolutions++;
	}

	if (earthOrbitTime > fEarthHalfOrbTime * 2) {
		earthOrbitTime -= fEarthHalfOrbTime * 2;
		nEarthOrbits++;
	}

	if (moonOrbitTime > fMoonHalfOrbTime * 2) {
		moonOrbitTime -= fMoonHalfOrbTime * 2;
		nMoonOrbits++;
	}
	

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	
	m_pMeshMngr->Print("Time:");
	m_pMeshMngr->PrintLine(std::to_string(fRunTime));

	m_pMeshMngr->Print("Day:");
	m_pMeshMngr->PrintLine(std::to_string(m_fDay));

	m_pMeshMngr->Print("E_Orbits:");
	m_pMeshMngr->PrintLine(std::to_string(nEarthOrbits));

	m_pMeshMngr->Print("E_Revolutions:");
	m_pMeshMngr->PrintLine(std::to_string(nEarthRevolutions));

	m_pMeshMngr->Print("M_Orbits:");
	m_pMeshMngr->PrintLine(std::to_string(nMoonOrbits));

	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	//Render the grid based on the camera's mode:
	switch (m_pCameraMngr->GetCameraMode())
	{
	default:
		break;
	case CAMERAMODE::CAMROTHOX:
		m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOY:
		m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOZ:
		m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
		break;
	}
	
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}