#pragma once

#include "stdafx.h"
#include "Sprite.h"
#include "textlabel.h"

class LevelManager
{
public:
	LevelManager();
	~LevelManager();

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
};

