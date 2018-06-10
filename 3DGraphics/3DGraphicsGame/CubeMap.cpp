#include "CubeMap.h"

CCubeMap::CCubeMap()
{
	//GLuint vbo;
	//GLuint ebo;

	//// Generating objects and texture
	//glGenVertexArrays(1, &m_vao);
	//glGenBuffers(1, &vbo);
	//glGenBuffers(1, &ebo);
	//// Bind objects and texture
	//glBindVertexArray(m_vao);
	//glBindBuffer(GL_ARRAY_BUFFER, vbo);


	//glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCubeMap), verticesCubeMap, GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(indicesCube), indicesCube, GL_STATIC_DRAW);

	//glGenTextures(1, &m_texture);
	//glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	//glEnableVertexAttribArray(0);

	//// Set Image via SOIL library
	//int width, height;
	//unsigned char* image = NULL;

	//for (GLuint i = 0; i < 6; i++)
	//{
	//	std::string fullPathName = "Resources/images/CubeMap/";

	//	fullPathName.append(g_faces[i]);
	//	image = SOIL_load_image(fullPathName.c_str(), &width, &height, 0,
	//		SOIL_LOAD_RGB);
	//	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB,
	//		width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	//	SOIL_free_image_data(image);
	//}

	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	//glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	//glBindTexture(GL_TEXTURE_CUBE_MAP, 0);


	GLuint vbo;
	GLuint ebo;

	// Set Image via SOIL library
	int width, height;
	unsigned char* image = NULL;

	for (GLuint i = 0; i < 6; i++)
	{
		std::string fullPathName = "Resources/images/CubeMap/";

		fullPathName.append(g_faces[i]);
		image = SOIL_load_image(fullPathName.c_str(), &width, &height, 0,
			SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB,
			width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	//Generate Mipmap
	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

	// Clear texture 2D
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	// Generating objects and texture
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	// Bind objects and texture
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);


	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCubeMap), verticesCubeMap, GL_STATIC_DRAW);


	glVertexAttribPointer(
		0, // Layout location on vertex shader
		3, // 3 float components (eg position)
		GL_FLOAT, // Type of data
		GL_FALSE, // Data normalized?
		9 * sizeof(GLfloat), //Stride of the single vertex(pos + color + uv)
		(GLvoid*)0); // Offset
	glVertexAttribPointer(
		1, // Layout location on vertex shader
		4, // 4 float components (eg position)
		GL_FLOAT, // Type of data
		GL_FALSE, // Data normalized?
		9 * sizeof(GLfloat), //Stride of the single vertex(pos + color + uv)
		(GLvoid*)(3 * sizeof(GLfloat))); // Offset
	glVertexAttribPointer(
		2, // Layout location on vertex shader
		2, // 2 float components (eg position)
		GL_FLOAT, // Type of data
		GL_FALSE, // Data normalized?
		9 * sizeof(GLfloat), //Stride of the single vertex(pos + color + uv)
		(GLvoid*)(7 * sizeof(GLfloat))); // Offset
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(indicesCube), indicesCube, GL_STATIC_DRAW);

}


CCubeMap::~CCubeMap()
{
}

void CCubeMap::Render()
{
	glDepthMask(GL_FALSE);
	glUseProgram(Utils::programCMap);

	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	glDisable(GL_CULL_FACE);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);
	glUniform1i(glGetUniformLocation(Utils::programCMap, "cubeSampler"), 0);
	glm::mat4 model = glm::scale(glm::mat4(), glm::vec3(1000.0f, 1000.0f, 1000.0f));
	glm::mat4 MVP = CCamera::GetInstance()->GetProjection() *  CCamera::GetInstance()->GetView() * model;
	glUniformMatrix4fv(glGetUniformLocation(Utils::programCMap, "MVP"), 1, GL_FALSE, glm::value_ptr(MVP));

	glBindVertexArray(m_vao);

	//glDrawArrays(GL_TRIANGLES, 0, 36);
	glDrawElements(GL_TRIANGLES, sizeof(indicesCube) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
	//glDrawElements(GL_TRIANGLES, sizeof(indicesCube) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
	//glUseProgram(0);

	glDepthMask(GL_TRUE);
	glDisable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}
