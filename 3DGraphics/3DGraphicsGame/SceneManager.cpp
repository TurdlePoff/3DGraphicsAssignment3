#include "SceneManager.h"
#include "Level.h"

CSceneManager* CSceneManager::s_pSceneInstance = 0;

CSceneManager::CSceneManager()
{
}

CSceneManager::~CSceneManager()
{
}

CSceneManager* CSceneManager::GetInstance()
{
	if (s_pSceneInstance == 0)
	{
		s_pSceneInstance = new CSceneManager();
	}
	return s_pSceneInstance;
}

void CSceneManager::DestroyInstance()
{
	if (s_pSceneInstance != 0) // If there is an instance of this class
	{
		//Delete the instance
		delete s_pSceneInstance;
		s_pSceneInstance = nullptr;
	}
}

void CSceneManager::SetUpScenes()
{
	std::shared_ptr<CSprite> playerSprite(new CSprite(LAPPLE));
	std::shared_ptr<CPlayer> playerWithSprite(new CPlayer(playerSprite));

	std::shared_ptr<CScene> startScreen(new CLevel(0, STARTSCR, playerWithSprite));
	std::shared_ptr<CScene> level1(new CLevel(1, BG, playerWithSprite));
	std::shared_ptr<CScene> endScreen(new CLevel(2, STARTSCR, playerWithSprite));

	AddScene(startScreen);
	AddScene(level1);
	AddScene(endScreen);

	SwitchScene(0);
}

void CSceneManager::AddScene(std::shared_ptr<CScene> scene)
{
	scenesList.push_back(scene);
	SwitchScene(scene->GetLevelNum());
}

void CSceneManager::RemoveScene(std::shared_ptr<CScene> scene)
{
	it = scenesList.begin();

	it = std::find(scenesList.begin(), scenesList.end(), scene);
	if (it != scenesList.end())
	{
		scenesList.erase(it);
		scenesList.shrink_to_fit();
	}
}

void CSceneManager::SwitchScene(int level)
{
	currentScene = scenesList[level];
}

void CSceneManager::UpdateScene(std::shared_ptr<CScene> scene)
{
	scene->Update();
}

void CSceneManager::RenderScene(std::shared_ptr<CScene> scene)
{
	scene->Render();
}

std::shared_ptr<CScene> CSceneManager::GetCurrentScene()
{
	return currentScene;
}
