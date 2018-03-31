#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include "Engine.h"
#include "Game.h"

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

GLfloat vts[]={
    0.0f,0.0f,1.0f,1.0f,1.0f,
    1.0f,1.0f,1.0f,1.0f,1.0f,
    0.0f,1.0f,1.0f,1.0f,1.0f
};

void Display()
{
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);

	GLuint VAO,VBO;

	glGenVertexArrays(1,&VAO);
	glGenBuffers(1,&VBO);
    glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);

	glBufferData(GL_ARRAY_BUFFER,sizeof(vts),vts,GL_STATIC_DRAW);

	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,5*sizeof(GLfloat),(GLvoid *)0);
    glEnableVertexAttribArray (0);
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,5*sizeof(GLfloat),(GLvoid *)(2*sizeof(GLfloat)));
    glEnableVertexAttribArray (1);

	glDrawArrays(GL_TRIANGLES,0,3);

	glutSwapBuffers();
}

void EngineInit()
{
    Shader *vShader=CreateShader(FALSE);
    Shader *fShader=CreateShader(TRUE);

    if(!LoadShader(vShader,"shader.vs",FALSE))
    {
        printf("Load vShader Fail:%s\n","shader.vs");
    }

    if(!LoadShader(fShader,"shader.fs",TRUE))
    {
        printf("Load fShader Fail:%s\n","shader.fs");
    }

    Program *pProgram=CreateProgram();

    LoadProgram(pProgram,vShader,fShader);

    glUseProgram(pProgram->ID);

    Vector *pVt=pEngine->pSceneManager->pSceneVt;

    InitGame();

    vtAddBack(pVt,pMainMenuScene);
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

	EngineInit();

	glutSwapBuffers();

	while(TRUE)
	{
        glutMainLoopEvent();

        if(pEngine->bLeaveLoop) break;

        pEngine->DoScenes(pEngine);

        pEngine->WaitForFrameTime(pEngine);

        glutSwapBuffers();
	}

	DestoryEngine(pEngine);

    return 0;
}
