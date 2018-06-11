#pragma once
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: "AIVector.h"
// Description	: AIVector declaration file
// Author		: Vivian Ngo & Melanie Jacobson
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

class CAIVector
{
public:
	CAIVector( float _x, float _z) : x(_x), z(_z) {};
	~CAIVector() {};
	
	CAIVector operator+(const CAIVector &_vec2) { x = _vec2.x; z = _vec2.z; };

	CAIVector( const CAIVector &p2) { x = p2.x; z = p2.z; }

	float x;
	float z;
};