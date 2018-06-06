#pragma once
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: "UIObject.h"
// Description	: UIObject declaration file
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#include "stdafx.h"
#include "TextLabel.h"
#include "Texture.h"
#include "Sprite.h"

class UIObject : public CSprite
{
public:
	UIObject() {};
	UIObject(EUIObject _uiType, EImage _sprImage, EShape _shape, std::string _text, glm::vec3 _pos);
	~UIObject();

	virtual void Draw();
	virtual void Update();

private:
	CTextLabel m_text;
	CSprite m_UISprite;

	glm::vec2 m_position;
	float m_rotation;
};

