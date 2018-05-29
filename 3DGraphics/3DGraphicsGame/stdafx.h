#pragma once
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\soil\SOIL.h"

#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"

#include "Dependencies\FMOD\fmod.hpp"
#include "Utils.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <fstream>

static const unsigned int SCR_WIDTH = 800;
static const unsigned int SCR_HEIGHT = 800;

static const GLuint indices[] = {
	0, 1, 2, // First Triangle
	0, 2, 3 // Second Triangle
};

static const GLuint indicesPyramid[] = {
	4, 12, 5, // Side 1 
	6, 12, 7, // Side 2 
	8, 12, 9, // Side 3 
	10, 12, 11, // Side 4
	3, 2, 1, // Bottom Triangle 1 
	3, 1, 0, // Bottom Triangle 2
};

static const GLuint indicesCube[] = {
	// Front Face
	0, 1, 2,
	0, 2, 3,
	// Right Face
	4, 5, 6,
	4, 6, 7,
	// Back Face
	8, 9, 10,
	8, 10, 11,
	// Left Face
	12, 13, 14,
	12, 14, 15,
	// Top Face	

	16, 17, 18,
	16, 18, 19,
	// Bottom Face
	20, 21, 22,
	20, 22, 23,
};

static GLfloat verticesCube[216] = {
	// Positions // Colors // TexCoords
	-1.0f, 1.0f, 1.0f,		1.0f, 1.0f, 1.0f,		0.0f, 0.0f,
	1.0f, 1.0f, 1.0f,		1.0f, 1.0f, 0.0f,		1.0f, 0.0f,
	1.0f, -1.0f, 1.0f,		0.0f, 1.0f, 1.0f,		1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,		1.0f, 0.0f, 1.0f,		0.0f, 1.0f,
	// Right Face
	1.0f, 1.0f, 1.0f,		1.0f, 1.0f, 0.0f,		0.0f, 0.0f,
	1.0f, 1.0f, -1.0f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,
	1.0f, -1.0f, -1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,		0.0f, 1.0f, 1.0f,		0.0f, 1.0f,

	// Back Face
	1.0f, 1.0f, -1.0f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f,
	-1.0f, 1.0f, -1.0f,		1.0f, 0.0f, 0.0f,		1.0f, 0.0f,
	-1.0f, -1.0f, -1.0f,	0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
	1.0f, -1.0f, -1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,
	// Left Face
	-1.0f, 1.0f, -1.0f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
	-1.0f, 1.0f, 1.0f,		1.0f, 1.0f, 1.0f,		1.0f, 0.0f,
	-1.0f, -1.0f, 1.0f,		1.0f, 0.0f, 1.0f,		1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,	0.0f, 0.0f, 1.0f,		0.0f, 1.0f,

	// Top Face
	-1.0f, 1.0f, -1.0f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
	1.0f, 1.0f, -1.0f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,
	1.0f, 1.0f, 1.0f,		1.0f, 1.0f, 0.0f,		1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,		1.0f, 1.0f, 1.0f,		0.0f, 1.0f,
	// Bottom Face
	-1.0f, -1.0f, 1.0f,		1.0f, 0.0f, 1.0f,		0.0f, 0.0f,
	1.0f, -1.0f, 1.0f,		0.0f, 1.0f, 1.0f,		1.0f, 0.0f,
	1.0f, -1.0f, -1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,	0.0f, 0.0f, 1.0f,		0.0f, 1.0f,
};

//Enums of images within the game
enum EImage {
	BASKET, 
	LAPPLE,
	MAPPLE,
	RAPPLE,
	ROTTENAPPLE,
	BIRB1,
	BIRB2,
	HIVE, 
	BEEKEE,
	LIFEAPPLE,
	BG,
	STARTSCR,
	ENDSCR
};

enum EShape {
	TWOD,
	PYRAMID,
	CUBE
};

enum EMouse
{
	LCLICK, MCLICK, RCLICK
};

enum InputState {
	INPUT_FIRST_RELEASE, // First frame of Up state 
	INPUT_RELEASED, // Default State (Up) 
	INPUT_FIRST_PRESS, // First frame of Down state 
	INPUT_HOLD, // Key is held Down
};