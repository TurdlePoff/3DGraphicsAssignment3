//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: "Scene.cpp"
// Description	: Scene implementation file
// Author		: Vivian Ngo & Melanie Jacobson
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#include "Scene.h"

/***********************
* Render: Render Scene	//VIRTUAL
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
***********************/
void CScene::Render() {}

/***********************
* Render: Update Scene	//VIRTUAL
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
***********************/
void CScene::Update() {}

/***********************
* CreateBackground: Create Background for Scene
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
* @parameter: bg - background to create and set
***********************/
void CScene::CreateBackground(EImage bg)
{
	std::shared_ptr<CSprite> newBg(new CSprite(bg, CUBE, glm::vec3(0.0f, -10.0f, 5.0f)));
	m_pBackgroundSprite = newBg;
}

/***********************
* AddToSpriteList: Add sprite to the scene's spritelist
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
* @parameter: _spr - sprite to add to sprite list
***********************/
void CScene::AddToSpriteList(std::shared_ptr<CSprite> _spr)
{
	m_pSpriteList.push_back(_spr);
}

/***********************
* AddToTextList: Add text to the scene's textlist
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
* @parameter: _txt - txt to add to text list
***********************/
void CScene::AddToTextList(std::shared_ptr<CTextLabel> _txt)
{
	m_pTextList.push_back(_txt);
}

/***********************
* AddToEnemyList: Add enemy to the scene's enemyList
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
* @parameter: _ene - enemy to add to enemy list
***********************/
void CScene::AddToEnemyList(std::shared_ptr<CEnemy> _ene)
{
	m_pEnemyList.push_back(_ene);

}

/***********************
* AddToPowerUpList: Add powerup to the scene's powerup list
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
* @parameter: _spr - powerup to add to powerup list
***********************/
void CScene::AddToPowerUpList(std::shared_ptr<CPowerUp> _pow)
{
	m_pPowerUpList.push_back(_pow);
}

/***********************
* AddToBulletList: Add bullet to the scene's bullet list
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
* @parameter: _blt - bullet to add to bullet list
***********************/
void CScene::AddToBulletList(std::shared_ptr<CBullet> _blt)
{
	m_pPlayerBulletList.push_back(_blt);
}

/***********************
* SetRemainingEnemies: Sets remaining enemies in level
* @author: Vivian Ngo & Melanie Jacobson
* @date: 8/06/18
* @parameter: remaining - remaining enemies
***********************/
void CScene::SetRemainingEnemies(int remaining)
{
	m_iEnemiesRemaining = remaining;
}

/***********************
* GetRemainingEnemies:
* @author: Vivian Ngo & Melanie Jacobson
* @date: 8/06/18
* @return: m_iEnemiesRemaining - remaining enemies in level
***********************/
int CScene::GetRemainingEnemies()
{
	return m_iEnemiesRemaining;
}

/***********************
* GetLevelNum: Gets the current level number/scene
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
* @return: m_iLevelNumber - current level/scene
***********************/
int CScene::GetLevelNum()
{
	return m_iLevelNumber;
}

/***********************
* GetPlayer: Player of the scene
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
* @return: m_pPlayer - player of the scene
***********************/
std::shared_ptr<CPlayer> CScene::GetPlayer()
{
	return m_pPlayer;
}


