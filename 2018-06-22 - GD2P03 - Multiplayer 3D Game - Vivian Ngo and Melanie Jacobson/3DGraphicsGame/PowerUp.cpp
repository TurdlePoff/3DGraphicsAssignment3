//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: "PowerUp.cpp"
// Description	: PowerUp implementation file
// Author		: Vivian Ngo & Melanie Jacobson
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#include "PowerUp.h"

/***********************
* CPowerUp constructor
* @author: Vivian Ngo & Melanie Jacobson
* @date: 9/04/18
* @parameter: _powSprite - sprite of power up
* @parameter: _powPoint - points the power up gives (if any)
* @parameter: _powType - power up type
***********************/
CPowerUp::CPowerUp(std::shared_ptr<CSprite> _powSprite, int _powPoint, EPowUps _powType) :
	m_pPowSprite(_powSprite), m_point(_powPoint), m_powType(_powType)
{
}

/***********************
* ~CPowerUp destructor
* @author: Vivian Ngo & Melanie Jacobson
* @date: 9/04/18
***********************/
CPowerUp::~CPowerUp()
{
}

/***********************
* GetPowPoint: Get the powerup's point
* @author: Vivian Ngo & Melanie Jacobson
* @date: 9/04/18
* @parameter: damage - damage of bullet to set
***********************/
int CPowerUp::GetPowPoint()
{
	return m_point;
}

/***********************
* GetPowType: Get the powerup's enum type
* @author: Vivian Ngo & Melanie Jacobson
* @date: 9/04/18
* @return: m_powType - type of power up
***********************/
EPowUps CPowerUp::GetPowType()
{
	return m_powType;
}

/***********************
* GetSprite: Gets the enemy's sprite
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
* @return: m_pEnemySprite - returns the enemy's sprite
***********************/
std::shared_ptr<CSprite> CPowerUp::GetSprite()
{
	return m_pPowSprite;
}
