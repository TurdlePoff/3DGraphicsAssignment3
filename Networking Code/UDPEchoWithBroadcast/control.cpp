// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name	: "Control.cpp"
// Description	: Implementation file for Control
//
//					Control Class contains all extra functions 
//					that are used within the program that makes it
//					look better and is not necessarilly 'game logic'.
//
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#include <string>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <iomanip>
#include <cstdlib>

#include "control.h"

using namespace std;

/**
* Function for creating a specified number of repeats of
*	whatever character the user specifies
* @author: Vivian Ngo
* @date: 07/03/18
* @parameter: character - the character the user wishes to repeat
* @parameter: size - the amount of repeats the user wants to make
*/
void CControl::Spc(char character, int size)
{
	std::cout << std::setfill(character) << std::setw(size) << character;
}

/***********************
* ClearScreen: Function for clearing the command line screen
* @author: Vivian Ngo
* @date: 07/03/18
* @parameter: _iX - X coordinate of where to start clearing the screen
* @parameter: _iY - Y coordinate of where to start clearing the screen
***********************/
void CControl::ClearScreen(int _iX, int _iY)
{
	COORD coordScreen = { (short)_iX, (short)_iY };
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(hConsole, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	FillConsoleOutputCharacter(hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	SetConsoleCursorPosition(hConsole, coordScreen);
}


/***********************
* GotoXY: Function for going to a certain location on the command line
* @author: Vivian Ngo
* @date: 07/03/18
* @parameter: _iX - X coordinate of where to place cursor
* @parameter: _iY - Y coordinate of where to place cursor
***********************/
void CControl::GotoXY(int _iX, int _iY)
{
	COORD point;
	point.X = _iX;
	point.Y = _iY;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}

/***********************
* SetColour: Function for setting colour of text
* @author: Vivian Ngo
* @date: 07/03/18
* @parameter: color - number of the colour you would like to set the text
*     Colours:
*     0 = Black      |   4 = Red            |   8 = DarkGray     |   12 = LightRed
*     1 = Blue       |   5 = Magenta        |   9 = LightBlue    |   13 = LightMagenta
*     2 = Green      |   6 = Yellow         |   10 = LightGreen  |   14 = LightYellow
*     3 = Cyan       |   7 = LightGray      |   11 = LightCyan   |   15 = White
***********************/
void CControl::SetColour(WORD colour)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colour);
}

/***********************
* SetStringInColour: Sets a given string into a given colour
* @author: Vivian Ngo
* @date: 07/03/18
* @parameter: text - text to change colour into
* @parameter: color - number of the colour you would like to set the text
*     Colours:
*     0 = Black      |   4 = Red            |   8 = DarkGray     |   12 = LightRed
*     1 = Blue       |   5 = Magenta        |   9 = LightBlue    |   13 = LightMagenta
*     2 = Green      |   6 = Yellow         |   10 = LightGreen  |   14 = LightYellow
*     3 = Cyan       |   7 = LightGray      |   11 = LightCyan   |   15 = White
***********************/
void CControl::SetStringInColour(std::string text, WORD colour)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colour);
	std::cout << text;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //Change back to normal text colour
}

/***********************
* KeyDetection: Function that detects keyboard input
* @author: Vivian Ngo
* @date: 07/03/18
* @return: enum of key pressed
***********************/
KeyType CControl::KeyDetection()
{
	int iKeyPress = _getch();
	if (iKeyPress != 0 && iKeyPress != 0xE0)
	{
		if (iKeyPress == 32)		//If SPACE is pressed
		{
			return SPACE;
		}
		else if (iKeyPress == 27)	//If ESC is pressed
		{
			return EXIT;
		}
		else if (iKeyPress == 9)	//If TAB is pressed
		{
			return TAB;
		}
		else if (iKeyPress == 13)	//If ENTER is pressed
		{
			return ENTER;
		}
	}
	else
	{
		// Arrow Key Codes.
		const int g_kiDownArrow = 80;
		const int g_kiUpArrow = 72;
		const int g_kiLeftArrow = 75;
		const int g_kiRightArrow = 77;

		int iCheckForArrowKey = _getch();
		switch (iCheckForArrowKey)
		{
			case g_kiUpArrow:
			{
				return UP;
				break;
			}
			case g_kiDownArrow:
			{
				return DOWN;
				break;
			}
			case g_kiLeftArrow:
			{
				return LEFT;
				break;
			}
			case g_kiRightArrow:
			{
				return RIGHT;
				break;
			}
			default:
			{
				return NONE;
				break;
			}
		}
	}
	return NONE;
}

/***********************
* ChooseOption: Allows player to choose an option and prompts a question if a wrong input is entered
*					//Allows a single character input
* @author: Vivian Ngo
* @date: 14/03/18
* @parameter: question - string containing the question to ask player if a wrong input is entered
* @parameter: numOptions - the number of options to select from
* @return: valid option inputted by player
************************/
char CControl::ChooseOption(std::string question, int numOptions)
{
	//Receive player input
	char option = _getch();
	//Recieve numbers depending on how many options are given
	while (option < 49 || option >(49 + numOptions - 1))
	{
		cout << endl;
		cout << question;
		option = _getch();
	}
	cout << option << endl << endl;
	return option;
}

/***********************
* CheckNumInput: Check the numbers (more than one character) the user has entered. 
*				 Keep asking for new input if invalid.
* @author: Vivian Ngo
* @date: 05/04/17
* @parameter: question - string containing the question to ask player if a wrong input is entered
* @parameter: numZeros - number of zeros at the back of a number to be restricted
* @return: valid option inputted by player
************************/
int CControl::CheckNumInput(std::string question, int start, int end)
{
	std::string input;
	//Checks if user input is valid (fully numeric)
	while (true)
	{
		bool isValid = true;
		string inputArg = "";

		//Gets string input but also checks whether string includes a space or not.
		getline(cin, input);

		//For each char in the string 'input' 
		//Check if char is not a number (ASCII)
		if (input.length() > 6)
		{
			inputArg = " Input must not exceed 1";
			for (int i = 0; i < 6; ++i)
				inputArg += "0";
			isValid = false;
		}

		//Method checking if input is an end line
		if (input == "")
		{
			inputArg = " Please enter a valid input: ";
			isValid = false;
		}

		for (char c : input)
		{
			if (c < 48 || c > 57)
			{
				//if any char is invalid, make isValid false
				inputArg = " Please enter a valid input: ";
				isValid = false;
			}
		}

		//If input is valid, break loop and return the input
		if (isValid)
		{
			if(stoi(input) > start && stoi(input) < end)
				break;
			else
			{
				inputArg = (stoi(input) <= start ? " Number is too low: " : inputArg);
				inputArg = (stoi(input) >= end ? " Number is too high: " : inputArg);

				//Otherwise, print arguments
				cout << inputArg;
				//cout << question;
			}
		}
		else
		{
			//Otherwise, print arguments
			cout << inputArg;
			//cout << question;
		}
	}

	//Returns and converts string into int
	return stoi(input);
}

void CControl::ChangeWindowSize(int w, int h)
{
	HWND hwnd = GetConsoleWindow();
	if (hwnd != NULL)
	{				 //  position	 size
		RECT rect;
		int width, height;
		if (GetWindowRect(hwnd, &rect))
		{
			width = rect.right - rect.left;
			height = rect.bottom - rect.top;
		}
		MoveWindow(hwnd, width / 2, height / 8, w, h, TRUE);  //Set console position to center
	}
}

/***********************
* PrintHorLine: Prints horizontal lines depending on board width
* @author: Vivian Ngo
* @date: 26/03/18
* @parameter: size - number of elements on that board
* @parameter: edge - bool for whether to print an edge line or mid line
* @return: valid option inputted by player
************************/
void CControl::PrintHorLine(int size, bool edge)
{
	cout << (edge ? "+" : "|");
	for (int i = 0; i < size-1; ++i)
		cout << "-";
	cout << (edge ? "+" : "|");
}
