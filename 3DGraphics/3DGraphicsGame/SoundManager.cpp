#include "SoundManager.h"

CSoundManager* CSoundManager::s_pSoundInstance = 0;

CSoundManager* CSoundManager::GetInstance()
{
	if (s_pSoundInstance == 0)
	{
		s_pSoundInstance = new CSoundManager();
	}
	return s_pSoundInstance;
}

void CSoundManager::DestroyInstance()
{
	if (s_pSoundInstance != 0) // If there is an instance of this class
	{
		//Delete the instance
		delete s_pSoundInstance;
		s_pSoundInstance = nullptr;
	}
}

CSoundManager::~CSoundManager() {}

bool CSoundManager::InitFmod() 
{
	FMOD_RESULT result; result = FMOD::System_Create(&audioMgr); 

	if (result != FMOD_OK) 
	{ 
		return false; 
	}

	result = audioMgr->init(50, FMOD_INIT_NORMAL, 0); 

	if (result != FMOD_OK) 
	{ 
		return false; 
	} 
	return true;
}

const bool CSoundManager::LoadAudio() 
{
	FMOD_RESULT result;

	//result = audioMgr->createSound("Resources/Audio/Thump.wav", FMOD_DEFAULT, 0, &fxThump); 
	result = audioMgr->createSound("Resources/sounds/Background.mp3", FMOD_DEFAULT, 0, &bgmTheme);

	bgmTheme->setMode(FMOD_LOOP_NORMAL);

	return true;
}

void CSoundManager::InitSound()
{
	InitFmod(); 
	LoadAudio();
	FMOD::Channel* channel; 
	audioMgr->playSound(bgmTheme, 0, false, &channel);
	channel->setVolume(0.5f);
}