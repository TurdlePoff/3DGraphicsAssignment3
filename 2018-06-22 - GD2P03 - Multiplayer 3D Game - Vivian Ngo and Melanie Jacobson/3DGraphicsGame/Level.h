#pragma once
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name : Level.h
// Description : Level declaration file
// Author : Vivian Ngo & Melanie Jacobson
// Mail : vivian.ngo7572@mediadesignschool.com
//

#include "Scene.h"
#include "CubeMap.h"

class CLevel : public CScene
{
public:
	CLevel();
	CLevel(int levelNum, EImage bgSprite, std::shared_ptr<CPlayer> player);
	~CLevel();

	void Render();
	void Update();
	void CheckEnemyCollision(std::shared_ptr<CSprite> player);
	void CheckPowerUpCollision(std::shared_ptr<CSprite> player);
	void CheckBulletEnemyCollision();
	void CheckBulletBoundaries();

	bool IsMouseOverButton(std::shared_ptr<CTextLabel> t);
	void CheckButtonHovered();
	void HandleStartScreenButtons();
	void SetUpAI();

	bool GetIsGameOver();
	void SetGameOver();

private:
	int m_iTimeTilHive;

	bool m_bGameOver;

	float m_move = 5.0f;
	
	std::string sc;

	std::shared_ptr<CCubeMap> cMap;
	std::vector<glm::vec3> pathToFollow;
	std::vector<glm::vec3> wallPath;

	std::vector<std::shared_ptr<CPlayer>> playerList;
	std::vector<sockaddr_in> serverList;

	bool isHost;
	bool lobbyFirst;
};