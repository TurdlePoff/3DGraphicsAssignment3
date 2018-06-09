#pragma once
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: "Player.h"
// Description	: Player declaration file
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#include "stdafx.h"
#include "Sprite.h"
#include "Bullet.h"

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
	void ResetPlayerStats();
	std::shared_ptr<CBullet> CreateBullet();

	std::shared_ptr<CSprite> GetSprite();	//Get player's sprite

private:
	std::shared_ptr<CSprite> m_pPlayerSprite;	//the player's sprite
	
	//int m_iCurrentLevel;	
	int m_iCurrentLives;	//Number of player lives
	int m_iScore;			//Player score
	int m_bulletStrength;	//Strength of the player's bullets
	bool m_invincible;		//determines whether player is invisible or not

};

