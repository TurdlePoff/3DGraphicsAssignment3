#pragma once
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name : Sprite.h
// Description : Sprite declaration file;
// Author : Vivian Ngo
// Mail : vivian.ngo7572@mediadesignschool.com
//

#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "stdafx.h"
#include <memory>

class CSprite
{
public:
	CSprite() {};

	CSprite(EImage spriteType);
	CSprite(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, glm::vec4 Colour,
		float width, float height, const char* filename);

	~CSprite() {};

	void Draw();
	void Update();
	void OnDestroy();

	void Translate(glm::vec3 Movement);
	void Rotate(glm::vec3 Rotation);
	void SetScale(glm::vec3 scale);

	glm::vec3 GetPos();
	glm::vec3 GetRot();
	glm::vec3 GetScale();

	float GetWidth();
	float GetHeight();
	float GetAxisZ();

	glm::vec3 GetTopLeft();
	glm::vec3 GetBotRight();

	bool GetIsDead();
	void SetIsDead(bool dead);

	bool IsCollidingWith(std::shared_ptr<CSprite> _e2);//std::shared_ptr<CSprite> e);

	bool TestGet();

private:
	EImage m_eSpriteType;

	glm::vec3 m_vPos;
	glm::vec3 m_vRotation;
	glm::vec3 m_vScale;
	glm::vec4 m_vColour;

	glm::vec3 m_vTopLeft;
	glm::vec3 m_fBotRight;

	float m_fWidth;
	float m_fHeight;

	GLuint m_vao;
	GLuint m_texture;
	const char* m_filename;

	EShape m_shape;

	bool m_bIsDead;
};

#endif //__SPRITE_H__