#pragma once

#include "stdafx.h"
#include "Sprite.h"

class CPowerUp : public CSprite
{
public:
	CPowerUp() {};
	CPowerUp(std::shared_ptr<CSprite> _powSprite, int _powPoint, EPowUps _powType);

	~CPowerUp();

	int GetPowPoint();

private:
	int m_point;
	EPowUps m_powType;
	std::shared_ptr<CSprite> m_pPowSprite;
};

