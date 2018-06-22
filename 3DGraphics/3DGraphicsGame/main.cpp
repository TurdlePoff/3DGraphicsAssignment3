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
// Author		: Vivian Ngo & Melanie Jacobson
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

//$(ProjectDir)\Dependencies\vld\2.5\include
//$(ProjectDir)\Dependencies\vld\2.5\lib
#pragma comment(lib, "Ws2_32.lib")

#include "stdafx.h"
#include "ShaderLoader.h"
#include "Input.h"
#include "SoundManager.h"
#include "Camera.h"
#include "Scene.h"
#include "Level.h"
#include "SceneManager.h"
#include "NetworkingManager.h"
#include "AI.h"
#include "Lighting.h"
#include "CubeMap.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vld.h>

void Init();
void Render(void);
void Update();

std::unique_ptr<CSceneManager> scManager(CSceneManager::GetInstance());
std::unique_ptr<CSoundManager> sndManager(CSoundManager::GetInstance());
std::unique_ptr<CInput> InputFunc(CInput::GetInstance());

/***********************
* Init: Initialises items for the application
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
***********************/
void Init() 
{
	srand((unsigned int)time(NULL));

	//Set up the scenes of the game
	scManager->SetUpScenes();

	//Create programs with shaderloader
	ShaderLoader sLoader;
	Utils::program = sLoader.CreateProgram("Resources/Shaders/VertexShader.txt", "Resources/Shaders/FragmentShader.txt");
	Utils::programTextured = sLoader.CreateProgram("Resources/Shaders/TextureVertexShader.txt", "Resources/Shaders/TextureFragmentShader.txt");
	Utils::programCMap = sLoader.CreateProgram("Resources/Shaders/CMapVertexShader.txt", "Resources/Shaders/CMapFragmentShader.txt");

	//Initialise fmod, load the audio and play it
	sndManager->InitFmod();
	sndManager->LoadAudio();
	//sndManager->InitBackground();
}

/***********************
* Render: Renders objects of the application
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
***********************/
void Render(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Render everything from the current scene
	scManager->RenderScene(scManager->GetCurrentScene());
	glutSwapBuffers();
}

/***********************
* Update: Updates the application
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
***********************/
void Update()
{
	//Update everything in the current scene
	CTime::GetInstance()->SetUpdateEndTime();

	if (CTime::GetUpdateEndTime() - CTime::GetUpdateStartTime() > 0.01f)
	{
		scManager->UpdateScene(scManager->GetCurrentScene());
		CTime::GetInstance()->SetUpdateStartTime();
	}
	glutPostRedisplay(); //render function is called
}

/***********************
* Exit: Destroys all singleton instances of the application
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
***********************/
void Exit()
{
	CSceneManager::DestroyInstance();
	CCamera::DestroyInstance();
	CInput::DestroyInstance();
	CSoundManager::DestroyInstance();
	CTime::DestroyInstance();
	CAIManager::DestroyInstance();
	CLighting::DestroyInstance();
	NetworkingManager::DestroyInstance();

}

/***********************
* main: main for OpenGL application
* @author: Vivian Ngo & Melanie Jacobson
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

	//Take in inputs
	glutKeyboardFunc(CInput::Keyboard_Down);
	glutKeyboardUpFunc(CInput::Keyboard_Up);
	glutMouseFunc(CInput::MouseClicked);
	glutPassiveMotionFunc(CInput::MousePassiveMovement);
	glutMotionFunc(CInput::MouseScrollHold);
	glutMouseWheelFunc(CInput::ScollCallback);
	glutSpecialFunc(CInput::SpecialKeyPress);
	glutSpecialUpFunc(CInput::SpecialKeyRelease);

	glutDisplayFunc(Render);
	glutIdleFunc(Update);

	glutCloseFunc(Exit);

	glutMainLoop();
	return 0;
}