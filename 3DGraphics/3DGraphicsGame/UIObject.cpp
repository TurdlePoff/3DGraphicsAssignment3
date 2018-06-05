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



UIObject::UIObject()
{
}


UIObject::~UIObject()
{
}

void UIObject::DrawUI()
{
}

void UIObject::UpdateUI()
{
}

void UIObject::SetPosition(glm::vec2 newPos)
{
	m_position = newPos;
}

void UIObject::SetRotate(float newRotation)
{
	m_rotation = newRotation;
}
