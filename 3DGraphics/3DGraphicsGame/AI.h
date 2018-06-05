#pragma once
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

