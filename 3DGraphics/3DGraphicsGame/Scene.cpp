#include "Scene.h"

CScene::CScene()
{
}

CScene::~CScene()
{
}

void CScene::Render()
{
	m_pBackgroundSprite->Draw();

	//remember to add bg first, with text being last
	for (unsigned int i = 0; i < m_pSpriteList.size(); ++i)
	{
		m_pSpriteList[i]->Draw();
	}


	for (unsigned int i = 0; i < m_pTextList.size(); ++i)
	{
		m_pTextList[i]->Render();
	}

}

void CScene::Update()
{

}

void CScene::SetDisplayScene(bool scene)
{
	m_bDisplay = scene;
}

bool CScene::GetIsDisplaying()
{
	return m_bDisplay;
}

void CScene::CreateBackground(EImage bg)
{
	std::shared_ptr<CSprite> newBg(new CSprite(bg));
	m_pBackgroundSprite = newBg;
}

void CScene::AddToSpriteList(std::shared_ptr<CSprite> _spr)
{
	m_pSpriteList.push_back(_spr);
}

void CScene::AddToTextList(std::shared_ptr<CTextLabel> _txt)
{
	m_pTextList.push_back(_txt);
}

void CScene::AddToEnemyList(std::shared_ptr<CEnemy> _ene)
{
	m_pEnemyList.push_back(_ene);

}

int CScene::GetLevelNum()
{
	return m_iLevelNumber;
}

std::shared_ptr<CPlayer> CScene::GetPlayer()
{
	return m_pPlayer;
}


