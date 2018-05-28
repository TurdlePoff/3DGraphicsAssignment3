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
