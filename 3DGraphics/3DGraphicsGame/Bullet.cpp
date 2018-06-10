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
// Author		: Vivian Ngo & Melanie Jacobson
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#include "Bullet.h"

/***********************
* CBullet constructor
* @author: Vivian Ngo & Melanie Jacobson
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
* @author: Vivian Ngo & Melanie Jacobson
* @date: 9/04/18
***********************/
CBullet::~CBullet() {}

/***********************
* Update: Update the bullet
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
***********************/
void CBullet::Update()
{
	if (GetSprite()->GetRot().z == 0.0f) //up
	{
		GetSprite()->Translate(glm::vec3(
			GetSprite()->GetPos().x,
			GetSprite()->GetPos().y,
			GetSprite()->GetPos().z - 0.8f));
	}
	else if (GetSprite()->GetRot().z == 180.0f) //down
	{
		GetSprite()->Translate(glm::vec3(
			GetSprite()->GetPos().x,
			GetSprite()->GetPos().y,
			GetSprite()->GetPos().z + 0.8f));
	}
	else if (GetSprite()->GetRot().z == 90.0f) //left
	{
		GetSprite()->Translate(glm::vec3(
			GetSprite()->GetPos().x - 0.8f,
			GetSprite()->GetPos().y,
			GetSprite()->GetPos().z));
	}
	else if (GetSprite()->GetRot().z == -90.0f) //left
	{
		GetSprite()->Translate(glm::vec3(
			GetSprite()->GetPos().x + 0.8f,
			GetSprite()->GetPos().y,
			GetSprite()->GetPos().z));
	}
}

/***********************
* SetDamagePoint: Sets the bullet damage to a new one
* @author: Vivian Ngo & Melanie Jacobson
* @date: 9/04/18
* @parameter: damage - damage of bullet to set
***********************/
void CBullet::SetDamagePoint(int damage)
{
	m_numDamage = damage;
}

/***********************
* GetDamagePoint: Gets the bullet damage
* @author: Vivian Ngo & Melanie Jacobson
* @date: 9/04/18
* @return: numDamage - damage of bullet
***********************/
int CBullet::GetDamagePoint()
{
	return m_numDamage;
}

/***********************
* GetSprite: Gets the bullet's sprite
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
* @return: m_pBulletSprite - returns the bullet's sprite
***********************/
std::shared_ptr<CSprite> CBullet::GetSprite()
{
	return m_pBulletSprite;
}
