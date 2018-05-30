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
CInput::~CInput()
{
}

/***********************
* Keyboard_Down: Sets the KeyState of the given pressed key as INPUT_HOLD
* @author: Vivian Ngo
* @date: 08/05/18
* @parameter: key - the character inputted
***********************/
void CInput::Keyboard_Down(unsigned char key, int x, int y)
{ 
	Utils::KeyState[key] = INPUT_HOLD; 
}

/***********************
* Keyboard_Down: Sets the KeyState of the given released key as INPUT_RELEASED
* @author: Vivian Ngo
* @date: 08/05/18
* @parameter: key - the character released
***********************/
void CInput::Keyboard_Up(unsigned char key, int x, int y)
{
	Utils::KeyState[key] = INPUT_RELEASED;
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
* MousePassiveMovement: havent used so not sure yet
***********************/
void CInput::MousePassiveMovement(int x, int y)
{
	Utils::XYO = x;
	Utils::YYO = y;

	if (FirstMouse == true)// Run only once to initialize the 'Last' vars
	{
		LastX = x;
		LastY = y;
		FirstMouse = false;
	}

	GLfloat xOffset = x - LastX;
	GLfloat yOffset = y - LastY;
	LastX = x;
	LastY = y;
	xOffset *= MouseSensitivity;
	yOffset *= MouseSensitivity;
	Yaw -= xOffset;
	Pitch -= yOffset;	// Clamp 'Pitch' so screen doesn’t flip
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
