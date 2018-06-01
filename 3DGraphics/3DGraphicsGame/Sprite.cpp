#include "Sprite.h"
#include "Camera.h"
#include "Texture.h"

CSprite::CSprite(EImage _spriteType) :
m_eSpriteType(_spriteType),
m_vRotation(glm::vec3(0, 0, 0)),
m_vColour(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),
m_bIsDead(false),
m_shape(TWOD)
{
	switch (_spriteType)
	{
		case BASKET:
		{
			m_vPos = glm::vec3(0, -1.9f, -50);
			//m_vScale = glm::vec3(0.55f, 0.5f, 1);
			m_vScale = glm::vec3(2, 2, 2);
			m_vRotation = glm::vec3(-60.0f, 0.5f, 1);
			//m_shape = CUBE;
			m_filename = "Resources/images/basket.png";
			break;
		}
		case LAPPLE:
		{
			m_vPos = glm::vec3(-0.0f, 0.0f, -6.0f);
			m_vScale = glm::vec3(2, 2, 2);
			m_filename = "Resources/images/goodApple.png";
			m_shape = CUBE;
			break;
		}
		case MAPPLE:
		{
			m_vPos = glm::vec3(-0.0f, 0.0f, 0);
			m_vScale = glm::vec3(0.25f, 0.38f, 1);
			m_filename = "Resources/images/goodApple.png";
			break;
		}
		case RAPPLE:
		{
			m_vPos = glm::vec3(0.6F, 2.8f, 0.0f);
			m_vScale = glm::vec3(0.25f, 0.38f, 1);
			m_filename = "Resources/images/goodApple.png";

			break;
		}
		case ROTTENAPPLE:
		{
			m_vPos = glm::vec3(-5.0f, 0.0f, 4.0f);
			m_vScale = glm::vec3(2, 2, 2);
			m_filename = "Resources/images/rottenApple.png";
			m_shape = CUBE;

			break;
		}
		case BIRB1:
		{
			m_vPos = glm::vec3(-0.0f, 0.0f, 0);
			m_vScale = glm::vec3(2, 2, 2);
			m_filename = "Resources/images/birb1.png";
			m_shape = CUBE;
			break;
		}
		case BIRB2:
		{
			m_vPos = glm::vec3(0, 0, 0);
			m_vScale = glm::vec3(0.33f, 0.43f, 1);
			m_filename = "Resources/images/birb2.png";
			break;
		}
		case HIVE:
		{
			m_vPos = glm::vec3(0, 2.6f, 0);
			m_vScale = glm::vec3(0.5f, 0.7f, 1);
			m_filename = "Resources/images/hive.png";
			break;
		}
		case BEEKEE:
		{
			m_vPos = glm::vec3(0, -2.3f, 0);
			m_vScale = glm::vec3(0.5f, 0.7f, 1);
			m_filename = "Resources/images/beeKeeper.png";
			//GET DAT PIC
			break;
		}
		case LIFEAPPLE:
		{
			m_vPos = glm::vec3(-0.45f, -2.85f, 0); //-0.15
			m_vScale = glm::vec3(0.25f, 0.38f, 1);
			m_filename = "Resources/images/goodApple.png";
			break;
		}
		case BG:
		{
			m_vPos = glm::vec3(0, -10.0, 0);
			m_vScale = glm::vec3(10, 0.2f, 50);
			m_vRotation = glm::vec3(0.0f, 0.0f, 0.0);
			m_shape = CUBE;			
			m_filename = "Resources/images/treePortrait.jpg";
			break;
		}
		case STARTSCR:
		{
			m_vPos = glm::vec3(-5, 1, -10);
			m_vScale = glm::vec3(2, 2, 2);
			m_vRotation = glm::vec3(-60.0f, 0.5f, 1);
			m_shape = CUBE;
			m_filename = "Resources/images/startScreen.png";
			break;
		}
		case ENDSCR:
		{
			m_vPos = glm::vec3(0.06f, 1, -1);
			m_vScale = glm::vec3(6, 8, 1);
			m_filename = "Resources/images/endScreen.png";
			break;
		}
	}
	m_fWidth = m_vScale.x;
	m_fHeight = m_vScale.z;
	m_vTopLeft = glm::vec3(-((m_fWidth / 2) + m_vPos.x), (m_fHeight / 2) + m_vPos.z, 0.0f);
	m_fBotRight = glm::vec3((m_fWidth / 2) + m_vPos.x, -((m_fHeight / 2) + m_vPos.z), 0.0f);

	Texture::BindTexture(m_filename, m_fWidth, m_fHeight, m_vColour, m_vao, m_texture, m_shape);
}

CSprite::CSprite(glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scale, glm::vec4 _colour, float _width, float _height, const char* _filename) :
	m_vPos(_pos),
	m_vRotation(_rot),
	m_vScale(_scale),
	m_vColour(_colour),
	m_filename(_filename)
{
	m_fWidth = 1;
	m_fHeight = 1;

	m_bIsDead = false;
	m_vTopLeft = glm::vec3(-((m_fWidth / 2) + _pos.x), (m_fHeight / 2) + _pos.y, 0.0f);
	m_fBotRight = glm::vec3((m_fWidth / 2) + _pos.x, -((m_fHeight / 2)+_pos.y), 0.0f);
	m_shape = PYRAMID;;
	Texture::BindTexture(m_filename, m_fWidth, m_fHeight, m_vColour, m_vao, m_texture, m_shape);
}

void CSprite::Draw()
{
	if (m_bIsDead == false)
	{
		//CCamera::GetInstance()->SetMVP(m_vPos, m_vScale, m_vRotation);
		CCamera::GetInstance()->SetMVP(m_vPos, m_vScale, m_vRotation);
		Texture::Render(m_vao, m_texture);
	}
}

void CSprite::Update()
{
}

void CSprite::OnDestroy()
{

}

void CSprite::Translate(glm::vec3 Movement)
{
	m_vPos = Movement;
}

void CSprite::Rotate(glm::vec3 Rotation)
{
	m_vRotation = Rotation;
}

void CSprite::SetScale(glm::vec3 scale)
{
	m_vScale = scale;
}

glm::vec3 CSprite::GetPos()
{
	return m_vPos;
}

glm::vec3 CSprite::GetRot()
{
	return m_vRotation;
}

glm::vec3 CSprite::GetScale()
{
	return m_vScale;
}

float CSprite::GetWidth()
{
	return m_fWidth;
}

float CSprite::GetHeight()
{
	return m_fHeight;
}

float CSprite::GetAxisZ()
{
	return m_vPos.z;
}

glm::vec3 CSprite::GetTopLeft()
{
	return m_vTopLeft;
}

glm::vec3 CSprite::GetBotRight()
{
	return m_fBotRight;
}

bool CSprite::GetIsDead()
{
	return m_bIsDead;
}

void CSprite::SetIsDead(bool dead)
{
	m_bIsDead = dead;
}

bool CSprite::IsCollidingWith(std::shared_ptr<CSprite> _e2)//std::shared_ptr<CSprite> _e2)
{

	bool colliding = false;

	float e1 = this->GetHeight()*2;
	float e1X = this->GetPos().x* this->GetScale().x;
	float e1Y = this->GetPos().z* this->GetScale().z;

	float e2 = _e2->GetHeight()*2;
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

bool CSprite::TestGet()
{
	return true;
}