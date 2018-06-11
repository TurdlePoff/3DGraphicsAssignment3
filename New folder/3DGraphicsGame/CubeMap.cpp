#include "CubeMap.h"
#include "Texture.h"

/***********************
* CCubeMap: CCubeMap constructor - initialises the cubemap
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
***********************/
CCubeMap::CCubeMap()
{
	Texture::BindTexture("", 0.0f, 0.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), m_vao, m_texture, CUBEMAP);
}

/***********************
* CCubeMap: CCubeMap destructor
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
***********************/
CCubeMap::~CCubeMap(){}

/***********************
* Render: CCubeMap Render - Renders cubemap onto screen
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
***********************/
void CCubeMap::Render()
{
	CCamera::GetInstance()->SetMVP(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0F));
	Texture::Render(m_vao, m_texture);
}
