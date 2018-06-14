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
// Author		: Vivian Ngo & Melanie Jacobson
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "stdafx.h" 
#include <memory>

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
	void SetVel(glm::vec3 vec) { m_vVel = vec; }
	void SetSteering(glm::vec3 ste) { m_vSte = ste; }


	glm::vec3 GetPos();
	glm::vec3 GetVel() { return m_vVel; }
	glm::vec3 GetSteering() { return m_vSte; }
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

private:
	EImage m_eSpriteType;

	glm::vec3 m_vPos;
	glm::vec3 m_vVel;
	glm::vec3 m_vSte;

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
	GLuint m_vbo;
	GLuint m_ebo;

	GLuint m_texture;
	const char* m_filename;

	EShape m_eShape;

	bool m_bIsDead;
};

#endif //__SPRITE_H__