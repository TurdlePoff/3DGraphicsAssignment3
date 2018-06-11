#pragma once
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: "stdafx.h"
// Description	: stdafx declaration file 
//				  Stores static variables to be used throughout the application
// Author		: Vivian Ngo & Melanie Jacobson
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

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

#include "Time.h"

static const unsigned int SCR_WIDTH = 900;
static const unsigned int SCR_HEIGHT = 800;

static const float SCR_TOP = -40.0f;
static const float SCR_BOT = 50.0f;
static const float SCR_LEFT = -45.0f;
static const float SCR_RIGHT = 45.0f;

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

// Positions // Colors // Tex Coords
static GLfloat vertices[] = {
	- 0.5f, 0.5f, 0.0f,		0.0f, 1.0f, 0.0f, 0.0f,		0.0f, 0.0f, // Top Left
	0.5f, 0.5f, 0.0f,		1.0f, 0.0f, 0.0f, 0.0f,		1.0f, 0.0f, // Top Right
	0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 0.0f, 0.0f,		1.0f, 1.0f, // Bottom Right
	- 0.5f, -0.5f, 0.0f,	0.0f, 0.0f, 1.0f, 0.0f,		0.0f, 1.0f, // Bottom Left
};

static GLfloat verticesPyramid[] = {
	// Positions // Colors // Tex Coords
	-1.0f, 0.0f, -1.0f,		1.0f, 1.0f, 0.0f, 0.0f,		0.0f, 1.0f, // 0 // Base
	1.0f, 0.0f, -1.0f,		1.0f, 0.0f, 0.0f, 0.0f,		1.0f, 1.0f, // 1
	1.0f, 0.0f, 1.0f,		0.0f, 1.0f, 0.0f, 0.0f,		1.0f, 0.0f, // 2
	-1.0f, 0.0f, 1.0f,		0.0f, 0.0f, 1.0f, 0.0f,		0.0f, 0.0f, // 3
	-1.0f, 0.0f, -1.0f,		1.0f, 1.0f, 0.0f, 0.0f,		0.0f, 1.0f, // 4 // Side 1
	-1.0f, 0.0f, 1.0f,		0.0f, 0.0f, 1.0f, 0.0f,		1.0f, 1.0f, // 5
	-1.0f, 0.0f, 1.0f,		0.0f, 0.0f, 1.0f, 0.0f,		0.0f, 1.0f, // 6 // Side 2
	1.0f, 0.0f, 1.0f,		0.0f, 1.0f, 0.0f, 0.0f,		1.0f, 1.0f, // 7
	1.0f, 0.0f, 1.0f,		0.0f, 1.0f, 0.0f, 0.0f,		0.0f, 1.0f, // 8 // Side 3
	1.0f, 0.0f, -1.0f,		1.0f, 0.0f, 0.0f, 0.0f,		1.0f, 1.0f, // 9
	1.0f, 0.0f, -1.0f,		1.0f, 0.0f, 0.0f, 0.0f,		0.0f, 1.0f, // 10 // Side 4
	-1.0f, 0.0f, -1.0f,		1.0f, 1.0f, 0.0f, 0.0f,		1.0f, 1.0f, // 11
	0.0f, 1.0f, 0.0f,		0.0f, 1.0f, 1.0f, 0.0f,		0.5f, 0.0f, // 12 // Top Point
};

static GLfloat verticesCube[216] = {
	// Positions // Colors // TexCoords
	-1.0f, 1.0f, 1.0f,		1.0f, 1.0f, 1.0f, 0.0f,		0.0f, 0.0f,
	1.0f, 1.0f, 1.0f,		1.0f, 1.0f, 0.0f, 0.0f,		1.0f, 0.0f,
	1.0f, -1.0f, 1.0f,		0.0f, 1.0f, 1.0f, 0.0f,		1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,		1.0f, 0.0f, 1.0f, 0.0f,		0.0f, 1.0f,
	// Right Face
	1.0f, 1.0f, 1.0f,		1.0f, 1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
	1.0f, 1.0f, -1.0f,		0.0f, 1.0f, 0.0f, 0.0f,		1.0f, 0.0f,
	1.0f, -1.0f, -1.0f,		0.0f, 0.0f, 0.0f, 0.0f,		1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,		0.0f, 1.0f, 1.0f, 0.0f,		0.0f, 1.0f,

	// Back Face
	1.0f, 1.0f, -1.0f,		0.0f, 1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
	-1.0f, 1.0f, -1.0f,		1.0f, 0.0f, 0.0f, 0.0f,		1.0f, 0.0f,
	-1.0f, -1.0f, -1.0f,	0.0f, 0.0f, 1.0f, 0.0f,		1.0f, 1.0f,
	1.0f, -1.0f, -1.0f,		0.0f, 0.0f, 0.0f, 0.0f,		0.0f, 1.0f,
	// Left Face
	-1.0f, 1.0f, -1.0f,		1.0f, 0.0f, 0.0f, 0.0f,		0.0f, 0.0f,
	-1.0f, 1.0f, 1.0f,		1.0f, 1.0f, 1.0f, 0.0f,		1.0f, 0.0f,
	-1.0f, -1.0f, 1.0f,		1.0f, 0.0f, 1.0f, 0.0f,		1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,	0.0f, 0.0f, 1.0f, 0.0f,		0.0f, 1.0f,

	// Top Face
	-1.0f, 1.0f, -1.0f,		1.0f, 0.0f, 0.0f, 0.0f,		0.0f, 0.0f,
	1.0f, 1.0f, -1.0f,		0.0f, 1.0f, 0.0f, 0.0f,		1.0f, 0.0f,
	1.0f, 1.0f, 1.0f,		1.0f, 1.0f, 0.0f, 0.0f,		1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,		1.0f, 1.0f, 1.0f, 0.0f,		0.0f, 1.0f,
	// Bottom Face
	-1.0f, -1.0f, 1.0f,		1.0f, 0.0f, 1.0f, 0.0f,		0.0f, 0.0f,
	1.0f, -1.0f, 1.0f,		0.0f, 1.0f, 1.0f, 0.0f,		1.0f, 0.0f,
	1.0f, -1.0f, -1.0f,		0.0f, 0.0f, 0.0f, 0.0f,		1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,	0.0f, 0.0f, 1.0f, 0.0f,		0.0f, 1.0f,
};

static GLfloat verticesCubeMap[] = {
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 0.0f,
	1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,

	// Right Face
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, 1.0f,

	// Back Face
	1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,

	// Left Face
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,

	// Left Face
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,

	// Top Face
	-1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,

	// Bottom Face
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
};

static GLfloat quadVertices[32] = {
	// Position				// Normals			// TexCoord
	-1.0f, 1.0f, 0.0f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f,
	1.0f, 1.0f, 0.0f,		0.0f, 0.0f, 1.0f,	1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,		0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
	-1.0f, -1.0f, 0.0f,		0.0f, 0.0f, 1.0f,	0.0f, 1.0f
};

//Enums of images within the game
enum EImage {
	INVAPPLE,
	BULLETDAMAPPLE,
	ROTTENAPPLE,
	BIRB1,
	BUBBLE,
	BG,
	STARTSCR,
	ENDSCR,
	SKYBOX
};

enum EShape {
	TWOD,
	PYRAMID,
	CUBE,
	CUBEMAP
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

enum EPowUps {
	POW_BULLET_DAMAGE,
	POW_INVINCIBLE,
	POW_1POINT
};

enum EBullets {
	BLT_NORM
};

enum EEnemyType {
	ENMY_NORM,
	ENMY_SEEK,
	ENMY_FLEE,
	ENMY_ARRIVAL,
	ENMY_WANDER,
	ENMY_PURSUIT,
	ENMY_EVADE,
	ENMY_PFOLLOW,
	ENMY_WALLFOLLOW
};

static const char* g_faces[] =
{
	"right.jpg",
	"left.jpg",
	"top.jpg",
	"bottom.jpg",
	"front.jpg",
	"back.jpg"
};