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
// Author		: Vivian Ngo & Melanie Jacobson
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
	static void MouseScrollHold(int x, int y);
	static void ScollCallback(int button, int glutState, int xOffset, int yOffset);
	static void SpecialKeyPress(int key, int x, int y);
	static void SpecialKeyRelease(int key, int x, int y);

	//Times
	static void SetStartPressed();
	static void SetLastPressed();
	static float GetStartPressed();
	static float GetLastPressed();
	static float GetElapsedPressedTime();
	static void SetIsPressed(bool _isHit);
	static bool GetIsPressed();


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

	static float m_StartTime;
	static float m_EndTime;
	static bool m_isPressed;
};

