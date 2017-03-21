#include "AppClass.h"
void AppClass::ProcessKeyboard(void)
{
	bool bModifier = false;
	float fSpeed = 0.01f;

#pragma region ON PRESS/RELEASE DEFINITION
	static bool	bLastF1 = false, bLastF2 = false, bLastF3 = false, bLastF4 = false, bLastF5 = false,
				bLastF6 = false, bLastF7 = false, bLastF8 = false, bLastF9 = false, bLastF10 = false,
				bLastEscape = false;
#define ON_KEY_PRESS_RELEASE(key, pressed_action, released_action){  \
			bool pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::key);			\
			if(pressed){											\
				if(!bLast##key) pressed_action;}/*Just pressed? */\
			else if(bLast##key) released_action;/*Just released?*/\
			bLast##key = pressed; } //remember the state
#pragma endregion

#pragma region Modifiers
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
		bModifier = true;
#pragma endregion


	static float rads = 1.0f;// glm::radians(1.0f);
	static vector3 m_v3XRot = vector3(1.0f, 0.0f, 0.0f);
	static vector3 m_v3YRot = vector3(0.0f,1.0f, 0.0f);
	static vector3 m_v3ZRot = vector3(0.0f, 0.0f, 1.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		m_v3Orientation = vector3(0.0f);
		m_quatOrientation = quaternion();
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
		std::cout << m_quatOrientation.w << " " << m_quatOrientation.x << " " << m_quatOrientation.y << " " << m_quatOrientation.z << std::endl;
	 }


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		if (!bModifier) {
			m_v3Orientation.x += 1.0f;
			m_quatOrientation = glm::rotate(m_quatOrientation, rads, m_v3XRot);
		}
		else {
			m_v3Orientation.x -= 1.0f;
			m_quatOrientation = glm::rotate(m_quatOrientation, -rads, m_v3XRot);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
	{
		if (!bModifier) {
			m_v3Orientation.y += 1.0f;
			m_quatOrientation = glm::rotate(m_quatOrientation, rads, m_v3YRot);
		}
		else {
			m_v3Orientation.y -= 1.0f;
			m_quatOrientation = glm::rotate(m_quatOrientation, -rads, m_v3YRot);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		if (!bModifier) {
			m_v3Orientation.z += 1.0f;
			m_quatOrientation = glm::rotate(m_quatOrientation, rads, m_v3ZRot);
		}
		else {
			m_v3Orientation.z -= 1.0f;
			m_quatOrientation = glm::rotate(m_quatOrientation, -rads, m_v3ZRot);
		}
	}

#pragma region Camera Positioning
	if(bModifier)
		fSpeed *= 10.0f;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		m_pCameraMngr->MoveForward(fSpeed);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		m_pCameraMngr->MoveForward(-fSpeed);
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		m_pCameraMngr->MoveSideways(-fSpeed);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_pCameraMngr->MoveSideways(fSpeed);
	m_pCameraMngr->CalculateView();
#pragma endregion

#pragma region Other Actions
	ON_KEY_PRESS_RELEASE(Escape, NULL, PostMessage(m_pWindow->GetHandler(), WM_QUIT, NULL, NULL))
#pragma endregion
}
void AppClass::ProcessMouse(void)
{
	m_bArcBall = false;
	m_bFPC = false;
	
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle))
		m_bArcBall = true;
	
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		m_bFPC = true;
}
