//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: "Utils.cpp"
// Description	: Utils implementation file
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#include "Utils.h"

GLuint Utils::program;
GLuint Utils::programText;
GLuint Utils::programTextured;
GLuint Utils::programLight;

unsigned int Utils::KeyState[255];
unsigned int Utils::MouseState[3];


float Utils::mouseX = 0;
float Utils::mouseY = 0;

float Utils::testX = 0;
float Utils::testY = 0;
float Utils::testZ = 0;