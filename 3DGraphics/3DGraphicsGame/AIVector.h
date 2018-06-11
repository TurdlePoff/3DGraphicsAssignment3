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
	CAIVector() { x = 0; z = 0; };
	CAIVector( float _x, float _z) : x(_x), z(_z) {};
	~CAIVector() {};
	
	CAIVector operator+(CAIVector const &_vec2)
	{ 
		CAIVector newVec;
		newVec.x = this->x + _vec2.x;
		newVec.z = this->z + _vec2.z;
		return newVec;
	};

	CAIVector( const CAIVector &p2) { x = p2.x; z = p2.z; }

	float x;
	float z;
};