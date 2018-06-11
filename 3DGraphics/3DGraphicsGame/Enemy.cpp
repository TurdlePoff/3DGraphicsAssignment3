//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: "Enemy.cpp"
// Description	: Enemy implementation file
// Author		: Vivian Ngo & Melanie Jacobson
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#include "Enemy.h"

/***********************
* CEnemy: Enemy constructor
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
* @parameter: enemySprite - sprite to set to the enemey
* @parameter: isGood - decides whether enemy instance is bad or good
***********************/
CEnemy::CEnemy(std::shared_ptr<CSprite> enemySprite, EEnemyType _enemyType)
{
	m_pEnemySprite = enemySprite;
	m_pos = new CAIVector(GetXPos(), GetZPos());
	m_vel = new CAIVector( 0.3f, 0.9f );
	m_acc = new CAIVector( 0.5f, 1.5f );
	m_force = new CAIVector( 0.5f, 1.5f );

	switch (_enemyType)
	{
		case ENMY_NORM:
		{
			m_gainPoints = 1;
			m_killPoint = -1;
			break;
		}
	}
}

/***********************
* ~CEnemy: Enemy destructor
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
***********************/
CEnemy::~CEnemy()
{
	delete m_pos;
	m_pos = 0;

	delete m_vel;
	m_vel = 0;

	delete m_acc;
	m_acc = 0;

	delete m_force;
	m_force = 0;
}

/***********************
* GetSprite: Gets the enemy's sprite
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
* @return: m_pEnemySprite - returns the enemy's sprite
***********************/
std::shared_ptr<CSprite> CEnemy::GetSprite()
{
	return m_pEnemySprite;
}

/***********************
* Update: Updates the enemy
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
* @return: m_pEnemySprite - returns the enemy's sprite
***********************/
void CEnemy::Update(){}

/***********************
* SetGoodApple: Sets whether enemy is a enemy OR basically a pickup //MUST CHANGE POSSIBLY
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
* @return: point - amount of points the enemy can damage the player
***********************/
void CEnemy::SetGoodApple(bool isGood)
{
	goodApple = isGood;
}

/***********************
* GetIsGoodApple: Gets whether enemy is a enemy OR a pickup
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
* @return: goodApple - whether enemy is good or bad
***********************/
bool CEnemy::GetIsGoodApple()
{
	return goodApple;
}

/***********************
* SetXPos: Set x position of enemy
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
* @parameter: newXPos - new x position of enemy
***********************/
void CEnemy::SetXPos(float newXPos)
{
	GetSprite()->Translate(glm::vec3(newXPos, GetSprite()->GetPos().y, GetSprite()->GetPos().z));
}

/***********************
* SetZPos: Set z position of enemy
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
* @parameter: newXPos - new z position of enemy
***********************/
void CEnemy::SetZPos(float newYPos)
{
	GetSprite()->Translate(glm::vec3(GetSprite()->GetPos().x, GetSprite()->GetPos().y, newYPos));
}

/***********************
* SetXPos: Get x position of enemy
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
* @return: newXPos - new x position of enemy
***********************/
float CEnemy::GetXPos()
{
	return GetSprite()->GetPos().x;
}

/***********************
* GetZPos: Get z position of enemy
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
* @parameter: newYPos - new y position of enemy
***********************/
float CEnemy::GetZPos()
{
	return GetSprite()->GetPos().z;
}
