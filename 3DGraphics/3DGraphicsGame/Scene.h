#pragma once

#include "stdafx.h"
#include "Sprite.h"
#include "TextLabel.h"
#include "Player.h"
#include "Enemy.h"

class CScene
{
public:
	CScene();
	~CScene();

	virtual void Render();
	virtual void Update();
	void SetDisplayScene(bool m_bDisplay);
	bool GetIsDisplaying();
	void CreateBackground(EImage bg);
	void AddToSpriteList(std::shared_ptr<CSprite> _spr);
	void AddToTextList(std::shared_ptr<CTextLabel> _spr);
	void AddToEnemyList(std::shared_ptr<CEnemy> _spr);

	std::shared_ptr<CPlayer> GetPlayer();

	int GetLevelNum();
protected:

	int m_iLevelNumber;

	std::vector<std::shared_ptr<CSprite>> m_pSpriteList;
	std::vector<std::shared_ptr<CEnemy>> m_pEnemyList;
	std::vector<std::shared_ptr<CTextLabel>> m_pTextList;

	std::shared_ptr<CSprite> m_pBackgroundSprite;
	bool m_bDisplay;	
	std::shared_ptr<CPlayer> m_pPlayer;

};