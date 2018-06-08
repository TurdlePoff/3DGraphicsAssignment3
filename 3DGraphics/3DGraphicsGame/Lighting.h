#pragma once
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: "Lighting.h"
// Description	: Lighting declaration file 
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#include "stdafx.h"

class CLighting
{
public:
	~CLighting() {};
	static CLighting* GetInstance();
	static void DestroyInstance();

	static void SetUpLighting();

private:
	static CLighting* s_pLightingInstance;
	CLighting() {};

};

