#pragma once
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

