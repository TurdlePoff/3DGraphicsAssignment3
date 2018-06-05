//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: "Level.cpp"
// Description	: Level implementation file
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#include "Level.h"
#include "SceneManager.h"
#include "Time.h"

CLevel::CLevel(){}

/***********************
* Level constructor
* @author: Vivian Ngo
* @date: 9/04/18
***********************/
CLevel::CLevel(int levelNum, EImage bgSprite, std::shared_ptr<CPlayer> player)
{
	m_iLevelNumber = levelNum;
	CreateBackground(bgSprite);
	m_pPlayer = player;
	m_pPlayer->SetPlayerLives(2);
	AddToSpriteList(m_pPlayer->GetSprite());

	//IF THE LEVEL IS THE TITLE SCREEN
	if (m_iLevelNumber == 0)
	{
		std::shared_ptr<CTextLabel> titleText1(new CTextLabel("Robotron ??", "Resources/Fonts/bubble.TTF", glm::vec2(40.0f, SCR_HEIGHT / 2 + 140)));
		titleText1->SetColor(glm::vec3(1.0f, 1.0f, 1.0f)); //0.4f, 0.8f, 1.0f)); 

		std::shared_ptr<CTextLabel> startText(new CTextLabel("START", "Resources/Fonts/bubble.TTF", glm::vec2(45.0f, ((SCR_HEIGHT / 2) - 100.0f))));//SCR_HEIGHT - 200.0f));
		startText->SetColor(glm::vec3(0, 1, 0.3f));//1.0f, 1.0f, 0.2f));

		AddToTextList(titleText1);
		AddToTextList(startText);
	}
	else if (m_iLevelNumber == 1)	//IF LEVEL 1
	{
		std::shared_ptr<CSprite> lAppleSprite1(new CSprite(LAPPLE));
		std::shared_ptr<CPowerUp> goodApple(new CPowerUp(lAppleSprite1, 1, POW_1POINT));

		std::shared_ptr<CSprite> mAppleSprite1(new CSprite(ROTTENAPPLE));
		std::shared_ptr<CEnemy> enemyBad(new CEnemy(mAppleSprite1, false));

		AddToPowerUpList(goodApple);
		//(goodApple);
		AddToEnemyList(enemyBad);

		std::string score = "1000";
		std::shared_ptr<CTextLabel> scoreText(new CTextLabel("Score: ", "Resources/Fonts/bubble.TTF", glm::vec2(5.0f, 40.0f)));//SCR_HEIGHT - 200.0f));
		scoreText->SetScale(0.3f);
		scoreText->SetColor(glm::vec3(1.0f, 1.0f, 1.0f)); //0.4f, 0.8f, 1.0f)); 
		AddToTextList(scoreText);

		sc = std::to_string(m_pPlayer->GetScore());
		std::shared_ptr<CTextLabel> actualScoreText(new CTextLabel(sc, "Resources/Fonts/bubble.TTF", glm::vec2(80.0f, 40.0f)));//SCR_HEIGHT - 200.0f));
		actualScoreText->SetScale(0.3f);
		actualScoreText->SetColor(glm::vec3(1.0f, 1.0f, 1.0f)); //0.4f, 0.8f, 1.0f)); 
		AddToTextList(actualScoreText);

		std::shared_ptr<CTextLabel> livesText(new CTextLabel("Lives: ", "Resources/Fonts/bubble.TTF", glm::vec2(5.0, 10.0f)));
		livesText->SetScale(0.3f);
		livesText->SetColor(glm::vec3(1.0f, 1.0f, 1.0f)); //0.4f, 0.8f, 1.0f)); 
		AddToTextList(livesText);

		std::string playerLives = std::to_string(m_pPlayer->GetPlayerLives());
		std::shared_ptr<CTextLabel> actualLivesText(new CTextLabel(playerLives, "Resources/Fonts/bubble.TTF", glm::vec2(80.0f, 10.0f)));//SCR_HEIGHT - 200.0f));
		actualLivesText->SetScale(0.3f);
		actualLivesText->SetColor(glm::vec3(1.0f, 1.0f, 1.0f)); //0.4f, 0.8f, 1.0f)); 
		AddToTextList(actualLivesText);
		/*AddToSpriteList(lAppleSprite1);
		AddToSpriteList(mAppleSprite1);*/
	}
	else if (m_iLevelNumber == 2)	//IF THE LEVEL IS THE GAME OVER SCREEN
	{
		std::shared_ptr<CTextLabel> titleText1(new CTextLabel("But its the only", "Resources/Fonts/bubble.TTF", glm::vec2(SCR_WIDTH / 2, SCR_HEIGHT / 2 + 140)));
		titleText1->SetScale(0.35f);
		titleText1->SetColor(glm::vec3(1.0f, 1.0f, 1.0f)); //0.4f, 0.8f, 1.0f)); 

		std::shared_ptr<CTextLabel> titleText2(new CTextLabel("apple tree out there", "Resources/Fonts/bubble.TTF", glm::vec2(SCR_WIDTH/2, (SCR_HEIGHT / 2 + 100))));
		titleText2->SetScale(0.35f);
		titleText2->SetColor(glm::vec3(1.0f, 1.0f, 1.0f)); //0.4f, 0.8f, 1.0f)); 

		std::shared_ptr<CTextLabel> startText(new CTextLabel("GAME OVER", "Resources/Fonts/bubble.TTF", glm::vec2(SCR_WIDTH / 2, ((SCR_HEIGHT / 2) - 100.0f))));//SCR_HEIGHT - 200.0f));
		startText->SetScale(0.5f);
		startText->SetColor(glm::vec3(0, 1, 0.3f));//1.0f, 1.0f, 0.2f));

		AddToTextList(titleText1);
		AddToTextList(titleText2);
		AddToTextList(startText);
	}
}

/***********************
* Level destructor
* @author: Vivian Ngo
* @date: 9/04/18
***********************/
CLevel::~CLevel() {}

/***********************
* Render: Renders all items in the level
* @author: Vivian Ngo
* @date: 08/05/18
***********************/
void CLevel::Render()
{
	//Draw/Render every item in scene
	m_pBackgroundSprite->Draw();

	//Render all items in sprite list
	for (unsigned int sList = 0; sList < m_pSpriteList.size(); ++sList)
	{
		if(m_pSpriteList[sList]->GetIsDead() != true)
			m_pSpriteList[sList]->Draw();
	}

	//Render all items in enemy list
	for (unsigned int eList = 0; eList < m_pEnemyList.size(); ++eList)
	{
		if (m_pEnemyList[eList]->GetIsDead() != true)
			m_pEnemyList[eList]->GetSprite()->Draw();
	}

	//Render all powerups in powerups list
	for (unsigned int pList = 0; pList < m_pPowerUpList.size(); ++pList)
	{
		if (m_pPowerUpList[pList]->GetIsDead() != true)
			m_pPowerUpList[pList]->GetSprite()->Draw();
	}

	//Render all text in text list
	for (unsigned int tList = 0; tList < m_pTextList.size(); ++tList)
	{
			m_pTextList[tList]->Render();
	}
}

/***********************
* Update: Updates all items in the game
* @author: Vivian Ngo
* @date: 08/05/18
***********************/
void CLevel::Update()
{
	//If the player is currently in level 0 or 2
	if (m_iLevelNumber == 0 || m_iLevelNumber == 2)
	{
		if (Utils::KeyState[(unsigned int)' '] == INPUT_FIRST_PRESS)
		{
			if(m_iLevelNumber == 0)
				CSceneManager::GetInstance()->SwitchScene(1);

			if(m_iLevelNumber == 2)
				CSceneManager::GetInstance()->SwitchScene(0);
		}
	}
	else if (m_iLevelNumber == 1)	//If the player is currently in level 1
	{
		std::shared_ptr<CSprite> player = (GetPlayer()->GetSprite());

		MovePlayer(player);

		CheckEnemyCollision(player);
		CheckPowerUpCollision(player);

		m_pTextList[1]->SetText(std::to_string(GetPlayer()->GetScore()));
		m_pTextList[3]->SetText(std::to_string(GetPlayer()->GetPlayerLives()));

		//If player was hit, player is temporarily red
		if (m_pPlayer->GetSprite()->GetIsHit())
		{
			//Calculate the time since it was hit
			m_pPlayer->GetSprite()->SetHitEndTime();

			//If time since hit is bigger than 1 second, revert colour back to normal
			if (m_pPlayer->GetSprite()->GetHitEndTime() - m_pPlayer->GetSprite()->GetHitStartTime() > 1)
			{
				m_pPlayer->GetSprite()->SetColour(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
			}
		}

		if (m_pPlayer->GetPlayerLives() <= 0)
		{
			CSceneManager::GetInstance()->SwitchScene(2);
		}
	}
}

/***********************
* MovePlayer: Move player based on player input
* @author: Vivian Ngo
* @date: 08/05/18
***********************/
void CLevel::MovePlayer(std::shared_ptr<CSprite> player)
{
	float val = 0.5f;// *CTime::GetInstance()->GetDeltaTime();
	float m_fX = 0;
	float m_fY = 0;
	float m_fZ = 0;

	//Moves player depending on direction moved
	if (Utils::KeyState[(unsigned int)'a'] == INPUT_HOLD || Utils::KeyState[(unsigned int)'A'] == INPUT_HOLD)
	{
		if (player->GetPos().x < -45.0f) //x boundary - If player is at further than -10 x then prevent them from moving any further
			m_fX = 0;
		else
			m_fX -= val;

			player->SetRotatation(glm::vec3(0.0f, 0.0f, 90.0f));
	}
	else if (Utils::KeyState[(unsigned int)'d'] == INPUT_HOLD || Utils::KeyState[(unsigned int)'D'] == INPUT_HOLD)
	{
		if (player->GetPos().x > 45.0f) //x boundary - If player is further than 10 x then prevent them from moving any further
			m_fX = 0;
		else
			m_fX += val;

			player->SetRotatation(glm::vec3(0.0f, 0.0f, -90.0f));
	}
	else if (Utils::KeyState[(unsigned int)'w'] == INPUT_HOLD || Utils::KeyState[(unsigned int)'W'] == INPUT_HOLD)
	{
		if (player->GetPos().z < -25.0f) //z boundary - If player is further than -10 z then prevent them from moving any further
			m_fZ = 0;
		else
			m_fZ -= val;

		player->SetRotatation(glm::vec3(0.0f, 0.0f, 0.0f));
	}
	else if (Utils::KeyState[(unsigned int)'s'] == INPUT_HOLD || Utils::KeyState[(unsigned int)'S'] == INPUT_HOLD)
	{
		if (player->GetPos().z > 45.0f) //z boundary - If player is further than 10 z then prevent them from moving any further
			m_fZ = 0;
		else
			m_fZ += val;

		player->SetRotatation(glm::vec3(0.0f, 0.0f, 180.0f));
	}

	//Translate player depending on key pressed
	player->Translate(glm::vec3(m_fX + player->GetPos().x, m_fY + player->GetPos().y, m_fZ + player->GetPos().z));
}

/***********************
* CheckEnemyCollision: Check enemy collision
* @author: Vivian Ngo
* @date: 08/05/18
* @return: player - player to check collision with enemies
***********************/
void CLevel::CheckEnemyCollision(std::shared_ptr<CSprite> player)
{
	for (unsigned int eList = 0; eList < m_pEnemyList.size(); ++eList)
	{
		if (player->IsCollidingWith(m_pEnemyList[eList]->GetSprite()))
		{
			//m_pEnemyList[eList]->GetSprite()->SetIsDead(true);
			//m_pPlayer->SetScore(m_pPlayer->GetScore() + m_pEnemyList[eList]->GetKillPoint());

			/*if (m_pPowerUpList[pList]->GetIsDead() == false)
			{*/


			m_pEnemyList[eList]->GetSprite()->SetHitEndTime();

			if (m_pEnemyList[eList]->GetSprite()->GetHitEndTime() - m_pEnemyList[eList]->GetSprite()->GetHitStartTime() > 2)
			{
				m_pPlayer->SetPlayerLives(m_pPlayer->GetPlayerLives() - 1);
				m_pEnemyList[eList]->GetSprite()->SetHitStartTime();

				m_pPlayer->GetSprite()->SetHitStartTime();
				m_pPlayer->GetSprite()->SetIsHit(true);

				m_pPlayer->GetSprite()->SetColour(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
			}
		}
	}
}

/***********************
* CheckEnemyCollision: Check enemy collision
* @author: Vivian Ngo
* @date: 08/05/18
* @return: player - player to check collision with enemies
***********************/
void CLevel::CheckPowerUpCollision(std::shared_ptr<CSprite> player)
{
	for (unsigned int pList = 0; pList < m_pPowerUpList.size(); ++pList)
	{
		if (player->IsCollidingWith(m_pPowerUpList[pList]->GetSprite()))
		{
			if (m_pPowerUpList[pList]->GetIsDead() == false)
			{
				m_pPowerUpList[pList]->SetIsDead(true);
				m_pPlayer->SetScore(m_pPlayer->GetScore() + m_pPowerUpList[pList]->GetPowPoint());
			}
		}
	}

}

/***********************
* GetIsGameOver: Gets variable that determines whether game is over or not
* @author: Vivian Ngo
* @date: 08/05/18
* @return: m_bGameOver
***********************/
bool CLevel::GetIsGameOver()
{
	return m_bGameOver;
}

/***********************
* SetGameOver: Sets the game as over
* @author: Vivian Ngo
* @date: 08/05/18
***********************/
void CLevel::SetGameOver()
{
	m_bGameOver = true;
}