#pragma once
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: "PowerUp.h"
// Description	: PowerUp declaration file
// Author		: Vivian Ngo & Melanie Jacobson
// Mail			: vivian.ngo7572@mediadesign.school.nz
//


#include "Player.h"
#include "Enemy.h"

//
//struct location
//{
//	float x;
//	float y;
//};

class CAIManager
{
public:
	static CAIManager* GetInstance();
	static void DestroyInstance();
	~CAIManager() {};

	void BouncyBall(std::shared_ptr<CEnemy> _enemy);
	void Seek(std::shared_ptr<CPlayer> _player, std::shared_ptr<CEnemy> _enemy);
	void Flee(std::shared_ptr<CPlayer> _player, std::shared_ptr<CEnemy>  _enemy);
	void Arrival(std::shared_ptr<CPlayer> _player, std::shared_ptr<CEnemy>  _enemy);

	void Wander(std::shared_ptr<CPlayer> _player, std::shared_ptr<CEnemy> _enemy);

private:
	static CAIManager* s_pAIInstance;
	CAIManager() {};

	float m_maxVelocity = 0.1f;
	float m_maxforce = 1.0f;
	float m_mass = 100.0f;
	float m_radius = 50.0f;

};

