//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: "AI.cpp"
// Description	: AI declaration file
// Author		: Vivian Ngo & Melanie Jacobson
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#include "AI.h"

//Initialise instance
CAIManager* CAIManager::s_pAIInstance = 0;

/***********************
* GetInstance: Gets the instance of the Singleton AI class
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
* @return: s_pAIInstance - Instance of the AI singleton class
***********************/
CAIManager * CAIManager::GetInstance()
{
	if (s_pAIInstance == 0)
	{
		s_pAIInstance = new CAIManager();
	}
	return s_pAIInstance;
}

/***********************
* DestroyInstance: Destroys AI manager Instance
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08 / 05 / 18
***********************/
void CAIManager::DestroyInstance()
{
	if (s_pAIInstance != 0) // If there is an instance of this class
	{
		//Delete the instance
		delete s_pAIInstance;
		s_pAIInstance = nullptr;
	}
}

/*
seek arrival pathfinding obstacle avoidance
*/

/***********************
* Seek: AI that seeks the player
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08 / 05 / 18
* @parameter: _player - player to search
* @parameter: _enemy - enemy to apply AI to
***********************/
void CAIManager::BouncyBall(std::shared_ptr<CEnemy> _enemy)
{
	_enemy->SetXPos(_enemy->GetXPos() + _enemy->GetSprite()->GetVel().x);
	_enemy->SetZPos(_enemy->GetZPos() + _enemy->GetSprite()->GetVel().z);

	//Calculate boundaries so enemy does not leave the game space
	CheckBoundaries(_enemy);
}

/***********************
* Seek: AI that seeks the player
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08 / 05 / 18
* @parameter: _player - player to search
* @parameter: _enemy - enemy to apply AI to
***********************/
void CAIManager::Seek(glm::vec3 _target, std::shared_ptr<CEnemy> _enemy)
{
	std::shared_ptr<CSprite> enS = _enemy->GetSprite();

	//Calculate a desire velocity so enemy knows not to directly travel to the player
	glm::vec3 desiredVelocity = _target - enS->GetPos();

	//Make sure desiredVelocity is not at 0 or normalize will break it
	if (glm::length(desiredVelocity) != 0.0f)
	{
		desiredVelocity = (glm::normalize(desiredVelocity) * m_maxVelocity);
	}
	else
	{
		//Set as 0 instead of normalizing it
		desiredVelocity = glm::vec3();
	}

	//Calculate a steer which will allow the AI to decrease 
	//the angle/distance slowly instead of heading straight towards the target
	glm::vec3 steer = desiredVelocity - enS->GetVel();
	steer /= m_mass;

	//Calculate final velocity by adding the steer to the current velocity
	glm::vec3 finalVelocity = enS->GetVel() + steer;

	//Make sure velocity does not exceed maximum velocity
	if (glm::length(finalVelocity) > m_maxVelocity)
	{
		finalVelocity = glm::normalize(finalVelocity) * m_maxVelocity;
	}

	enS->SetVel(finalVelocity); //Set final velocity to the AI's velocity

	//Calculate boundaries so enemy does not leave the game space
	CheckBoundaries(_enemy);

	//Apply to enemy
	enS->Translate(enS->GetPos() + enS->GetVel());
}

/***********************
* Flee: AI that flees the player
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08 / 05 / 18
* @parameter: _player - player to search
* @parameter: _enemy - enemy to apply AI to
***********************/
void CAIManager::Flee(glm::vec3 _target, std::shared_ptr<CEnemy> _enemy)
{
	std::shared_ptr<CSprite> enS = _enemy->GetSprite();
	
	glm::vec3 desiredVelocity = enS->GetPos() - _target;

	//If the player is within the radius of the enemy, evade
	if (glm::length(desiredVelocity) < m_radius)
	{
		//Calculate a desired velocity so enemy knows not to directly travel to the player
		if (glm::length(desiredVelocity) != 0.0f)
		{
			desiredVelocity = (glm::normalize(desiredVelocity) * m_maxVelocity);
		}
		else
		{
			//Set as 0 instead of normalizing it
			desiredVelocity = glm::vec3();
		}

		//Calculate a steer which will allow the AI to decrease 
		//the angle/distance slowly instead of heading straight away from the target
		glm::vec3 steer = desiredVelocity - enS->GetVel();
		steer /= m_mass;

		//Calculate final velocity by adding the steer to the current velocity
		glm::vec3 finalVelocity = enS->GetVel() + steer;

		//Make sure velocity does not exceed maximum velocity
		if (glm::length(finalVelocity) > m_maxVelocity)
		{
			finalVelocity = glm::normalize(finalVelocity) * m_maxVelocity;
		}

		enS->SetVel(finalVelocity); //Set final velocity to the AI's velocity

		//Calculate boundaries so enemy does not leave the game space
		CheckBoundaries(_enemy);

		//Apply to enemy
		enS->Translate(enS->GetPos() + enS->GetVel());
	}
	else
	{
		//If enemy is outside the evade zone, seek (so enemy doesnt stay still)
		Seek(_target, _enemy);
	}
}

/***********************
* Arrival: AI that slows down as it arrives at a destination
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08 / 05 / 18
* @parameter: _player - player to search
* @parameter: _enemy - enemy to apply AI to
***********************/
void CAIManager::Arrival(glm::vec3 _target, std::shared_ptr<CEnemy> _enemy)
{
	std::shared_ptr<CSprite> enS = _enemy->GetSprite();

	//Calculate a desired velocity so enemy knows not to directly travel to the player
	glm::vec3 desiredVelocity = _target - enS->GetPos();

	//Calculate a desire velocity so enemy knows not to directly travel away from the player
	if (glm::length(desiredVelocity) != 0.0f)
	{
		if (glm::length(desiredVelocity) < m_radius)
		{
			//Slow down gradually so AI arrives at player perfectly without overshooting
			desiredVelocity = glm::normalize(desiredVelocity) * m_maxVelocity 
						   * (glm::length(desiredVelocity) / m_radius);
		}
		else
		{
			//Speed to target at max speed if distance is higher than radius of target
			desiredVelocity = glm::normalize(desiredVelocity) * m_maxVelocity;
		}
	}
	else
	{
		//Set as 0 instead of normalizing it
		desiredVelocity = glm::vec3();
	}

	//Calculate a steer which will allow the AI to decrease 
	//the angle/distance slowly instead of heading straight towards the target
	glm::vec3 steer = desiredVelocity - enS->GetVel();
	steer /= m_mass;

	glm::vec3 finalVelocity = glm::vec3();

	//Calculate final velocity by adding the steer to the current velocity
 	finalVelocity = enS->GetVel() + steer;

	//Make sure velocity does not exceed maximum velocity
	if (glm::length(finalVelocity) > m_maxVelocity)
	{
		finalVelocity = glm::normalize(finalVelocity) * m_maxVelocity;
	}
	enS->SetVel(finalVelocity); //Set final velocity to the AI's velocity

	//Calculate boundaries so enemy does not leave the game space
	CheckBoundaries(_enemy);

	enS->Translate(enS->GetPos() + enS->GetVel());	//Apply to enemy
}

void CAIManager::ObstacleAvoidance(glm::vec3 _target, std::shared_ptr<CEnemy> _enemy)
{
	std::shared_ptr<CSprite> enS = _enemy->GetSprite();

	glm::vec3 ahead = enS->GetPos() + glm::normalize(enS->GetVel()) * m_maxSeeAhead;
	glm::vec3 ahead2 = enS->GetPos() + glm::normalize(enS->GetVel()) * (m_maxSeeAhead * 0.5f);
	glm::vec3 avoidance_force = ahead - _target;
	avoidance_force = normalize(avoidance_force) * m_maxAvoidanceForce;


}

/***********************
* Wander: AI that Wanders
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08 / 05 / 18
* @parameter: _player - player to search
* @parameter: _enemy - enemy to apply AI to
***********************/
void CAIManager::Wander(std::shared_ptr<CPlayer> _target, std::shared_ptr<CEnemy> _enemy)
{
	std::shared_ptr<CSprite> enS = _enemy->GetSprite();

}

/***********************
* CheckBoundaries: Checks the boundaries of the AI
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08 / 05 / 18
* @parameter: _enemy - enemy to apply AI to
***********************/
void CAIManager::CheckBoundaries(std::shared_ptr<CEnemy> _enemy)
{
	//If AI is horizontally out of boundaries, reverse the velocity (simulate bounce back)
	if ((_enemy->GetXPos() >= SCR_RIGHT) || (_enemy->GetXPos() <= SCR_LEFT))
	{
		_enemy->GetSprite()->SetVel(glm::vec3(
			_enemy->GetSprite()->GetVel().x * -1,
			_enemy->GetSprite()->GetVel().y,
			_enemy->GetSprite()->GetVel().z)
		);
	}

	//If AI is vertically out of boundaries, reverse the velocity (simulate bounce back)
	if ((_enemy->GetZPos() >= SCR_BOT) || (_enemy->GetZPos() <= SCR_TOP))
	{
		_enemy->GetSprite()->SetVel(glm::vec3(
			_enemy->GetSprite()->GetVel().x,
			_enemy->GetSprite()->GetVel().y,
			_enemy->GetSprite()->GetVel().z * -1)
		);
	}
}