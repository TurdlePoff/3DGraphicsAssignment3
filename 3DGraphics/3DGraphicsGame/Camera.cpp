//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: "Camera.cpp"
// Description	: Camera implementation file
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#include "Camera.h"
#include "Time.h"
#include "Input.h"

CCamera* CCamera::s_pCameraInstance = 0;
glm::vec3 CCamera::cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
float CCamera::m_fov = 45.0f; // field of view

/***********************
* CCamera: Camera constructor
* @author: Vivian Ngo
* @date: 08/05/18
***********************/
CCamera::CCamera()
{

	//projection = glm::ortho(-iWidthScaled, iWidthScaled, -iHeightScaled, iHeightScaled, 0.0f, 100.0f);
	glm::mat4 translate = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 rotation = glm::rotate(glm::mat4(), glm::radians(glm::vec3(0.0f, 0.0f, 0.0f).x), glm::vec3(1, 0, 0));
	rotation = glm::rotate(rotation, glm::radians(glm::vec3(0.0f, 0.0f, 0.0f).z), glm::vec3(0, 1, 0));
	rotation = glm::rotate(rotation, glm::radians(glm::vec3(0.0f, 0.0f, 0.0f).y), glm::vec3(0, 0, 1));
	glm::mat4 scale = glm::scale(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f));

	glm::mat4 Model = translate * rotation * scale;

	//cameraFront = CInput::GetInstance()->MousePassiveMovement();

	//Moves the camera when WASD input is pressed
	float cameraSpeed = 0.01f * CTime::GetInstance()->GetCurTimeSecs();
	glm::mat4 ROT = glm::rotate(glm::mat4(), glm::radians(80.0f), glm::vec3(1.0f, 0.0f, -1.0f));

	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp) * ROT;

	projection = glm::perspective(m_fov, (GLfloat)SCR_WIDTH / (GLfloat)SCR_HEIGHT, 0.1f, 1000.0f);
	glm::mat4 MVP = projection * view * Model;
	glUseProgram(Utils::programTextured);
	GLint MVPLoc = glGetUniformLocation(Utils::programTextured, "MVP");
	glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, glm::value_ptr(MVP));
}

/***********************
* GetInstance: Gets the instance of the camera singleton class
* @author: Vivian Ngo
* @date: 08/05/18
* @return: s_pCameraInstance - Instance of the Camera singleton class
***********************/
CCamera* CCamera::GetInstance()
{
	if (s_pCameraInstance == 0)
	{
		s_pCameraInstance = new CCamera();
	}
	return s_pCameraInstance;
}

/***********************
* DestroyInstance: Destroys the instance of the camera singleton class if there is one
* @author: Vivian Ngo
* @date: 08/05/18
***********************/
void CCamera::DestroyInstance()
{
	if (s_pCameraInstance != 0) // If there is an instance of this class
	{
		//Delete the instance
		delete s_pCameraInstance;
		s_pCameraInstance = nullptr;
	}
}

/***********************
* SetMVP: Destroys the instance of the camera singleton class if there is one
* @author: Vivian Ngo
* @date: 08/05/18
* @parameter: _trans - Translation
* @parameter: _scale - Scale
* @parameter: _rot - Rotation
***********************/
void CCamera::SetMVP(glm::vec3 _trans, glm::vec3 _scale, glm::vec3 _rot)
{
	//Calculate the model to be displayed onto the screen
	glm::mat4 translate = glm::translate(glm::mat4(), _trans);
	glm::mat4 rotation = glm::rotate(glm::mat4(), glm::radians(_rot.x), glm::vec3(1, 0, 0));
	rotation = glm::rotate(rotation, glm::radians(_rot.z), glm::vec3(0, 1, 0));
	rotation = glm::rotate(rotation, glm::radians(_rot.y), glm::vec3(0, 0, 1));
	glm::mat4 scale = glm::scale(glm::mat4(), _scale);

	glm::mat4 Model = translate * rotation * scale;

	//cameraFront = CInput::GetInstance()->MousePassiveMovement();

	//Moves the camera when WASD input is pressed
	float cameraSpeed = 0.01f * CTime::GetInstance()->GetCurTimeSecs();


	//UNCOMMENT TO MOVE CAMERA
	/*if (Utils::KeyState[(unsigned int)'w'] == INPUT_HOLD || Utils::KeyState[(unsigned int)'W'] == INPUT_HOLD)
	{
	cameraPos += cameraSpeed * cameraFront;
	}
	else if (Utils::KeyState[(unsigned int)'s'] == INPUT_HOLD || Utils::KeyState[(unsigned int)'S'] == INPUT_HOLD)
	{
	cameraPos -= cameraSpeed * cameraFront;
	}
	else if (Utils::KeyState[(unsigned int)'a'] == INPUT_HOLD || Utils::KeyState[(unsigned int)'A'] == INPUT_HOLD)
	{
	cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
	else if (Utils::KeyState[(unsigned int)'d'] == INPUT_HOLD || Utils::KeyState[(unsigned int)'D'] == INPUT_HOLD)
	{
	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}*/

	//ROTATE CAMERA TO VIEW AS EAGLE EYE
	glm::mat4 ROT = glm::rotate(glm::mat4(), glm::radians(80.0f), glm::vec3(1.0f, 0.0f, 0.0f));


	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp) * ROT;

	projection = glm::perspective(m_fov, (GLfloat)SCR_WIDTH / (GLfloat)SCR_HEIGHT, 0.1f, 1000.0f);
	//Rotating camera - take away the camera wasd input first to test
	//float currentTime = glutGet(GLUT_ELAPSED_TIME);
	//currentTime = currentTime * 0.001f;
	//GLfloat camHeight = 3.0f;
	//GLfloat radius = 20.0f;
	//GLfloat camX = sin(currentTime) * radius; // Rotating the Camera around
	//GLfloat camZ = cos(currentTime) * radius; // the 3D object
	//view = glm::lookAt(glm::vec3(camX, camHeight, camZ), glm::vec3(0.0f, 0.0f, 0.0f),
	//	glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 MVP = projection * view * Model;
	glUseProgram(Utils::programTextured);
	GLint MVPLoc = glGetUniformLocation(Utils::programTextured, "MVP");
	glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, glm::value_ptr(MVP));
}

/***********************
* SetFOV: Sets the field of view
* @author: Vivian Ngo
* @date: 08/05/18
* @parameter: _fov to change
***********************/
void CCamera::SetFOV(float _fov)
{
	m_fov = _fov;
}

float CCamera::GetFOV()
{
	return m_fov;
}

/***********************
* SetCamFront: Sets the camera front
* @author: Vivian Ngo
* @date: 08/05/18
* @parameter: _cFront - the coordinates of the camera front to change to
***********************/
void CCamera::SetCamFront(glm::vec3 _cFront)
{
	cameraFront = _cFront;
}

/***********************
* SetCamPos: Sets the camera position
* @author: Vivian Ngo
* @date: 08/05/18
* @parameter: _cPos - the coordinates of the camera position to change to
***********************/
void CCamera::SetCamPos(glm::vec3 _cPos)
{
	cameraPos = _cPos;
}

/***********************
* SetCamUp: Sets camera up
* @author: Vivian Ngo
* @date: 08/05/18
* @parameter: _cUp - the coordinates of camera up to change to
***********************/
void CCamera::SetCamUp(glm::vec3 _cUp)
{
	cameraUp = _cUp;
}

/***********************
* SetCamSpeed: Sets the speed of the camera
* @author: Vivian Ngo
* @date: 08/05/18
* @parameter: _cSpeed - the camera speed to change to
***********************/
void CCamera::SetCamSpeed(float _cSpeed)
{
	cameraSpeed = _cSpeed;
}

/***********************
* GetCamFront: Gets the camera front
* @author: Vivian Ngo
* @date: 08/05/18
* @return: cameraFront - the camera front
***********************/
glm::vec3 CCamera::GetCamFront()
{
	return cameraFront;
}

/***********************
* GetCamPos: Gets the camera's position
* @author: Vivian Ngo
* @date: 08/05/18
* @return: cameraPos - the camera's position
***********************/
glm::vec3 CCamera::GetCamPos()
{
	return cameraPos;
}

/***********************
* GetCamUp: Gets the camera up coordinates
* @author: Vivian Ngo
* @date: 08/05/18
* @return: cameraUp - the camera up coordinate
***********************/
glm::vec3 CCamera::GetCamUp()
{
	return cameraUp;
}

/***********************
* GetCamSpeed: Gets the camera speed
* @author: Vivian Ngo
* @date: 08/05/18
* @return: cameraSpeed - the camera speed
***********************/
float CCamera::GetCamSpeed()
{
	return cameraSpeed;
}
