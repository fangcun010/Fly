#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include "Engine.h"
#include "Game.h"

Engine *pEngine;
EventManager *pEventManager;

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

void EngineInit()
{
	pEngine=CreateEngine();

	pEventManager=pEngine->pEventManager;

	glPixelStorei(GL_UNPACK_ALIGNMENT,1);

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

    int loc=glGetUniformLocation(pProgram->ProgramID,"tex");

    ProgramManager *pProgramManager=pEngine->pProgramManager;

    unsigned int ProgramID=pProgramManager->AddProgram(pProgramManager,pProgram);

    pProgramManager->UseProgram(pProgramManager,ProgramID);

    glUniform1ui(loc,0);

    SceneManager *pSceneManager=pEngine->pSceneManager;

    InitGame();

    pSceneManager->AddScene(pSceneManager,pMainMenuScene);
}

void Mouse(int button,int state,int x,int y)
{
    EventManager *pM=pEngine->pEventManager;
    Event *pEvent=CreateClickEvent();
    ClickEvent *pClickEvent=pEvent->pTag;

    if(state==GLUT_DOWN)
        pClickEvent->bDown=TRUE;
    else
        pClickEvent->bDown=FALSE;

    pClickEvent->x=x;
    pClickEvent->y=y;

    pClickEvent->Button=button;

    pM->AddEvent(pM,pEvent);
}

int main(int argc,char *argv[])
{
	glutInit(&argc,argv);

	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);

	glutInitWindowSize(WND_W,WND_H);
	glutCreateWindow("Fly");

	glutMouseFunc(Mouse);

	GLenum err=glewInit();

	if(err!=GLEW_OK)
	{
        fprintf(stderr,"GLEW Error: %s\n",glewGetErrorString(err));
        return 1;
	}

	ShowOpenGLVersion();

	EngineInit();

	while(TRUE)
	{
        glutMainLoopEvent();

        if(pEngine->bLeaveLoop) break;

        pEngine->DoScenes(pEngine);

        pEventManager->DestoryAllEvents(pEventManager);
        pEngine->WaitForFrameTime(pEngine);

        glutSwapBuffers();
	}

	DestoryEngine(pEngine);

    return 0;
}
