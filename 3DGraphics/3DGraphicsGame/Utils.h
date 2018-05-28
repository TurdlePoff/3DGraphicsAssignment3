
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"

#pragma once
class Utils
{
public:
	static GLuint program;
	static GLuint Utils::programText;
	static GLuint Utils::programTextured;
	static unsigned int KeyState[255];
	static unsigned int MouseState[3];
};

