//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: "Input.cpp"
// Description	: Input implementation file
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#include "Input.h"
#include "Camera.h"
#include "SceneManager.h"

CInput* CInput::s_pInputInstance = 0;

//Static variables
GLfloat CInput::MouseSensitivity = 0.05f;
GLfloat CInput::Yaw = 0.0f;
GLfloat CInput::Pitch = 0.0f;
GLfloat CInput::Roll = 0.0f;
GLfloat CInput::LastX = (float)SCR_WIDTH;
GLfloat CInput::LastY = (float)SCR_HEIGHT;
float CInput::LastScrollY = 365.0f;
bool CInput::FirstMouse = true;
float CInput::m_StartTime = 0.0f;
float CInput::m_EndTime = 0.0f;
bool CInput::m_isPressed = false;

GLfloat xOffset;
GLfloat yOffset;

/***********************
* GetInstance: Gets the instance of the Singleton Input class
* @author: Vivian Ngo
* @date: 08/05/18
* @return: s_pInputInstance - Instance of the Input singleton class
***********************/
CInput * CInput::GetInstance()
{
	if (s_pInputInstance == 0)
	{
		s_pInputInstance = new CInput();
	}
	return s_pInputInstance;
}

/***********************
* DestroyInstance: Destroys the instance of the Singleton Input class
* @author: Vivian Ngo
* @date: 08/05/18
***********************/
void CInput::DestroyInstance()
{
	if (s_pInputInstance != 0) // If there is an instance of this class
	{
		//Delete the instance
		delete s_pInputInstance;
		s_pInputInstance = nullptr;
	}
}

/***********************
* ~CInput Destructor
* @author: Vivian Ngo
* @date: 08/05/18
***********************/
CInput::~CInput() {}

/***********************
* Keyboard_Down: Sets the KeyState of the given pressed key as INPUT_HOLD
* @author: Vivian Ngo
* @date: 08/05/18
* @parameter: key - the character inputted
***********************/
void CInput::Keyboard_Down(unsigned char key, int x, int y)
{ 
	if (key != ' ')
	{
		Utils::KeyState[key] = INPUT_HOLD;
	}
	else
	{
		SetLastPressed();

		if (GetElapsedPressedTime() > 0.1f)
		{
  			Utils::SpaceState[key] = INPUT_HOLD;
			SetStartPressed();
		}
	}
}

/***********************
* Keyboard_Down: Sets the KeyState of the given released key as INPUT_RELEASED
* @author: Vivian Ngo 
* @date: 08/05/18
* @parameter: key - the character released
***********************/
void CInput::Keyboard_Up(unsigned char key, int x, int y)
{

	if (Utils::SpaceState[key] == INPUT_HOLD)
	{
		Utils::SpaceState[key] = INPUT_RELEASED;
	}
	
	if(Utils::KeyState[key] == INPUT_HOLD)
	{
		Utils::KeyState[key] = INPUT_RELEASED;

	}
}

/***********************
* MouseClicked: Sets the MouseState as the currently held/released mouse button
* @author: Vivian Ngo
* @date: 08/05/18
* @parameter: button - the mouse button clicked/released
* @parameter: glutState - the state of the mouse button
***********************/
void CInput::MouseClicked(int button, int glutState, int x, int y)
{ 
	if (button < 3) 
	{ 
		Utils::MouseState[button] = (glutState == GLUT_DOWN) ? INPUT_HOLD : INPUT_RELEASED;
	} 
}

/***********************
* MousePassiveMovement: Allows screen to change pitch and yaw when navigating window
* @author: Vivian Ngo
* @date: 29/05/18
* @parameter: x - x position of the mouse
* @parameter: y - y position of the mouse
***********************/
void CInput::MousePassiveMovement(int x, int y)
{
	Utils::mouseX = (float)x;
	Utils::mouseY = (float)y;
	if (FirstMouse == true)// Run only once to initialize the 'Last' vars
	{
		LastX = (GLfloat)x;
		LastY = (GLfloat)y;
		FirstMouse = false;
	}

	LastX = (GLfloat)x;
	LastY = (GLfloat)y;

	xOffset *= MouseSensitivity;
	yOffset *= MouseSensitivity;

	Yaw -= xOffset;
	Pitch -= yOffset;

	// Clamp 'Pitch' so screen doesn’t flip
	if (Pitch > 89.0f)
	{
		Pitch = 89.0f;
	}
	if (Pitch < -89.0f)
	{
		Pitch = -89.0f;
	}

	glm::vec3 frontVector(-cos(glm::radians(Pitch))*sin(glm::radians(Yaw)),
		sin(glm::radians(Pitch)),
		-cos(glm::radians(Pitch)) * cos(glm::radians(Yaw)));
	CCamera::GetInstance()->SetCamFront(glm::normalize(frontVector));
}

/***********************
* MousePassiveMovement: Allows screen to change pitch and yaw when navigating window
* @author: Vivian Ngo
* @date: 29/05/18
* @parameter: x - x position of the mouse
* @parameter: y - y position of the mouse
***********************/
void CInput::MouseScrollHold(int x, int y)
{
	if (Utils::MouseState[1] == INPUT_HOLD)
	{
		if (FirstMouse == true)// Run only once to initialize the 'Last' vars
		{
			LastX = (GLfloat)x;
			LastY = (GLfloat)y;
			FirstMouse = false;
		}

		GLfloat xOffset = (GLfloat)x - LastX;
		GLfloat yOffset = (GLfloat)y - LastY;

		LastX = (GLfloat)x;
		LastY = (GLfloat)y;

		xOffset *= MouseSensitivity + 0.05f;
		yOffset *= MouseSensitivity + 0.05f;

		Yaw -= xOffset;

		Pitch -= yOffset;

		if (Pitch > 89.0f)
		{
			Pitch = 89.0f;
		}
		if (Pitch < -89.0f)
		{
			Pitch = -89.0f;
		}

		glm::vec3 frontVector(-cos(glm::radians(Pitch))*sin(glm::radians(Yaw)),
			sin(glm::radians(Pitch)),
			-cos(glm::radians(Pitch)) * cos(glm::radians(Yaw)));
		CCamera::GetInstance()->SetCamFront(glm::normalize(frontVector));
	}
}

/***********************
* ScollCallback: Scroll window
* @author: Vivian Ngo
* @date: 29/05/18
* @parameter: button - button 
* @parameter: glutState - scroll state
* @parameter: xOffset - x offset
* @parameter: yOffset - y offset
***********************/
void CInput::ScollCallback(int button, int glutState, int xOffset, int yOffset)
{
	CCamera * c = CCamera::GetInstance();
	float movement = 0.1f;
	//If player scrolls mouse
	if (glutState == 1 || glutState == -1)
	{
		glutState *= -1; //Reverse glutstate
		
		//Increase/decrease the field of view
		if (c->GetFOV() > 44.35f && c->GetFOV() < 46.2f)
		{
			c->SetFOV(c->GetFOV() + (movement * glutState));
		}
		else if (c->GetFOV() <= 44.4f)
		{
			c->SetFOV(44.4f);
		}
		else if (c->GetFOV() >= 46.1f)
		{
			c->SetFOV(46.1f);
		}
	}
}

/***********************
* SpecialKeyPress: Sets special key as pressed
* @author: Vivian Ngo
* @date: 08/05/18
* @parameter: key - key pressed
* @parameter: x
* @parameter: y
***********************/
void CInput::SpecialKeyPress(int key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_UP:
		{
			Utils::SpecKeyState[0] = INPUT_HOLD;
			break;
		}
		case GLUT_KEY_DOWN:
		{
			Utils::SpecKeyState[1] = INPUT_HOLD;
			break;

		}
		case GLUT_KEY_LEFT:
		{
			Utils::SpecKeyState[2] = INPUT_HOLD;
			break;
		}
		case GLUT_KEY_RIGHT:
		{
			Utils::SpecKeyState[3] = INPUT_HOLD;
			break;
		} 
	}
}

/***********************
* SpecialKeyRelease: Release special keys
* @author: Vivian Ngo
* @date: 08/05/18
* @parameter: key - key pressed
* @parameter: x
* @parameter: y
***********************/
void CInput::SpecialKeyRelease(int key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_UP:
		{
			Utils::SpecKeyState[0] = INPUT_RELEASED;
			break;
		}
		case GLUT_KEY_DOWN:
		{
			Utils::SpecKeyState[1] = INPUT_RELEASED;
			break;

		}
		case GLUT_KEY_LEFT:
		{
			Utils::SpecKeyState[2] = INPUT_RELEASED;
			break;
		}
		case GLUT_KEY_RIGHT:
		{
			Utils::SpecKeyState[3] = INPUT_RELEASED;
			break;
		}
	}
}

/***********************
* SetHitStartTime: Sets start time of when collided with
* @author: Vivian Ngo
* @date: 08/05/18
***********************/
void CInput::SetStartPressed()
{
	m_StartTime = CTime::GetCurTimeSecs();
}

/***********************
* SetHitEndTime: Sets latest time of when collided with
* @author: Vivian Ngo
* @date: 08/05/18
***********************/
void CInput::SetLastPressed()
{
	m_EndTime = CTime::GetCurTimeSecs();
}

/***********************
* SetHitEndTime: Sets latest time of when collided with
* @author: Vivian Ngo
* @date: 08/05/18
* @return: m_StartTime - time of when enemy was first collided
***********************/
float CInput::GetStartPressed()
{
	return m_StartTime;
}

/***********************
* SetHitEndTime: Sets latest time of when collided with
* @author: Vivian Ngo
* @date: 08/05/18
***********************/
float CInput::GetLastPressed()
{
	return m_EndTime;
}

/***********************
* GetElapsedHitTime: Gets the elapsed hit time from when the enemy was first collided to now
* @author: Vivian Ngo
* @date: 08/05/18
***********************/
float CInput::GetElapsedPressedTime()
{
	return m_EndTime - m_StartTime;
}

/***********************
* SetHit: Set sprite is hit
* @author: Vivian Ngo
* @date: 08/05/18
* @parameter: _isHit - Set whether sprite entity is hit or not
***********************/
void CInput::SetIsPressed(bool _isHit)
{
	m_isPressed = _isHit;
}

/***********************
* GetIsHit: Get sprite is hit
* @author: Vivian Ngo
* @date: 08/05/18
* @return: m_isHit - Gets whether sprite entity is hit or not
***********************/
bool CInput::GetIsPressed()
{
	return m_isPressed;
}