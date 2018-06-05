#pragma once
#include "stdafx.h"
#include "Sprite.h"

class CPlayer : public CSprite
{
public:
	CPlayer(){};
	CPlayer(std::shared_ptr<CSprite> playerSprite);
	~CPlayer();

	/*int GetCurrentLevel();
	void SetCurrentLevel(int _level);*/
	int GetPlayerLives();				//Gets num of player lives
	void SetPlayerLives(int _lives);	//Sets num player lives available
	int GetScore();						//Get player's current score
	void SetScore(int _newScore);		//Set player's current score
	std::shared_ptr<CSprite> GetSprite();	//Get player's sprite
	
private:
	std::shared_ptr<CSprite> m_pPlayerSprite;	//the player's sprite
	
	//int m_iCurrentLevel;	
	int m_iCurrentLives;	//Number of player lives
	int m_iScore;			//Player score
	int m_bulletStrength;	//Strength of the player's bullets
	bool m_invisible;		//determines whether player is invisible or not
};

