#pragma once
#include "stdafx.h"
#include "Sprite.h"

class CPlayer
{
public:
	CPlayer(){};
	CPlayer(EImage _spriteType);
	CPlayer(std::shared_ptr<CSprite> playerSprite);
	~CPlayer();

	int GetCurrentLevel();
	void SetCurrentLevel(int _level);
	int GetPlayerLives();
	void SetPlayerLives(int _lives);
	int GetScore();
	void SetScore(int _newScore);
	std::shared_ptr<CSprite> GetSprite();
	
private:
	std::shared_ptr<CSprite> m_pPlayerSprite;
	
	int m_iCurrentLevel;
	int m_iCurrentLives;
	int m_iScore;


};

