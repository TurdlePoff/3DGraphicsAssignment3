#pragma once

#include "stdafx.h"
#include <memory>

class CCamera
{
public:
	static CCamera* GetInstance();
	static void DestroyInstance();

	void SetMVP(glm::vec3 _trans, glm::vec3 _scale, glm::vec3 _rot);

	void SetCamFront(glm::vec3 _cFront);
	void SetCamPos(glm::vec3 _cPos);
	void SetCamUp(glm::vec3 _cUp);
	void SetCamSpeed(float _cSpeed);

	glm::vec3 GetCamFront();
	glm::vec3 GetCamPos();
	glm::vec3 GetCamUp();
	float GetCamSpeed();

private:
	static CCamera* s_pCameraInstance;
	CCamera();
	
	glm::mat4 view;
	glm::mat4 projection;

	glm::vec3 cameraPos = glm::vec3(0.0f, 5.0f, 50.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -10.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget); //pointing in reverse of where it is pointing
	glm::vec3 cameraRight = glm::normalize(glm::cross(cameraUp, cameraDirection));

	float cameraSpeed = 0.05f;

	GLfloat currentTime;
};

