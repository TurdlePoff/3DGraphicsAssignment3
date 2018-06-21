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
// Author		: Vivian Ngo & Melanie Jacobson
// Mail			: vivian.ngo7572@mediadesign.school.nz
//


#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <WS2tcpip.h>
#include <string>
#include <strstream>

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
	static GLuint programText;
	static GLuint programTextured;
	static GLuint programLight;
	static GLuint programCMap;

	static unsigned int SpecKeyState[4];
	static unsigned int KeyState[255];
	static unsigned int SpaceState[255];

	static unsigned int MouseState[3];
	static float mouseX;
	static float mouseY;

	static float testX;
	static float testY;
	static float testZ;
};

