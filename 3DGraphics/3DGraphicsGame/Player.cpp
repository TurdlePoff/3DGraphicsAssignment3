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
// Author		: Vivian Ngo & Melanie Jacobson
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#include "Player.h"
#include "Input.h"
#include "SoundManager.h"

/***********************
* CPlayer: Player constructor
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
* @parameter: playerSprite - Set sprite
***********************/
CPlayer::CPlayer(std::shared_ptr<CSprite> playerSprite)
{
	m_pPlayerSprite = playerSprite;
	ResetPlayerStats();
	m_invincible = false;
}

/***********************
* ~CPlayer: Player destructor
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
***********************/
CPlayer::~CPlayer(){}


/***********************
* GetPlayerLives: Gets current player lives
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
* @return: m_iCurrentLives - num of player lives
***********************/
int CPlayer::GetPlayerLives()
{
	return m_iCurrentLives;
}

/***********************
* SetPlayerLives: Sets player lives
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
* @parameter: _lives - num of player lives to set
***********************/
void CPlayer::SetPlayerLives(int _lives)
{
	m_iCurrentLives = _lives;
}

/***********************
* GetScore: Gets player's score
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
* @return: m_iScore - player score
***********************/
int CPlayer::GetScore()
{
	return m_iScore;
}

/***********************
* SetScore: Sets player's score
* @author: Vivian Ngo & Melanie Jacobson
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
	m_invincible = false;
	m_fInvStartTime = 0;
	m_fInvEndTime = 0;
}

/***********************
* MovePlayer: Move player based on player input
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
***********************/
void CPlayer::MovePlayer()
{
	float val = 0.5f;

	float m_fX = 0;
	float m_fY = 0;
	float m_fZ = 0;

	//Moves player depending on direction moved
	if (Utils::KeyState[(unsigned int)'a'] == INPUT_HOLD || Utils::KeyState[(unsigned int)'A'] == INPUT_HOLD)
	{
		if (GetSprite()->GetPos().x < SCR_LEFT) //x boundary - If player is at further than -10 x then prevent them from moving any further
			m_fX = 0;
		else
			m_fX -= val;

		GetSprite()->SetRotatation(glm::vec3(0.0f, 0.0f, 90.0f));
	}
	else if (Utils::KeyState[(unsigned int)'d'] == INPUT_HOLD || Utils::KeyState[(unsigned int)'D'] == INPUT_HOLD)
	{
		if (GetSprite()->GetPos().x > SCR_RIGHT) //x boundary - If player is further than 10 x then prevent them from moving any further
			m_fX = 0;
		else
			m_fX += val;

		GetSprite()->SetRotatation(glm::vec3(0.0f, 0.0f, -90.0f));
	}
	else if (Utils::KeyState[(unsigned int)'w'] == INPUT_HOLD || Utils::KeyState[(unsigned int)'W'] == INPUT_HOLD)
	{
		if (GetSprite()->GetPos().z < SCR_TOP) //z boundary - If player is further than -10 z then prevent them from moving any further
			m_fZ = 0;
		else
			m_fZ -= val;

		GetSprite()->SetRotatation(glm::vec3(0.0f, 0.0f, 0.0f));
	}
	else if (Utils::KeyState[(unsigned int)'s'] == INPUT_HOLD || Utils::KeyState[(unsigned int)'S'] == INPUT_HOLD)
	{
		if (GetSprite()->GetPos().z > SCR_BOT) //z boundary - If player is further than 10 z then prevent them from moving any further
			m_fZ = 0;
		else
			m_fZ += val;

		GetSprite()->SetRotatation(glm::vec3(0.0f, 0.0f, 180.0f));
	}

	//Translate player depending on key pressed
	GetSprite()->Translate(glm::vec3(
		m_fX + GetSprite()->GetPos().x, 
		m_fY + GetSprite()->GetPos().y, 
		m_fZ + GetSprite()->GetPos().z));
}

/***********************
* GetSprite: Gets player's sprite
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
* @return: m_pPlayerSprite - player's sprite
***********************/
std::shared_ptr<CSprite> CPlayer::GetSprite()
{
	return m_pPlayerSprite;
}

/***********************
* SetPowerUpStartTime: Sets a timer if player obtains an invibility power up
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
***********************/
void CPlayer::SetPowerUpStartTime()
{
	m_fInvStartTime = CTime::GetCurTimeSecs();
}

/***********************
* SetPowerUpEndTime: Sets a the latest time checked 
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
***********************/
void CPlayer::SetPowerUpEndTime()
{
	m_fInvEndTime = CTime::GetCurTimeSecs();
}

/***********************
* GetPowerUpStartTime: Gets start of timer
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
***********************/
float CPlayer::GetPowerUpStartTime()
{
	return m_fInvStartTime;
}

/***********************
* GetPowerUpEndTime: Gets latest call of timer
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
***********************/
float CPlayer::GetPowerUpEndTime()
{
	return m_fInvEndTime;
}

/***********************
* CreateBullet: Creates bullet infront of player
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
* @parameter: player - player to shoot bullet
***********************/
std::shared_ptr<CBullet> CPlayer::CreateBullet()
{
	std::shared_ptr<CSprite> newBulletSprite = std::make_shared<CSprite>(BUBBLE, CUBE, glm::vec3(-10.0f, 0.0f, 0.0));
	newBulletSprite->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
	newBulletSprite->SetRotatation(GetSprite()->GetRot());

	if (GetSprite()->GetRot().z == 0.0f) //up
	{
		newBulletSprite->Translate(glm::vec3(
			GetSprite()->GetPos().x,
			GetSprite()->GetPos().y,
			GetSprite()->GetPos().z - 0.4f));
	}
	else if (GetSprite()->GetRot().z == 180.0f) //down
	{
		newBulletSprite->Translate(glm::vec3(
			GetSprite()->GetPos().x,
			GetSprite()->GetPos().y,
			GetSprite()->GetPos().z + 0.4f));
	}
	else if (GetSprite()->GetRot().z == 90.0f) //left
	{
		newBulletSprite->Translate(glm::vec3(
			GetSprite()->GetPos().x - 0.4f,
			GetSprite()->GetPos().y,
			GetSprite()->GetPos().z));
	}
	else if (GetSprite()->GetRot().z == -90.0f) //left
	{
		newBulletSprite->Translate(glm::vec3(
			GetSprite()->GetPos().x + 0.4f,
			GetSprite()->GetPos().y,
			GetSprite()->GetPos().z));
	}

	std::shared_ptr<CBullet> newBullet = std::make_shared<CBullet>(newBulletSprite, 1, BLT_NORM);
	CSoundManager::GetInstance()->InitThump();
	return newBullet;
}

/***********************
* SetInvincible: Sets player as invincible (or not)
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
* @parameter: invincible - set if invincible or not
***********************/
void CPlayer::SetInvincible(bool invincible)
{
	m_invincible = invincible;
	if (invincible)
	{
		GetSprite()->SetColour(glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));
	}
	else
	{
		GetSprite()->SetColour(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

/***********************
* GetInvincible: Get if player is invincible
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
* @return: m_invincible - whether player is invincible or not
***********************/
bool CPlayer::GetInvincible()
{ 
	return m_invincible; 
}

///*********************** not sure if will use yet
//* GetCurrentLevel: Gets current level player is in
//* @author: Vivian Ngo & Melanie Jacobson
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