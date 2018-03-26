#include "Engine.h"
#include <stdlib.h>
#include <sys/time.h>

Engine *CreateEngine()
{
    Engine *pEngine=malloc(sizeof(Engine));

    pEngine->bLeaveLoop=FALSE;
    pEngine->nLastFrameTime=GetTickCount();

    pEngine->pSceneManager=CreateSceneManager();
    pEngine->pTextureManager=CreateTextureManager();
    pEngine->pSoundManager=CreateSoundManager();

    pEngine->WaitForFrameTime=WaitForFrameTime;

    return pEngine;
}

void DestoryEngine(Engine *pEngine)
{
}

void WaitForFrameTime(Engine *pEngine)
{
    if(GetTickCount()-pEngine->nLastFrameTime<FRAMETIME)
    {
        usleep((FRAMETIME-(GetTickCount()-pEngine->nLastFrameTime))*1000);
    }

    pEngine->nLastFrameTime=GetTickCount();
}

SceneManager *CreateSceneManager()
{
    SceneManager *pM=malloc(sizeof(SceneManager));

    pM->DoCal=SceneManagerDoCal;
    pM->DoDraw=SceneManagerDoDraw;
    pM->DoEvents=SceneManagerDoEvents;

    return pM;
}

void SceneManagerDoCal(SceneManager *pM)
{
    for(int i=0;i<vtCount(pM->pSceneVt);i++)
    {
        Scene *pScene=vtGet(pM->pSceneVt);

        pScene->DoCal();
    }
}

void SceneManagerDoDraw(SceneManager *pM)
{
    for(int i=0;i<vtCount(pM->pSceneVt);i++)
    {
        Scene *pScene=vtGet(pM->pSceneVt);

        pScene->DoDraw();
    }
}

void SceneManagerDoEvents(SceneManager *pM)
{
    for(int i=0;i<vtCount(pM->pSceneVt);i++)
    {
        Scene *pScene=vtGet(pM->pSceneVt);

        pScene->DoEvents();
    }
}

void DestorySceneManager(SceneManager *pM)
{
    vtDestory(pVt);
    free(pM);
}

TextureManager *CreateTextureManager()
{

}

void DestoryTextureManager(TextureManager *pM)
{

}

SoundManager *CreateSoundManager()
{
}

void DestorySoundManager(SoundManager *pM)
{

}

unsigned long GetTickCount()
{
    struct timeval t;

    gettimeofday(&t,NULL);

    return t.tv_sec*1000LL+t.tv_usec/1000;
}

