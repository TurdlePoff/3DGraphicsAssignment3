#pragma once
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: "Scene.h"
// Description	: Scene declaration file
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#include "stdafx.h"
#include "Sprite.h"
#include "TextLabel.h"
#include "Player.h"
#include "Enemy.h"
#include "PowerUp.h"
#include "Bullet.h"

class CScene
{
public:
	CScene() {};
	~CScene() {};

	virtual void Render();
	virtual void Update();
	void CreateBackground(EImage bg);
	void AddToSpriteList(std::shared_ptr<CSprite> _spr);
	void AddToTextList(std::shared_ptr<CTextLabel> _txt);
	void AddToEnemyList(std::shared_ptr<CEnemy> _ene);
	void AddToPowerUpList(std::shared_ptr<CPowerUp> _pow);
	void AddToBulletList(std::shared_ptr<CBullet> _blt);

	std::shared_ptr<CPlayer> GetPlayer();

	int GetLevelNum();
protected:

	int m_iLevelNumber;

	std::vector<std::shared_ptr<CSprite>> m_pSpriteList;
	std::vector<std::shared_ptr<CEnemy>> m_pEnemyList;
	std::vector<std::shared_ptr<CTextLabel>> m_pTextList;
	std::vector<std::shared_ptr<CPowerUp>> m_pPowerUpList;
	std::vector<std::shared_ptr<CBullet>> m_pBulletList;

	std::shared_ptr<CSprite> m_pBackgroundSprite;
	bool m_bDisplay;
	std::shared_ptr<CPlayer> m_pPlayer;

};