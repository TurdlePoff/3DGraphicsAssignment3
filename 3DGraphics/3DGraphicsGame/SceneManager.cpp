#include "SceneManager.h"
#include "Level.h"

CSceneManager* CSceneManager::s_pSceneInstance = 0;

/***********************
* GetInstance: Gets scene manager Instance
* @author: Vivian Ngo
* @date: 08 / 05 / 18
* return s_pSoundInstance - instance of sound manager
***********************/
CSceneManager* CSceneManager::GetInstance()
{
	if (s_pSceneInstance == 0)
	{
		s_pSceneInstance = new CSceneManager();
	}
	return s_pSceneInstance;
}

/***********************
* DestroyInstance: Destroys scene manager Instance
* @author: Vivian Ngo
* @date: 08 / 05 / 18
***********************/
void CSceneManager::DestroyInstance()
{
	if (s_pSceneInstance != 0) // If there is an instance of this class
	{
		//Delete the instance
		delete s_pSceneInstance;
		s_pSceneInstance = nullptr;
	}
}

/***********************
* SetUpScenes: Set up scene items
* @author: Vivian Ngo
* @date: 08 / 05 / 18
***********************/
void CSceneManager::SetUpScenes()
{
	std::shared_ptr<CSprite> playerSprite(new CSprite(BIRB1));
	std::shared_ptr<CPlayer> playerWithSprite(new CPlayer(playerSprite));

	std::shared_ptr<CScene> startScreen(new CLevel(0, STARTSCR, playerWithSprite));
	std::shared_ptr<CScene> level1(new CLevel(1, BG, playerWithSprite));
	std::shared_ptr<CScene> endScreen(new CLevel(2, STARTSCR, playerWithSprite));

	AddScene(startScreen);
	AddScene(level1);
	AddScene(endScreen);

	SwitchScene(0);
}

/***********************
* AddScene: Add scene to scene manager
* @author: Vivian Ngo
* @date: 08 / 05 / 18
* @parameter: scene - scene to add
***********************/
void CSceneManager::AddScene(std::shared_ptr<CScene> scene)
{
	scenesList.push_back(scene);
	SwitchScene(scene->GetLevelNum());
}

/***********************
* RemoveScene: Remove scene from scene manager
* @author: Vivian Ngo
* @date: 08 / 05 / 18
* @parameter: scene - scene to add
***********************/
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

/***********************
* SwitchScene: Switch scene to the number specified
* @author: Vivian Ngo
* @date: 08 / 05 / 18
* @parameter: level - scene to change to
***********************/
void CSceneManager::SwitchScene(int level)
{
	currentScene = scenesList[level];
}

/***********************
* UpdateScene: Update the scene specified
* @author: Vivian Ngo
* @date: 08 / 05 / 18
* @parameter: scene - scene to update
***********************/
void CSceneManager::UpdateScene(std::shared_ptr<CScene> scene)
{
	scene->Update();
}

/***********************
* RenderScene: Render the scene specified
* @author: Vivian Ngo
* @date: 08 / 05 / 18
* @parameter: scene - scene to render
***********************/
void CSceneManager::RenderScene(std::shared_ptr<CScene> scene)
{
	scene->Render();
}

/***********************
* GetCurrentScene: Gets the current scene
* @author: Vivian Ngo
* @date: 08 / 05 / 18
* @return: currentScene - the current scene
***********************/
std::shared_ptr<CScene> CSceneManager::GetCurrentScene()
{
	return currentScene;
}
