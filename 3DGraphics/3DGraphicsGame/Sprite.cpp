//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: "Sprite.cpp"
// Description	: Sprite implementation file
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#include "Sprite.h"
#include "Camera.h"
#include "Texture.h"

/***********************
* CSprite: CSprite constructor
* @author: Vivian Ngo
* @date: 08/05/18
* @parameter: _spriteType - type of the sprite
***********************/
CSprite::CSprite(EImage _spriteType, EShape _shape, glm::vec3 _pos)
{
	ChangeSprite(_spriteType, _shape, _pos);

	//Initialise initial times
	SetHitStartTime();
	SetHitEndTime();
}

/***********************
* Draw: Draaw the sprite
* @author: Vivian Ngo
* @date: 08/05/18
***********************/
void CSprite::Draw()
{
	CCamera::GetInstance()->SetMVP(m_vPos, m_vScale, m_vRotation);
	Texture::Render(m_vao, m_texture);
}

/***********************
* Update: Update the sprite
* @author: Vivian Ngo
* @date: 08/05/18
***********************/
void CSprite::Update()
{
}

/***********************
* OnDestroy: When destroying sprite
* @author: Vivian Ngo
* @date: 08/05/18
***********************/
void CSprite::OnDestroy()
{

}

/***********************
* Translate: Translate the sprite
* @author: Vivian Ngo
* @date: 08/05/18
* @parameter: Movement - move sprite
***********************/
void CSprite::Translate(glm::vec3 Movement)
{
	m_vPos = Movement;
}

/***********************
* SetRotatation: SetRotatation of sprite
* @author: Vivian Ngo
* @date: 08/05/18
* @parameter: Rotation - new rotation of sprite
***********************/
void CSprite::SetRotatation(glm::vec3 Rotation)
{
	m_vRotation = Rotation;
}

/***********************
* SetScale: Set Scale of the sprite
* @author: Vivian Ngo
* @date: 08/05/18
* @parameter: scale - scale sprite
***********************/
void CSprite::SetScale(glm::vec3 scale)
{
	m_vScale = scale;
}

void CSprite::SetColour(glm::vec4 colour)
{
	Texture::BindTexture(m_filename, m_fWidth, m_fHeight, colour, m_vao, m_texture, m_eShape);
}

void CSprite::ChangeSprite(EImage _spriteType, EShape _shape, glm::vec3 _pos)
{
	m_vRotation = glm::vec3(0.0f, 0.0f, 0.0f);
	switch (_spriteType)
	{
		case INVAPPLE:
		{
			m_filename = "Resources/images/rainbowApple.png";
			m_vScale = glm::vec3(2.0f, 2.0f, 2.0f);
			break;
		}
		case BULLETDAMAPPLE:
		{
			m_filename = "Resources/images/goodApple.png";
			m_vScale = glm::vec3(2.0f, 2.0f, 2.0f);
			break;
		}
		case ROTTENAPPLE:
		{
			m_filename = "Resources/images/rottenApple.png";
			m_vScale = glm::vec3(2.0f, 2.0f, 2.0f);
			break;
		}
		case BIRB1:
		{
			m_filename = "Resources/images/birb1.png";
			m_vScale = glm::vec3(2.0f, 2.0f, 2.0f);

			break;
		}
		case BUBBLE:
		{
			m_filename = "Resources/images/bubble.png";
			m_vScale = glm::vec3(2.0f, 2.0f, 2.0f);

			break;
		}
		case BG:
		{
			m_filename = "Resources/images/floorBg.jpg";
			m_vScale = glm::vec3(10, 0.2f, 50);
			break;
		}
		case STARTSCR:
		{
			m_filename = "Resources/images/bubblesBg.jpg";
			m_vScale = glm::vec3(15, 0.2f, 60);
			m_vRotation = glm::vec3(0.0f, 0.0f, 180.0f);
			break;
		}
		case ENDSCR:
		{
			m_filename = "Resources/images/bubblesBg.jpg";
			m_vScale = glm::vec3(15, 0.2f, 60);
			m_vRotation = glm::vec3(0.0f, 0.0f, 180.0f);
			break;
		}
		case SKYBOX:
		{			
			m_filename = " ";
			m_vScale = glm::vec3(10.0f, 10.0f, 10.0f);
			m_vRotation = glm::vec3(0.0f, 0.0f, 180.0f);
			break;
		}
	}

	m_vPos = _pos;
	m_eShape = _shape;

	m_vColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_bIsDead = false;
	m_fWidth = m_vScale.x;
	m_fHeight = m_vScale.z;
	m_vTopLeft = glm::vec3(-((m_fWidth / 2) + m_vPos.x), (m_fHeight / 2) + m_vPos.z, 0.0f);
	m_fBotRight = glm::vec3((m_fWidth / 2) + m_vPos.x, -((m_fHeight / 2) + m_vPos.z), 0.0f);

	Texture::BindTexture(m_filename, m_fWidth, m_fHeight, m_vColour, m_vao, m_texture, m_eShape);
}

/***********************
* GetPos: Get Pos of the sprite
* @author: Vivian Ngo
* @date: 08/05/18
* @return: m_vPos - Get pos of sprite
***********************/
glm::vec3 CSprite::GetPos()
{
	return m_vPos;
}

/***********************
* GetRot: Get rotation of the sprite
* @author: Vivian Ngo
* @date: 08/05/18
* @return: m_vRotation - Get rotation of sprite
***********************/
glm::vec3 CSprite::GetRot()
{
	return m_vRotation;
}

/***********************
* GetScale: Get scale of the sprite
* @author: Vivian Ngo
* @date: 08/05/18
* @return: m_vScale - Get scale of sprite
***********************/
glm::vec3 CSprite::GetScale()
{
	return m_vScale;
}

/***********************
* GetWidth: Get Width of the sprite
* @author: Vivian Ngo
* @date: 08/05/18
* @return: m_fWidth - Get width of sprite
***********************/
float CSprite::GetWidth()
{
	return m_fWidth;
}

/***********************
* GetHeight: Get Height of the sprite
* @author: Vivian Ngo
* @date: 08/05/18
* @return: m_fHeight - Get Height of sprite
***********************/
float CSprite::GetHeight()
{
	return m_fHeight;
}

/***********************
* GetAxisZ: Get z pos of the sprite
* @author: Vivian Ngo
* @date: 08/05/18
* @return: m_vPos.z - Get position z
***********************/
float CSprite::GetAxisZ()
{
	return m_vPos.z;
}

/***********************
* GetTopLeft: Get top left pos of the sprite
* @author: Vivian Ngo
* @date: 08/05/18
* @return: m_vTopLeft - Top left position
***********************/
glm::vec3 CSprite::GetTopLeft()
{
	return m_vTopLeft;
}

/***********************
* GetBotRight: Get bot right pos of the sprite
* @author: Vivian Ngo
* @date: 08/05/18
* @return: m_fBotRight - bot right position
***********************/
glm::vec3 CSprite::GetBotRight()
{
	return m_fBotRight;
}

/***********************
* GetIsDead: Check if sprite is dead
* @author: Vivian Ngo
* @date: 08/05/18
* @return: m_bIsDead - variable stating whether sprite is dead or not / not shown on screen
***********************/
bool CSprite::GetIsDead()
{
	return m_bIsDead;
}

/***********************
* SetIsDead: Set sprite is dead
* @author: Vivian Ngo
* @date: 08/05/18
* @parameter: dead - set is dead or not dead
***********************/
void CSprite::SetIsDead(bool dead)
{
	m_bIsDead = dead;
}

/***********************
* IsCollidingWith: Checks if sprite is colliding with another sprite
* @author: Vivian Ngo
* @date: 08/05/18
* @parameter: _e2 - The other sprite being compared to this one
* @return: colliding - bool whether the current sprite is colliding with another
***********************/
bool CSprite::IsCollidingWith(std::shared_ptr<CSprite> _e2)//std::shared_ptr<CSprite> _e2)
{

	bool colliding = false;

	float e1 = this->GetHeight() * 2;
	float e1X = this->GetPos().x* this->GetScale().x;
	float e1Y = this->GetPos().z* this->GetScale().z;

	float e2 = _e2->GetHeight() * 2;
	float e2X = _e2->GetPos().x * _e2->GetScale().x;
	float e2Y = _e2->GetPos().z * _e2->GetScale().z;

	float collision = e1 + e2;

	float actualdistance = (sqrt(pow(abs(e2X - e1X), 2) + pow(abs(e2Y - e1Y), 2)));

	if (actualdistance < collision)
	{
		colliding = true;
	}

	return colliding;
}

/***********************
* SetHitStartTime: Sets start time of when collided with
* @author: Vivian Ngo
* @date: 08/05/18
***********************/
void CSprite::SetHitStartTime()
{
	m_StartTime = CTime::GetCurTimeSecs();
}

/***********************
* SetHitEndTime: Sets latest time of when collided with
* @author: Vivian Ngo
* @date: 08/05/18
***********************/
void CSprite::SetHitEndTime()
{
	m_EndTime = CTime::GetCurTimeSecs();
}

/***********************
* SetHitEndTime: Sets latest time of when collided with
* @author: Vivian Ngo
* @date: 08/05/18
* @return: m_StartTime - time of when enemy was first collided
***********************/
float CSprite::GetHitStartTime()
{
	return m_StartTime;
}

/***********************
* SetHitEndTime: Sets latest time of when collided with
* @author: Vivian Ngo
* @date: 08/05/18
***********************/
float CSprite::GetHitEndTime()
{
	return m_EndTime;
}

/***********************
* GetElapsedHitTime: Gets the elapsed hit time from when the enemy was first collided to now
* @author: Vivian Ngo
* @date: 08/05/18
***********************/
float CSprite::GetElapsedHitTime()
{
	return m_EndTime - m_StartTime;
}

/***********************
* SetHit: Set sprite is hit
* @author: Vivian Ngo
* @date: 08/05/18
* @parameter: _isHit - Set whether sprite entity is hit or not
***********************/
void CSprite::SetIsHit(bool _isHit)
{
	m_isHit = _isHit;
}

/***********************
* GetIsHit: Get sprite is hit
* @author: Vivian Ngo
* @date: 08/05/18
* @return: m_isHit - Gets whether sprite entity is hit or not
***********************/
bool CSprite::GetIsHit()
{
	return m_isHit;
}
