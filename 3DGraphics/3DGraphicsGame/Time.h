#pragma once
class CTime
{
public:
	static CTime* GetInstance();
	static void DestroyInstance();

	static float GetDeltaTime();

	static float deltaTime;	// Time between current frame and last frame
	static float lastFrame; // Time of last frame
private:
	CTime();
	~CTime();
	static CTime* s_pTimeInstance;

};

