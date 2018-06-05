#pragma once
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: "PowerUp.h"
// Description	: PowerUp declaration file
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//


#include "Player.h"
#include "Enemy.h"

class CAIManager
{
public:
	static CAIManager* GetInstance();
	static void DestroyInstance();
	~CAIManager() {};

	void Seek(CPlayer& _player, CEnemy& _enemy);
	void Flee(CPlayer& _player, CEnemy& _enemy);

	void Wander(CPlayer& _player, CEnemy& _enemy);

private:
	static CAIManager* s_pAIInstance;
	CAIManager() {};
};

