#include "AI.h"

CAIManager* CAIManager::s_pAIInstance = 0;

CAIManager * CAIManager::GetInstance()
{
	if (s_pAIInstance == 0)
	{
		s_pAIInstance = new CAIManager();
	}
	return s_pAIInstance;
}

void CAIManager::DestroyInstance()
{
	if (s_pAIInstance != 0) // If there is an instance of this class
	{
		//Delete the instance
		delete s_pAIInstance;
		s_pAIInstance = nullptr;
	}
}

void CAIManager::Seek(CPlayer & _player, CEnemy & _enemy)
{
}

void CAIManager::Flee(CPlayer & _player, CEnemy & _enemy)
{
}
