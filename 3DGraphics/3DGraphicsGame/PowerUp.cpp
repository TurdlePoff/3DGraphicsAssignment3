#include "PowerUp.h"

CPowerUp::CPowerUp(std::shared_ptr<CSprite> _powSprite, int _powPoint, EPowUps _powType):
	m_pPowSprite(_powSprite), m_point(_powPoint), m_powType(_powType)
{
}

CPowerUp::~CPowerUp()
{
}

int CPowerUp::GetPowPoint()
{
	return m_point;
}
