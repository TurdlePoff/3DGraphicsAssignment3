#pragma once
#include "stdafx.h"
#include "Sprite.h"

class CEnemy
{
public:
	CEnemy() {};
	CEnemy(std::shared_ptr<CSprite> enemySprite, bool isGoodApple);
	~CEnemy();


	std::shared_ptr<CSprite> GetSprite();
	void SetKillPoint(int point);
	int GetKillPoint();
	void SetGoodApple(bool ga);
	bool GetIsGoodApple();

private:
	int m_killPoint;
	bool goodApple;
	std::shared_ptr<CSprite> m_pEnemySprite;

};

