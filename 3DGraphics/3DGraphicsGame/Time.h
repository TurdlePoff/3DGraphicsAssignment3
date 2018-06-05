#pragma once
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: "Time.h"
// Description	: Time declaration file
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

class CTime
{
public:
	static CTime* GetInstance();
	static void DestroyInstance();

	static float GetCurTimeSecs();

	static float deltaTime;	// Time between current frame and last frame
	static float lastFrame; // Time of last frame

private:
	CTime();
	~CTime();
	static CTime* s_pTimeInstance;

};

