#pragma once

#if !defined(__UTILS_H__)
#define __UTILS_H__

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
// Author		: Vivian Ngo & Melanie Jacobson
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

// Library Includes
#include <WS2tcpip.h>
#include <string>
#include <strstream>

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"

#define VALIDATE(a) if (!a) return (false)

namespace {
	std::string ToString(sockaddr_in _sockAddress)
	{
		//INET_ADDRSTRLEN - maximum length for IPv4 addresses
		char _pcAddress[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &_sockAddress.sin_addr, _pcAddress, INET_ADDRSTRLEN);

		std::string _strAddress = _pcAddress;
		std::string _strPort = std::to_string(ntohs(_sockAddress.sin_port));
		std::string _strAddressPort = _strAddress + ':' + _strPort;

		return _strAddressPort;
	}
}

template<typename T>
std::string ToString(const T& _value)
{
	std::strstream theStream;
	theStream << _value << std::ends;
	return (theStream.str());
}

class Utils
{
public:
	static GLuint program;
	static GLuint Utils::programText;
	static GLuint Utils::programTextured;
	static GLuint Utils::programLight;
	static GLuint Utils::programCMap;

	static unsigned int SpecKeyState[4];
	static unsigned int KeyState[255];
	static unsigned int SpaceState[255];

	static unsigned int MouseState[3];
	static float Utils::mouseX;
	static float Utils::mouseY;

	static float testX;
	static float testY;
	static float testZ;

	

};

#endif    // __UTILS_H__