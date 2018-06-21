#pragma once

#ifndef __CONTROL_H__
#define __CONTROL_H__
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2017 Media Design School
//
// File Name : control.h
// Description : control declaration file //with static functions
//				 Contains tecnical things to improve- generally aesthetics of applciation
// Author : Vivian Ngo
// Mail : vivian.ngo7572@mediadesignschool.com
//

#include <string>
#include <Windows.h>

enum KeyType
{
	UP, DOWN, LEFT, RIGHT, SPACE, EXIT, TAB, ENTER, NONE
};

class CControl
{
public:
	//Member functions
	static void Spc(char character, int size);	//Sets specified num spaces with specified character inputted
	static void ClearScreen(int _iX, int _iY);	//Clears screen from the coordinate input onwards
	static void GotoXY(int _iX, int _iY);		//Goes to the coordinates specified
	static void SetColour(WORD colour);			//Sets the colour of text to whatever is specified after the function is called
	static void SetStringInColour(std::string text, WORD colour);
	static KeyType KeyDetection();						//Detects and returns Key being pressed
	static char ChooseOption(std::string question, int numOptions);
	static void PrintHorLine(int size, bool edge);
	static int CheckNumInput(std::string question, int start, int end);
	static void ChangeWindowSize(int w, int h);
};

#endif //__CONTROL_H__