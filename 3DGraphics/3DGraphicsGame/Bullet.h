#pragma once
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

#include "stdafx.h"
#include "Sprite.h"

class CBullet : public CSprite
{
public:
	CBullet() {};
	CBullet(std::shared_ptr<CSprite> _bulletSprite, int _damage, EBullets _bltType);
	~CBullet();

	virtual void Update();
	void SetDamagePoint(int damage);
	int GetDamagePoint();
	std::shared_ptr<CSprite> GetSprite();

private:
	int m_numDamage;
	EBullets m_bltType;
	std::shared_ptr<CSprite> m_pBulletSprite;
};

