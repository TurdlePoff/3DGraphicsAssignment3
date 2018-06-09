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
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#include "stdafx.h"
#include "Sprite.h"

struct enVector
{
	float x;
	float z;
};

class CEnemy : public CSprite
{
public:
	CEnemy() {};
	CEnemy(std::shared_ptr<CSprite> enemySprite, EEnemyType _enemyType);
	~CEnemy();

	std::shared_ptr<CSprite> GetSprite();

	
	void SetGoodApple(bool ga);
	bool GetIsGoodApple();

	void SetXPos(float newXPos);
	void SetZPos(float newYPos);

	float GetXPos();
	float GetZPos();

	/***********************
	* SetKillPoint: Sets how much the enemy can damage the player
	* @author: Vivian Ngo
	* @date: 08/05/18
	* @parameter: point - point to set as the kill point
	***********************/
	void SetKillPoint(int point) { m_killPoint = point; }

	/***********************
	* GetKillPoint: Gets how much the enemy can damage the player
	* @author: Vivian Ngo
	* @date: 08/05/18
	* @return: point - amount of points the enemy can damage the player
	***********************/
	int GetKillPoint() { return m_killPoint; }

	/***********************
	* SetGainPoint: Sets how much the player gains when enemy is killed
	* @author: Vivian Ngo
	* @date: 08/05/18
	* @parameter: point - amount player gains when enemy is killed
	***********************/
	void SetGainPoint(int point) { m_gainPoints = point; }

	/***********************
	* GetGainPoint: Gets how much the player gains when enemy is killed
	* @author: Vivian Ngo
	* @date: 08/05/18
	* @return: point - amount player gains when enemy is killed
	***********************/
	int GetGainPoint() { return m_gainPoints; }

	/*void SetXSpeed(float newSpeed) { m_xSpeed = newSpeed; }
	void SetZSpeed(float newSpeed) { m_zSpeed = newSpeed; }

	float GetXSpeed() { return m_xSpeed; }
	float GetZSpeed() { return m_zSpeed; }

	void SetXSpeed(float newSpeed) { m_vel.x = newSpeed; }
	void SetZSpeed(float newSpeed) { m_vel.z = newSpeed; }

	float GetXSpeed() { return m_vel.x; }
	float GetZSpeed() { return m_vel.z; }*/

	enVector m_vel;

	enVector m_acc;
	enVector m_force;

private:
	int m_killPoint;
	int m_gainPoints;

	bool goodApple;
	std::shared_ptr<CSprite> m_pEnemySprite;

	/*float m_xSpeed = 0.5f;
	float m_zSpeed = 1.5f;*/

};

