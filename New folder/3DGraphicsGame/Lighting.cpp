//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: "Lighting.cpp"
// Description	: Lighting implementation file 
// Author		: Vivian Ngo & Melanie Jacobson
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#include "Lighting.h"

CLighting* CLighting::s_pLightingInstance = 0;

/***********************
* GetInstance: Gets scene manager Instance
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08 / 05 / 18
* return s_pSoundInstance - instance of sound manager
***********************/
CLighting* CLighting::GetInstance()
{
	if (s_pLightingInstance == 0)
	{
		s_pLightingInstance = new CLighting();
	}
	return s_pLightingInstance;
}

/***********************
* DestroyInstance: Destroys scene manager Instance
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08 / 05 / 18
***********************/
void CLighting::DestroyInstance()
{
	if (s_pLightingInstance != 0) // If there is an instance of this class
	{
		//Delete the instance
		delete s_pLightingInstance;
		s_pLightingInstance = nullptr;
	}
}

void CLighting::SetUpLighting()
{
	unsigned int lightVAO;
	GLuint vbo;
	//GLuint ebo;

	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	// we only need to bind to the VBO, the container's VBO's data already contains the correct data.
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// set the vertex attributes (only position data for our lamp)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}
