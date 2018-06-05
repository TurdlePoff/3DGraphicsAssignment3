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
// Description : The logic of the game/every level and not the level itself.
// Author : Vivian Ngo
// Mail : vivian.ngo7572@mediadesignschool.com
//

#include "Scene.h"

class CLevel : public CScene
{
public:
	CLevel();
	CLevel(int levelNum, EImage bgSprite, std::shared_ptr<CPlayer> player);
	~CLevel();

	void Render();
	void Update();
	void MovePlayer();
	bool GetIsGameOver();
	void SetGameOver();

private:
	int m_iTimeTilHive;

	bool m_bGameOver;
	
	std::string sc;

};