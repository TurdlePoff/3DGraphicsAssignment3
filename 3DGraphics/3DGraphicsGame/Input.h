#pragma once

//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: "Input.cpp"
// Description	: Input declaration file
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//


#include "stdafx.h"

class CInput
{
public: 
	static CInput* GetInstance();
	static void DestroyInstance();

	~CInput();

	static void Keyboard_Down(unsigned char keyPressed, int x, int y);
	static void Keyboard_Up(unsigned char keyPressed, int x, int y);
	static void MouseClicked(int buttonPressed, int glutState, int x, int y);
	static void MousePassiveMovement(int x, int y);
	static void ScollCallback(int button, int glutState, int xOffset, int yOffset);

	//void InputGlutFunctions();
	//Glutspecialfunctions
private:
	CInput() {};
	static CInput* s_pInputInstance;
	static GLfloat MouseSensitivity;
	static GLfloat Yaw;
	static GLfloat Pitch;
	static GLfloat Roll;
	static GLfloat LastX;
	static GLfloat LastY;
	static float LastScrollY;

	static bool FirstMouse;
	float m_fX;
	float m_fY;
};

