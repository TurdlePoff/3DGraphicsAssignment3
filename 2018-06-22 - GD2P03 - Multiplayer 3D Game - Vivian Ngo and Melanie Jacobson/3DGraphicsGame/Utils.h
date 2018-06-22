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


#include "stdafx.h"

#include <WS2tcpip.h>
#include <string>
#include <strstream>
#include <sstream>

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

	std::string Vec3ToString(glm::vec3& _vector)
	{
		std::strstream theStream;
		theStream << _vector.x << " " << _vector.y << " " << _vector.z << std::ends;
		return (theStream.str());
	}

	std::string Vec4ToString(glm::vec4& _vector4)
	{
		std::strstream theStream;
		theStream << _vector4.r << " " << _vector4.g << " " << _vector4.b << " " << _vector4.a << std::ends;
		return (theStream.str());
	}

	glm::vec3 ToVec3(std::string _vectorString)
	{
		std::stringstream ss(_vectorString);
		float x, y, z;
		ss >> x >> y >> z;
		return glm::vec3{ x, y, z };
	}

	glm::vec4 ToVec4(std::string _vectorString)
	{
		std::stringstream ss(_vectorString);
		float r, g, b, a;
		ss >> r >> g >> b >> a;
		return glm::vec4{ r, g, b, a };
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

