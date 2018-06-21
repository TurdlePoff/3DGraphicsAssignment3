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
// Author		: Vivian Ngo & Melanie Jacobson
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

class CTime
{
public:
	static CTime* GetInstance();
	static void DestroyInstance();

	static float GetCurTimeSecs();

	static void SetUpdateStartTime();
	static void SetUpdateEndTime();
	static float GetUpdateStartTime();
	static float GetUpdateEndTime();

	static float GetDeltaTime();

private:
	CTime();
	~CTime();
	static CTime* s_pTimeInstance;
	static float oldTime;
	static float deltaTime;	// Time between current frame and last frame
	static float lastUpdate; // Time of last update
	static float startUpdate; // Time of last update

};

