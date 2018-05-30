//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: "main.cpp"
// Description	: main.cpp OpenGL Project
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//


//Do dying snes noise
//sleep and shrink


#include "stdafx.h"
#include "ShaderLoader.h"
#include "Texture.h"
#include "Input.h"
#include "SoundManager.h"
#include "Sprite.h"
#include "Camera.h"
#include "Scene.h"
#include "Level.h"
#include "SceneManager.h"
//#include <vld.h>


void Init();
void Render(void);
void Update();

std::unique_ptr<CSceneManager> scManager(CSceneManager::GetInstance());
std::unique_ptr<CSoundManager> sndManager(CSoundManager::GetInstance());
std::unique_ptr<CInput> InputFunc(CInput::GetInstance());

/***********************
* Init: Initialises items for the application
* @author: Vivian Ngo
* @date: 08/05/18
***********************/
void Init() 
{
	scManager->SetUpScenes();

	ShaderLoader sLoader;
	Utils::program = sLoader.CreateProgram("Shaders/VertexShader.txt", "Shaders/FragmentShader.txt");
	Utils::programTextured = sLoader.CreateProgram("Shaders/TextureVertexShader.txt", "Shaders/TextureFragmentShader.txt");
	
	sndManager->InitFmod();
	sndManager->LoadAudio();
	sndManager->InitSound();
}

/***********************
* Render: Renders objects of the application
* @author: Vivian Ngo
* @date: 08/05/18
***********************/
void Render(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(Utils::programTextured);

	scManager->RenderScene(scManager->GetCurrentScene());

	glUseProgram(0);

	glutSwapBuffers();
}

/***********************
* Update: Updates the application
* @author: Vivian Ngo
* @date: 08/05/18
***********************/
void Update()
{
	scManager->UpdateScene(scManager->GetCurrentScene());
	glutPostRedisplay(); //render function is called
}

/***********************
* Exit: Destroys all singleton instances of the application
* @author: Vivian Ngo
* @date: 08/05/18
***********************/
void Exit()
{
	CSceneManager::DestroyInstance();
	CCamera::DestroyInstance();
	CInput::DestroyInstance();
	CSoundManager::DestroyInstance();
}

/***********************
* main: main for OpenGL application
* @author: Vivian Ngo
* @date: 08/05/18
***********************/
int main(int argc, char **argv) 
{
	//SoundManager::InitSound();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(485, 50);
	glutInitWindowSize(SCR_WIDTH, SCR_HEIGHT);
	glutCreateWindow("3DProject");
	glClearColor(0.5, 0.0, 1.0, 1.0);	//clear blue

	glewInit();
	Init();

	glutKeyboardFunc(CInput::Keyboard_Down);
	glutKeyboardUpFunc(CInput::Keyboard_Up);
	glutMouseFunc(CInput::MouseClicked);
	glutPassiveMotionFunc(CInput::MousePassiveMovement);
	glutMotionFunc(CInput::MousePassiveMovement);
	glutMouseWheelFunc(CInput::ScollCallback);

	glutDisplayFunc(Render);
	glutIdleFunc(Update);

	glutCloseFunc(Exit);

	
	glutMainLoop();
	return 0;
}