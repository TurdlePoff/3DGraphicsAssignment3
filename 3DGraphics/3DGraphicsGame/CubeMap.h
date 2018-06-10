#pragma once
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: "CubeMap.h"
// Description	: CubeMap declaration file
// Author		: Vivian Ngo & Melanie Jacobson
// Mail			: vivian.ngo7572@mediadesign.school.nz
//
#include "stdafx.h"
#include "Camera.h"

class CCubeMap
{
public:
	CCubeMap();
	~CCubeMap();

	void Render();

private:
	GLuint m_vao;
	GLuint m_texture;

};

