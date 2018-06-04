#pragma once

#include "stdafx.h"
#include "Dependencies\FMOD\fmod.hpp"

class CSoundManager
{
public:
	static CSoundManager* GetInstance();
	static void DestroyInstance();

	~CSoundManager() {};

	bool InitFmod();
	void LoadAudio();
	void InitSound();

private: 
	static CSoundManager* s_pSoundInstance;
	CSoundManager() {};

	FMOD::System* audioMgr; 
	FMOD::Sound* fxThump; 
	FMOD::Sound* bgmTheme;
};
