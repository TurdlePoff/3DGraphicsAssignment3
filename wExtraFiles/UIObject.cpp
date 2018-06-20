//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: "UIObject.cpp"
// Description	: UIObject implementation file
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#include "UIObject.h"



UIObject::UIObject(EUIObject _uiType, EImage _sprImage, EShape _shape, std::string _text, glm::vec3 _pos)
{
	switch (_uiType)
	{
		case UI_TEXT:
		{
			m_text = CTextLabel(_text, "Resources/Fonts/bubble.TTF", glm::vec2(5.0f, 40.0f));
			break;
		}
		case UI_BOX:
		{
			break;
		}
		case UI_BUTTON:
		{
			m_text = CTextLabel(_text, "Resources/Fonts/bubble.TTF", glm::vec2(5.0f, 40.0f));
			ChangeSprite(_sprImage, _shape, _pos);
			break;
		}
		default:
		{

		}
	}
}

UIObject::~UIObject()
{
}

void UIObject::Draw()
{
}

void UIObject::Update()
{
}
