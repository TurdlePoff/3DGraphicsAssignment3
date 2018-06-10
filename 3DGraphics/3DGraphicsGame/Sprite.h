#pragma once
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: "Sprite.h"
// Description	: Sprite declaration file
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "stdafx.h" 
#include <memory>
#include "Model.h"
class CSprite
{
public:
	CSprite() {};

	CSprite(EImage _spriteType, EShape _shape, glm::vec3 _pos);
	/*CSprite(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, glm::vec4 Colour,
		float width, float height, const char* filename);*/

	~CSprite() {};

	void Draw();
	virtual void Update();
	void OnDestroy();
	void Translate(glm::vec3 Movement);
	void SetRotatation(glm::vec3 Rotation);
	void SetScale(glm::vec3 scale);
	void SetColour(glm::vec4 colour);
	void ChangeSprite(EImage _spriteType, EShape _shape, glm::vec3 pos);

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

	//Times
	void SetHitStartTime();
	void SetHitEndTime();
	float GetHitStartTime();
	float GetHitEndTime();
	float GetElapsedHitTime();
	void SetIsHit(bool _isHit);
	bool GetIsHit();
	bool IsCollidingWith(std::shared_ptr<CSprite> _e2);//std::shared_ptr<CSprite> e);
	//void RedMove(std::shared_ptr<CSprite> ree);

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

	float m_StartTime;
	float m_EndTime;
	bool m_isHit;

	GLuint m_vao;
	GLuint m_texture;
	const char* m_filename;

	EShape m_eShape;

	bool m_bIsDead;
};

#endif //__SPRITE_H__