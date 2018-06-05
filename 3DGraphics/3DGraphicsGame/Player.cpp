#include "Player.h"
#include "Input.h"

CPlayer::CPlayer(EImage _spriteType)
{
}

CPlayer::CPlayer(std::shared_ptr<CSprite> playerSprite)
{
	m_pPlayerSprite = playerSprite;
}


CPlayer::~CPlayer()
{

}

//gettimeelapsed 

int CPlayer::GetCurrentLevel()
{
	return m_iCurrentLevel;
}

void CPlayer::SetCurrentLevel(int _level)
{
	m_iCurrentLevel = _level;
}

int CPlayer::GetPlayerLives()
{
	return m_iCurrentLives;
}

void CPlayer::SetPlayerLives(int _lives)
{
	m_iCurrentLives = _lives;
}

int CPlayer::GetScore()
{
	return m_iScore;
}

void CPlayer::SetScore(int _newScore)
{
	m_iScore = _newScore;
}

std::shared_ptr<CSprite> CPlayer::GetSprite()
{
	return m_pPlayerSprite;
}