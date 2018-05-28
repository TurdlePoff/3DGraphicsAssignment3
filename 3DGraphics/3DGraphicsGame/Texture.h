#pragma once
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: "Texture.cpp"
// Description	: Texture implementation file
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#include "stdafx.h"

class Texture
{
public:

	Texture();
	~Texture();

	static void BindTexture(const char* filename, float _fHalfWidth, float _fHalfHeight, glm::vec4 _colour, GLuint& vao, GLuint& texture, EShape _shape);
	static void Render(GLuint vao, GLuint texture);

	GLuint tex;

private:
};
