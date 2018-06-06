#pragma once
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: "Enemy.h"
// Description	: Enemy declaration file
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#include "stdafx.h"
#include "Sprite.h"

class CEnemy : public CSprite
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
/*
	void SetXSpeed(float newSpeed) { m_xSpeed = newSpeed; }
	void SetYSpeed(float newSpeed) { m_ySpeed = newSpeed; }

	float GetXSpeed() { return m_xSpeed; }
	float GetYSpeed() { return m_ySpeed; }*/

private:
	int m_killPoint;
	bool goodApple;
	std::shared_ptr<CSprite> m_pEnemySprite;
};

