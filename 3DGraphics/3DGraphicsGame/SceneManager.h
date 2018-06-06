#pragma once
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: "SceneManager.h"
// Description	: SceneManager declaration file
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#include "Scene.h"

class CSceneManager
{
public:
	~CSceneManager() {};
	static CSceneManager* GetInstance();
	static void DestroyInstance();

	void SetUpScenes();
	void AddScene(std::shared_ptr<CScene> scene);
	void RemoveScene(int scene);
	void SwitchScene(int level);
	void ResetLevels(std::shared_ptr<CPlayer> _player);
	void UpdateScene(std::shared_ptr<CScene> scene);
	void RenderScene(std::shared_ptr<CScene> scene);
	std::shared_ptr<CScene> GetCurrentScene();
	int GetCurrentSceneNumber();


private:
	static CSceneManager* s_pSceneInstance;
	CSceneManager() {};

	std::vector<std::shared_ptr<CScene>>::iterator it;
	std::vector<std::shared_ptr<CScene>> scenesList;
	std::shared_ptr<CScene> currentScene;

	
};

