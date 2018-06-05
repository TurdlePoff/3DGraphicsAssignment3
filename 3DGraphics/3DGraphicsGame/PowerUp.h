#pragma once
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: "PowerUp.h"
// Description	: PowerUp declaration file
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#include "stdafx.h"
#include "Sprite.h"

class CPowerUp : public CSprite
{
public:
	CPowerUp() {};
	CPowerUp(std::shared_ptr<CSprite> _powSprite, int _powPoint, EPowUps _powType);

	~CPowerUp();

	int GetPowPoint();
	EPowUps GetPowType();

private:
	int m_point;
	EPowUps m_powType;
	std::shared_ptr<CSprite> m_pPowSprite;
};

