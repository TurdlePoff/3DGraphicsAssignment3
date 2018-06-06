//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: "Player.cpp"
// Description	: Player implementation file
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#include "Player.h"
#include "Input.h"

/***********************
* CPlayer: Player constructor
* @author: Vivian Ngo
* @date: 08/05/18
* @parameter: playerSprite - Set sprite
***********************/
CPlayer::CPlayer(std::shared_ptr<CSprite> playerSprite)
{
	m_pPlayerSprite = playerSprite;
	ResetPlayerStats();
}

/***********************
* ~CPlayer: Player destructor
* @author: Vivian Ngo
* @date: 08/05/18
***********************/
CPlayer::~CPlayer(){}


/***********************
* GetPlayerLives: Gets current player lives
* @author: Vivian Ngo
* @date: 08/05/18
* @return: m_iCurrentLives - num of player lives
***********************/
int CPlayer::GetPlayerLives()
{
	return m_iCurrentLives;
}

/***********************
* SetPlayerLives: Sets player lives
* @author: Vivian Ngo
* @date: 08/05/18
* @parameter: _lives - num of player lives to set
***********************/
void CPlayer::SetPlayerLives(int _lives)
{
	m_iCurrentLives = _lives;
}

/***********************
* GetScore: Gets player's score
* @author: Vivian Ngo
* @date: 08/05/18
* @return: m_iScore - player score
***********************/
int CPlayer::GetScore()
{
	return m_iScore;
}

/***********************
* SetScore: Sets player's score
* @author: Vivian Ngo
* @date: 08/05/18
* @parameter: _newScore - new player score
***********************/
void CPlayer::SetScore(int _newScore)
{
	m_iScore = _newScore;
}

void CPlayer::ResetPlayerStats()
{
	m_iCurrentLives = 2;
	m_iScore = 0;
	m_bulletStrength = 1;
	m_invisible = false;
}

/***********************
* GetSprite: Gets player's sprite
* @author: Vivian Ngo
* @date: 08/05/18
* @return: m_pPlayerSprite - player's sprite
***********************/
std::shared_ptr<CSprite> CPlayer::GetSprite()
{
	return m_pPlayerSprite;
}



///*********************** not sure if will use yet
//* GetCurrentLevel: Gets current level player is in
//* @author: Vivian Ngo
//* @date: 08/05/18
//***********************/
//int CPlayer::GetCurrentLevel()
//{
//	return m_iCurrentLevel;
//}
//
//void CPlayer::SetCurrentLevel(int _level)
//{
//	m_iCurrentLevel = _level;
//}