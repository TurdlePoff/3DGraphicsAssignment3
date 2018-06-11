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
	void Seek(glm::vec3 _target, std::shared_ptr<CEnemy> _enemy);
	void Flee(glm::vec3 _target, std::shared_ptr<CEnemy>  _enemy);
	void Arrival(glm::vec3 _target, std::shared_ptr<CEnemy>  _enemy);
	void ObstacleAvoidance(std::vector<glm::vec3> _obstList, std::shared_ptr<CEnemy>  _enemy);
	void Wander(std::shared_ptr<CPlayer> _target, std::shared_ptr<CEnemy> _enemy);
	
	
	void CheckBoundaries(std::shared_ptr<CEnemy>  _enemy);
	bool FindClosestPoint();

private:
	static CAIManager* s_pAIInstance;
	CAIManager() {};

	float m_maxVelocity = 0.2f;
	float m_maxforce = 1.0f;
	float m_mass = 100.0f;
	float m_radius = 50.0f;
	float m_maxSeeAhead = 20.0f;
	float m_avoidanceForce = 1.0f;
	float m_maxAvoidanceForce = 5.0f;
};

