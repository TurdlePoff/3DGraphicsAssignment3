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
// Author		: Vivian Ngo & Melanie Jacobson
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#include "stdafx.h"
#include "Sprite.h"

class CEnemy : public CSprite
{
public:
	CEnemy() {};
	CEnemy(std::shared_ptr<CSprite> enemySprite, EEnemyType _enemyType);
	~CEnemy();

	std::shared_ptr<CSprite> GetSprite();
	virtual void Update();

	
	void SetGoodApple(bool ga);
	bool GetIsGoodApple();

	void SetXPos(float newXPos);
	void SetZPos(float newYPos);

	float GetXPos();
	float GetZPos();

	/***********************
	* SetKillPoint: Sets how much the enemy can damage the player
	* @author: Vivian Ngo & Melanie Jacobson
	* @date: 08/05/18
	* @parameter: point - point to set as the kill point
	***********************/
	void SetKillPoint(int point) { m_killPoint = point; }

	/***********************
	* GetKillPoint: Gets how much the enemy can damage the player
	* @author: Vivian Ngo & Melanie Jacobson
	* @date: 08/05/18
	* @return: point - amount of points the enemy can damage the player
	***********************/
	int GetKillPoint() { return m_killPoint; }

	/***********************
	* SetGainPoint: Sets how much the player gains when enemy is killed
	* @author: Vivian Ngo & Melanie Jacobson
	* @date: 08/05/18
	* @parameter: point - amount player gains when enemy is killed
	***********************/
	void SetGainPoint(int point) { m_gainPoints = point; }

	/***********************
	* GetGainPoint: Gets how much the player gains when enemy is killed
	* @author: Vivian Ngo & Melanie Jacobson
	* @date: 08/05/18
	* @return: point - amount player gains when enemy is killed
	***********************/
	int GetGainPoint() { return m_gainPoints; }

	void SetType(EEnemyType _e) { m_eType = _e; }
	EEnemyType GetType() { return m_eType; }
	int targetListNum;

private:
	int m_killPoint;
	int m_gainPoints;

	bool goodApple;
	std::shared_ptr<CSprite> m_pEnemySprite;

	EEnemyType m_eType;
	
	/*float m_xSpeed = 0.5f;
	float m_zSpeed = 1.5f;*/

};

