#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include "Engine.h"

#define 				WND_W						400
#define				WND_H						600

Engine *pEngine;

void ShowOpenGLVersion()
{
	const GLubyte* strName = glGetString(GL_VENDOR); //返回负责当前OpenGL实现厂商的名字
    const GLubyte* strLabel = glGetString(GL_RENDERER);//返回一个渲染器标识符，通常是个硬件平台
    const GLubyte* strOpenGLVersion =glGetString(GL_VERSION);//返回当前OpenGL实现的版本号
    const GLubyte* strgluVersion= gluGetString(GLU_VERSION);//返回当前GLU工具库版本
    printf("OpenGL实现厂商的名字：%s\n", strName);
    printf("渲染器标识符：%s\n", strLabel);
    printf("OpenGL实现的版本号：%s\n",strOpenGLVersion );
    printf("OpenGL工具库版本：%s\n", strgluVersion);
}

void Display()
{
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);

	glutSwapBuffers();
}

int main(int argc,char *argv[])
{
	glutInit(&argc,argv);

	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);

	glutInitWindowSize(WND_W,WND_H);
	glutCreateWindow("Fly");

	glutDisplayFunc(Display);

	GLenum err=glewInit();

	if(err!=GLEW_OK)
	{
        fprintf(stderr,"GLEW Error: %s\n",glewGetErrorString(err));
        return 1;
	}

	ShowOpenGLVersion();

	pEngine=CreateEngine();

	while(TRUE)
	{
        glutMainLoopEvent();

        if(pEngine->bLeaveLoop) break;



        pEngine->WaitForFrameTime(pEngine);

        glutSwapBuffers();
	}

    return 0;
}
