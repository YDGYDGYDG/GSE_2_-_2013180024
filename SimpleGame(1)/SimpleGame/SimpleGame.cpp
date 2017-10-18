/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Renderer.h"
#include "GameObject.h"
#include "SceneMgr.h"

Renderer *g_Renderer = NULL;
SceneMgr *g_SceneMgr = NULL;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	for (int i = 0; i < g_SceneMgr->CountObject(); i++) {
		g_Renderer->DrawSolidRect(
			g_SceneMgr->GetObjectStats(i)->posX,
			g_SceneMgr->GetObjectStats(i)->posY,
			g_SceneMgr->GetObjectStats(i)->posZ,
			g_SceneMgr->GetObjectStats(i)->size,
			g_SceneMgr->GetObjectStats(i)->colorR, 
			g_SceneMgr->GetObjectStats(i)->colorG, 
			g_SceneMgr->GetObjectStats(i)->colorB, 
			g_SceneMgr->GetObjectStats(i)->colorA );
		g_SceneMgr->Update();
	}

	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
	g_SceneMgr->Update();
}

void MouseInput(int button, int state, int x, int y)
{
	//RenderScene();
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		g_SceneMgr->AddObject(x, y, 0);
	}
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize Renderer
	g_Renderer = new Renderer(500, 500);
	g_SceneMgr = new SceneMgr();

	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}


	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete g_Renderer;
	for (int i = 0; i < g_SceneMgr->CountObject(); i++) {
		g_SceneMgr->DeleteObject(i);
	}

    return 0;
}

