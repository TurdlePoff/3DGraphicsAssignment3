#include "SoundManager.h"

CSoundManager* CSoundManager::s_pSoundInstance = 0;

/***********************
* GetInstance: Gets the instance of the sound manager
* @author: Vivian Ngo
* @date: 08/05/18
* @return: s_pSoundInstance - instance of the sound manager
***********************/
CSoundManager* CSoundManager::GetInstance()
{
	if (s_pSoundInstance == 0)
	{
		s_pSoundInstance = new CSoundManager();
	}
	return s_pSoundInstance;
}

/***********************
* DestroyInstance: Destroys the instance of the sound manager
* @author: Vivian Ngo
* @date: 08/05/18
***********************/
void CSoundManager::DestroyInstance()
{
	if (s_pSoundInstance != 0) // If there is an instance of this class
	{
		//Delete the instance
		delete s_pSoundInstance;
		s_pSoundInstance = nullptr;
	}
}

/***********************
* ~CSoundManager: Destructor of the sound manager
* @author: Vivian Ngo
* @date: 08/05/18
***********************/
CSoundManager::~CSoundManager() {}

/***********************
* InitFmod: Initialise fmod
* @author: Vivian Ngo
* @date: 08/05/18
***********************/
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

/*********************** //	NEED TO CHANGE METHOD TO ALLOW DIF BG SOUNDS
* LoadAudio: Load the sound to play
* @author: Vivian Ngo
* @date: 08/05/18
***********************/
void CSoundManager::LoadAudio() 
{
	FMOD_RESULT result;

	//result = audioMgr->createSound("Resources/Audio/Thump.wav", FMOD_DEFAULT, 0, &fxThump); 
	result = audioMgr->createSound("Resources/sounds/Background.mp3", FMOD_DEFAULT, 0, &bgmTheme);

	bgmTheme->setMode(FMOD_LOOP_NORMAL);
}

/***********************
* InitSound: Initialise the sound to play
* @author: Vivian Ngo
* @date: 08/05/18
***********************/
void CSoundManager::InitSound()
{
	InitFmod(); 
	LoadAudio();
	FMOD::Channel* channel; 
	audioMgr->playSound(bgmTheme, 0, false, &channel);
	channel->setVolume(0.5f);
}