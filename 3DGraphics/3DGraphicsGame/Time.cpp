#include "stdafx.h"
#include "Time.h"

CTime* CTime::s_pTimeInstance = 0;
float CTime::deltaTime = 0.0f;	// Time between current frame and last frame
float CTime::lastFrame = 0.0f; // Time of last frame

CTime::CTime()
{
	deltaTime = 0.0f;	// Time between current frame and last frame
	lastFrame = 0.0f; // Time of last frame
}

CTime::~CTime()
{
}

/***********************
* GetInstance: Gets the instance of the time singleton class
* @author: Vivian Ngo
* @date: 08/05/18
* @return: s_pTimeInstance - Instance of the Time singleton class
***********************/
CTime * CTime::GetInstance()
{
	if (s_pTimeInstance == 0)
	{
		s_pTimeInstance = new CTime();
	}
	return s_pTimeInstance;
}

/***********************
* DestroyInstance: Destroys the instance of the Time singleton class if there is one
* @author: Vivian Ngo
* @date: 08/05/18
***********************/
void CTime::DestroyInstance()
{
	if (s_pTimeInstance != 0) // If there is an instance of this class
	{
		//Delete the instance
		delete s_pTimeInstance;
		s_pTimeInstance = nullptr;
	}
}

float CTime::GetDeltaTime()
{
	float curTime = (float)glutGet(GLUT_ELAPSED_TIME);
	deltaTime = curTime - lastFrame;
	lastFrame = curTime;
	return deltaTime;
}