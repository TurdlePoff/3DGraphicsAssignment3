#pragma once
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: "Utils.h"
// Description	: Utils declaration file
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//


#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"

class Utils
{
public:
	static GLuint program;
	static GLuint Utils::programText;
	static GLuint Utils::programTextured;
	static unsigned int KeyState[255];
	static unsigned int MouseState[3];
	static float Utils::XYO;
	static float Utils::YYO;
};

