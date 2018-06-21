//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: "Time.cpp"
// Description	: Time implementation file
// Author		: Vivian Ngo & Melanie Jacobson
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#include "stdafx.h"
#include "Time.h"

CTime* CTime::s_pTimeInstance = 0;
float CTime::deltaTime = 0.0f;	// Time between current frame and last frame
float CTime::lastUpdate = 0.0f; // Time of last frame
float CTime::startUpdate = 0.0f; // Time of last frame
float CTime::oldTime = 0.0f;

/***********************
* CTime constructor
* @author: Vivian Ngo & Melanie Jacobson
* @date: 9/04/18
***********************/
CTime::CTime()
{
	deltaTime = 0.0f;	// Time between current frame and last frame
	lastUpdate = 0.0f; // Time of last frame
	startUpdate = 0.0f;
}

/***********************
* ~CTime destructor
* @author: Vivian Ngo & Melanie Jacobson
* @date: 9/04/18
***********************/
CTime::~CTime(){}

/***********************
* GetInstance: Gets the instance of the time singleton class
* @author: Vivian Ngo & Melanie Jacobson
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
* @author: Vivian Ngo & Melanie Jacobson
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

/***********************
* GetDeltaTime: Gets the current time on the system
* @author: Vivian Ngo & Melanie Jacobson
* @date: 9/04/18
* @return current time in seconds;
***********************/
float CTime::GetCurTimeSecs()
{
	return (float)glutGet(GLUT_ELAPSED_TIME)/1000;
}

void CTime::SetUpdateStartTime()
{
	startUpdate = GetCurTimeSecs();
}

void CTime::SetUpdateEndTime()
{
	lastUpdate = GetCurTimeSecs();
}

float CTime::GetUpdateStartTime()
{
	return startUpdate;
}

float CTime::GetUpdateEndTime()
{
	return lastUpdate;
}

float CTime::GetDeltaTime()
{
	//return lastFrame - startFrame;
	float CurrentTime = static_cast<float>(glutGet(GLUT_ELAPSED_TIME) / 1000.0f);
	float TimeDelta = (CurrentTime - oldTime);
	oldTime = CurrentTime;
	return TimeDelta;
}
