#pragma once
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: "Camera.h"
// Description	: Camera declaration file
// Author		: Vivian Ngo & Melanie Jacobson
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#include "stdafx.h"
#include <memory>

class CCamera
{
public:
	static CCamera* GetInstance();
	static void DestroyInstance();

	void SetMVP(glm::vec3 _trans, glm::vec3 _scale, glm::vec3 _rot);

	static void SetFOV(float _fov);
	static float GetFOV();
	static void SetCamFront(glm::vec3 _cFront);
	void SetCamPos(glm::vec3 _cPos);
	void SetCamUp(glm::vec3 _cUp);
	void SetCamSpeed(float _cSpeed);
	void CameraMovement(float _camSpeed);

	glm::vec3 GetCamFront();
	glm::vec3 GetCamPos();
	glm::vec3 GetCamUp();
	float GetCamSpeed();
	glm::mat4 GetMVP() { return MVP; }
	glm::mat4 GetProjection() { return projection; }
	glm::mat4 GetView() { return view; }
	void SetRotation(glm::mat4 rot) {ROT = rot; }

private:
	static CCamera* s_pCameraInstance;
	CCamera();

	static glm::vec3 cameraFront;
	static float m_fov;

	glm::mat4 view;
	glm::mat4 projection;

	glm::vec3 cameraPos = glm::vec3(0.0f, -10.0f, 90.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);

	glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget); //pointing in reverse of where it is pointing
	glm::vec3 cameraRight = glm::normalize(glm::cross(cameraUp, cameraDirection));

	float cameraSpeed = 0.05f;

	GLfloat currentTime;
	static glm::mat4 MVP;
	glm::mat4 ROT = glm::rotate(glm::mat4(), glm::radians(40.0f), glm::vec3(1.0f, 0.0f, 0.0f));

};

