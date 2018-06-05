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

class UIObject
{
public:
	UIObject();
	~UIObject();

	virtual void DrawUI();
	virtual void UpdateUI();

	void SetPosition(glm::vec2 newPos);
	void SetRotate(float newRotation);

private:
	glm::vec2 m_position;
	float m_rotation;
};

