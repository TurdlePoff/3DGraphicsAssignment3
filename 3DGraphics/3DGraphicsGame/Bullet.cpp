//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: "Bullet.cpp"
// Description	: Bullet declaration file
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#include "Bullet.h"

/***********************
* CBullet constructor
* @author: Vivian Ngo
* @date: 9/04/18
* @parameter: bulletSprite - sprite of bullet
* @parameter: damage - damage of bullet
* @parameter: _bltType - bullet type
***********************/
CBullet::CBullet(std::shared_ptr<CSprite> _bulletSprite, int _damage, EBullets _bltType) :
	m_pBulletSprite(_bulletSprite), m_numDamage(_damage), m_bltType(_bltType)
{

}

/***********************
* CBullet destructor
* @author: Vivian Ngo
* @date: 9/04/18
***********************/
CBullet::~CBullet(){}

/***********************
* SetDamagePoint: Sets the bullet damage to a new one
* @author: Vivian Ngo
* @date: 9/04/18
* @parameter: damage - damage of bullet to set
***********************/
void CBullet::SetDamagePoint(int damage)
{
	m_numDamage = damage;
}

/***********************
* GetDamagePoint: Gets the bullet damage
* @author: Vivian Ngo
* @date: 9/04/18
* @return: numDamage - damage of bullet
***********************/
int CBullet::GetDamagePoint()
{
	return m_numDamage;
}
