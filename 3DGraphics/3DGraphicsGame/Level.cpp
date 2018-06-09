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
#include "AI.h"

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
	AddToSpriteList(m_pPlayer->GetSprite());

	//Mouse position text
	std::shared_ptr<CTextLabel> xText(new CTextLabel("x: ", "Resources/Fonts/bubble.TTF", glm::vec2(SCR_WIDTH - 200.0f, 40.0f)));
	xText->SetScale(0.3f);
	xText->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	AddToTextList(xText);

	std::shared_ptr<CTextLabel> yText(new CTextLabel("y: ", "Resources/Fonts/bubble.TTF", glm::vec2(SCR_WIDTH - 200.0f, 60.0f)));
	yText->SetScale(0.3f);
	yText->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	AddToTextList(yText);

	if (m_iLevelNumber == 10)	//IF THE LEVEL IS THE START SCREEN
	{
		player->Translate(glm::vec3(0.0f, player->GetPos().y, 0.0f));

		std::shared_ptr<CTextLabel> titleText1(new CTextLabel("BUBBLETRON", "Resources/Fonts/bubble.TTF", glm::vec2((SCR_WIDTH / 2) - 110.0f - 100.0f, SCR_HEIGHT / 2 + 200)));
		titleText1->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
		AddToTextList(titleText1);

		std::shared_ptr<CTextLabel> startText(new CTextLabel("START", "Resources/Fonts/bubble.TTF", glm::vec2((SCR_WIDTH / 2) - 110.0f - 5.0f, ((SCR_HEIGHT / 2)))));
		startText->SetColor(glm::vec3(0.0f, 0.0f, 1.0f));
		AddToTextList(startText);

		std::shared_ptr<CTextLabel> multiText(new CTextLabel("MULTIPLAYER", "Resources/Fonts/bubble.TTF", glm::vec2((SCR_WIDTH / 2) - 110.0f - 120.0f, ((SCR_HEIGHT / 2) - 100))));
		multiText->SetColor(glm::vec3(0.0f, 0.0f, 1.0f));
		AddToTextList(multiText);

		std::shared_ptr<CTextLabel> instrText(new CTextLabel("INSTRUCTIONS", "Resources/Fonts/bubble.TTF", glm::vec2((SCR_WIDTH / 2) - 110.0f - 130.0f, ((SCR_HEIGHT / 2) - 200))));
		instrText->SetColor(glm::vec3(0.0f, 0.0f, 1.0f));
		AddToTextList(instrText);
	}
	else if (m_iLevelNumber == 11)	//IF THE LEVEL IS THE INSTRUCTIONS SCREEN
	{
		player->Translate(glm::vec3(0.0f, player->GetPos().y, 0.0f));

		std::shared_ptr<CTextLabel> titleText1(new CTextLabel("INSTRUCTIONS", "Resources/Fonts/bubble.TTF", glm::vec2((SCR_WIDTH / 2) - 110.0f - 130.0f, SCR_HEIGHT / 2 + 200)));
		titleText1->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
		AddToTextList(titleText1);

		std::shared_ptr<CTextLabel> startText(new CTextLabel("W H Y", "Resources/Fonts/bubble.TTF", glm::vec2((SCR_WIDTH / 2) - 110.0f - 5.0f, ((SCR_HEIGHT / 2)))));
		startText->SetColor(glm::vec3(0.0f, 1.0f, 0.3f));
		AddToTextList(startText);

		std::shared_ptr<CTextLabel> exText(new CTextLabel("BACK", "Resources/Fonts/bubble.TTF", glm::vec2((SCR_WIDTH / 2) - 110.0f + 25.0f, ((SCR_HEIGHT / 2) - 300))));
		exText->SetColor(glm::vec3(0.0f, 0.0f, 1.0f));
		AddToTextList(exText);

	}
	else if (m_iLevelNumber == 12)	//IF THE LEVEL IS THE GAME OVER SCREEN
	{
		std::shared_ptr<CTextLabel> scoreText(new CTextLabel("Score: ", "Resources/Fonts/bubble.TTF", glm::vec2((SCR_WIDTH / 2) - 100.0f, (SCR_HEIGHT / 2) - 100.0f)));
		scoreText->SetScale(0.8f);
		scoreText->SetColor(glm::vec3(0.6f, 0.1f, 0.3f));
		AddToTextList(scoreText);

		sc = std::to_string(GetPlayer()->GetScore());
		std::shared_ptr<CTextLabel> actualScoreText(new CTextLabel(sc, "Resources/Fonts/bubble.TTF", glm::vec2((SCR_WIDTH / 2) - 20.0f + 100.0f, (SCR_HEIGHT / 2) - 100.0f)));
		actualScoreText->SetScale(0.8f);
		actualScoreText->SetColor(glm::vec3(0.6f, 0.1f, 0.3f));
		AddToTextList(actualScoreText);

		std::shared_ptr<CTextLabel> gameOver(new CTextLabel("GAME OVER", "Resources/Fonts/bubble.TTF", glm::vec2((SCR_WIDTH / 2) - 150.0f - 20.0f, SCR_HEIGHT / 2)));//SCR_HEIGHT - 200.0f));
		gameOver->SetScale(1.0f);
		gameOver->SetColor(glm::vec3(0.0f, 1.0f, 0.0f));
		AddToTextList(gameOver);

		std::shared_ptr<CTextLabel> mmText(new CTextLabel("MAIN MENU", "Resources/Fonts/bubble.TTF", glm::vec2((SCR_WIDTH / 2) - 150.0f - 20.0f, ((SCR_HEIGHT / 2) - 300))));
		mmText->SetColor(glm::vec3(0.0f, 0.0f, 1.0f));
		AddToTextList(mmText);
	}
	else if (m_iLevelNumber == 1)	//IF LEVEL 1
	{
		std::shared_ptr<CSprite> lAppleSprite1(new CSprite(LAPPLE, CUBE, glm::vec3(10.0f, 0.0f, 0.0)));
		std::shared_ptr<CPowerUp> goodApple(new CPowerUp(lAppleSprite1, 1, POW_1POINT));
		//lAppleSprite1->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
		std::shared_ptr<CSprite> mAppleSprite1(new CSprite(ROTTENAPPLE, CUBE, glm::vec3(-10.0f, 0.0f, 0.0)));
		std::shared_ptr<CEnemy> enemyBad(new CEnemy(mAppleSprite1, ENMY_NORM));

		AddToPowerUpList(goodApple);
		AddToEnemyList(enemyBad);

		std::string score = "1000";
		std::shared_ptr<CTextLabel> scoreText(new CTextLabel("Score: ", "Resources/Fonts/bubble.TTF", glm::vec2(5.0f, 40.0f)));
		scoreText->SetScale(0.3f);
		scoreText->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
		AddToTextList(scoreText);

		sc = std::to_string(m_pPlayer->GetScore());
		std::shared_ptr<CTextLabel> actualScoreText(new CTextLabel(sc, "Resources/Fonts/bubble.TTF", glm::vec2(80.0f, 40.0f)));
		actualScoreText->SetScale(0.3f);
		actualScoreText->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
		AddToTextList(actualScoreText);

		std::shared_ptr<CTextLabel> livesText(new CTextLabel("Lives: ", "Resources/Fonts/bubble.TTF", glm::vec2(5.0, 10.0f)));
		livesText->SetScale(0.3f);
		livesText->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
		AddToTextList(livesText);

		std::string playerLives = std::to_string(m_pPlayer->GetPlayerLives());
		std::shared_ptr<CTextLabel> actualLivesText(new CTextLabel(playerLives, "Resources/Fonts/bubble.TTF", glm::vec2(80.0f, 10.0f)));
		actualLivesText->SetScale(0.3f);
		actualLivesText->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
		AddToTextList(actualLivesText);
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

	for (unsigned int bList = 0; bList < m_pPlayerBulletList.size(); ++bList)
	{
		m_pPlayerBulletList[bList]->GetSprite()->Draw();
	}
}

/***********************
* Update: Updates all items in the game
* @author: Vivian Ngo
* @date: 08/05/18
***********************/
void CLevel::Update()
{
	m_pTextList[0]->SetText(std::to_string(Utils::mouseX));
	m_pTextList[1]->SetText(std::to_string(Utils::mouseY));
	//If the player is currently in level 0 or 2
	
	if (m_iLevelNumber == 1)	//If the player is currently in level 1
	{
		std::shared_ptr<CSprite> player = (GetPlayer()->GetSprite());

		MovePlayer(player);

		if (Utils::SpaceState[' '] == INPUT_HOLD)
		{
			std::shared_ptr<CBullet> newBullet = GetPlayer()->CreateBullet();
			newBullet->Draw();
			newBullet->Update();
			AddToBulletList(GetPlayer()->CreateBullet());
			Utils::SpaceState[' '] = INPUT_RELEASED;
		}

		for (unsigned int bList = 0; bList < m_pPlayerBulletList.size(); ++bList)
		{
			m_pPlayerBulletList[bList]->Update();
		}

		if(m_pEnemyList.size() != 0)
			CAIManager::GetInstance()->BouncyBall(m_pEnemyList[0]);

		CheckEnemyCollision(player);
		CheckPowerUpCollision(player);

		m_pTextList[3]->SetText(std::to_string(GetPlayer()->GetScore()));
		m_pTextList[5]->SetText(std::to_string(GetPlayer()->GetPlayerLives()));

		CheckBulletEnemyCollision();
		CheckBulletBoundaries();

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

		if (m_pPlayer->GetPlayerLives() <= 0 || m_pEnemyList.size() == 0)
		{
			m_pPlayer->GetSprite()->Translate(glm::vec3(0.0f, player->GetPos().y, 0.0f));
			m_pPlayer->GetSprite()->SetRotatation(glm::vec3(0.0f, 0.0f, 0.0f));
			m_pPlayer->GetSprite()->SetColour(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

			CSceneManager::GetInstance()->SwitchScene(12);
		}
	}
	

	CheckButtonHovered();
	HandleStartScreenButtons();

	if (CSceneManager::GetInstance()->GetCurrentSceneNumber() == 12)
	{
		m_pTextList[3]->SetText(std::to_string(GetPlayer()->GetScore()));
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
		if (player->GetPos().z < -40.0f) //z boundary - If player is further than -10 z then prevent them from moving any further
			m_fZ = 0;
		else
			m_fZ -= val;

		player->SetRotatation(glm::vec3(0.0f, 0.0f, 0.0f));
	}
	else if (Utils::KeyState[(unsigned int)'s'] == INPUT_HOLD || Utils::KeyState[(unsigned int)'S'] == INPUT_HOLD)
	{
		if (player->GetPos().z > 50.0f) //z boundary - If player is further than 10 z then prevent them from moving any further
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
			//Set if making enemy that dies via touch

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
* CheckEnemyBulletCollision: Check Enemy Bullet Collision
* @author: Vivian Ngo
* @date: 08/05/18
* @return: player - player to check collision with enemies
***********************/
void CLevel::CheckBulletEnemyCollision()
{
	
	for (unsigned int bList = 0; bList < m_pPlayerBulletList.size(); ++bList)
	{
		for (unsigned int eList = 0; eList < m_pEnemyList.size(); ++eList)
		{
			if (!m_pEnemyList[eList]->GetIsHit())
			{
				if (m_pPlayerBulletList[bList]->GetSprite()->IsCollidingWith(m_pEnemyList[eList]->GetSprite()))
				{
					m_pEnemyList[eList]->SetIsHit(true);
					m_pEnemyList[eList]->SetIsDead(true);

					GetPlayer()->SetScore(m_pPlayer->GetScore() + m_pEnemyList[eList]->GetGainPoint());
				
					m_pEnemyList.erase(m_pEnemyList.begin() + eList);

					m_pPlayerBulletList.erase(m_pPlayerBulletList.begin() + bList);

					SetRemainingEnemies(GetRemainingEnemies() - 1);
				}
			}
		}
	}
}

/***********************
* CheckBulletBoundaries: Check Bullet Boundaries
* @author: Vivian Ngo
* @date: 08/05/18
***********************/
void CLevel::CheckBulletBoundaries()
{
	for (unsigned int bList = 0; bList < m_pPlayerBulletList.size(); ++bList)
	{
		if (m_pPlayerBulletList[bList]->GetSprite()->GetPos().x < SCR_LEFT ||
			m_pPlayerBulletList[bList]->GetSprite()->GetPos().x > SCR_RIGHT || 
			m_pPlayerBulletList[bList]->GetSprite()->GetPos().z < SCR_TOP ||
			m_pPlayerBulletList[bList]->GetSprite()->GetPos().z > SCR_BOT)
		{
			m_pPlayerBulletList.erase(m_pPlayerBulletList.begin() + bList);
		}
	}
}

/***********************
* IsMouseOverButton: Detects if mouse is hovering over a button location
* @author: Vivian Ngo
* @date: 08/05/18
* @parameter: text - text button being hovered
* @return: true if button is hovered
***********************/
bool CLevel::IsMouseOverButton(std::shared_ptr<CTextLabel> text)
{
	if (Utils::mouseX > (text->GetPosition().x)
		&& Utils::mouseX < (text->GetPosition().x + text->GetTextWidth()) &&
		abs(SCR_HEIGHT - Utils::mouseY) > ((text->GetPosition().y))
		&& abs(SCR_HEIGHT - Utils::mouseY) < ((text->GetPosition().y + text->GetTextHeight())))
	{
		text->SetIsHovering(true);
		return true;
	}
	else
	{
		text->SetIsHovering(false);
		return false;
	}
}

/***********************
* IsMouseOverButton: Detects if mouse is hovering over a button location
* @author: Vivian Ngo
* @date: 08/05/18
* @return: m_bGameOver
***********************/
void CLevel::CheckButtonHovered()
{
	if (m_iLevelNumber == 10) //Start Screen
	{
		for (unsigned int i = 3; i <= 5; ++i)
		{
			if (IsMouseOverButton(m_pTextList[i]))//Hover over all hoverable text in start screen
			{
				m_pTextList[i]->SetColor(glm::vec3(0.0f, 1.0f, 0.3f));
			}
			else
			{
				m_pTextList[i]->SetColor(glm::vec3(0.0f, 0.0f, 1.0f));
			}
		}
	}
	else if (m_iLevelNumber == 11) //Instructions
	{
		if (IsMouseOverButton(m_pTextList[4]))//Hover over return button
		{
			m_pTextList[4]->SetColor(glm::vec3(0.0f, 1.0f, 0.3f));
		}
		else
		{
			m_pTextList[4]->SetColor(glm::vec3(0.0f, 0.0f, 1.0f));
		}
	}
	else if (m_iLevelNumber == 12) //Game over screen
	{
		if (IsMouseOverButton(m_pTextList[5]))//Hover over return button
		{
			m_pTextList[5]->SetColor(glm::vec3(0.0f, 1.0f, 0.3f));
		}
		else
		{
			m_pTextList[5]->SetColor(glm::vec3(0.0f, 0.0f, 1.0f));
		}
	}
}

/***********************
* HandleStartScreenButtons: Decides what to do with the buttons in the starting screen
* @author: Vivian Ngo
* @date: 08/05/18
* @return: m_bGameOver
***********************/
void CLevel::HandleStartScreenButtons()
{
	if (m_iLevelNumber == 10) //Start screen
	{
		if (m_pTextList[3]->GetIsHovering())//Start game
		{
			if (Utils::MouseState[0] == INPUT_HOLD)
			{
				GetPlayer()->ResetPlayerStats();
				CSceneManager::GetInstance()->SwitchScene(1);
			}
		}
		
		if(m_pTextList[4]->GetIsHovering())//Multiplayer
		{
			if (Utils::MouseState[0] == INPUT_HOLD)
			{
				//Multiplayer
			}
		}

		if (m_pTextList[5]->GetIsHovering())//Instructions
		{
			if (Utils::MouseState[0] == INPUT_HOLD)
			{
				//Instructions
				CSceneManager::GetInstance()->SwitchScene(11);
			}
		}
	}
	else if(m_iLevelNumber == 11) //Instructions
	{
		if (m_pTextList[4]->GetIsHovering())
		{
			if (Utils::MouseState[0] == INPUT_HOLD)
			{
				//Multiplayer
				CSceneManager::GetInstance()->SwitchScene(10);		//RETURN TO MAIN MENU FROM INSTRUCTIONS
			}
		}
	}
	else if (m_iLevelNumber == 12) //Ending/Game over screen
	{
		if (m_pTextList[5]->GetIsHovering())//Returning to start screen
		{
			if (Utils::MouseState[0] == INPUT_HOLD)
			{
				//Multiplayer
				CSceneManager::GetInstance()->ResetLevels(GetPlayer());
				CSceneManager::GetInstance()->SwitchScene(10);		//RETURN TO MAIN MENU
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