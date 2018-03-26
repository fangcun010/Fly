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

    pM->pSceneVt=vtCreate();
    pM->DoCal=SceneManagerDoCal;
    pM->DoDraw=SceneManagerDoDraw;
    pM->DoEvents=SceneManagerDoEvents;

    return pM;
}

void SceneManagerDoCal(SceneManager *pM)
{
    for(int i=0;i<vtCount(pM->pSceneVt);i++)
    {
        Scene *pScene=vtGet(pM->pSceneVt,i);

        pScene->DoCal(pScene);
    }
}

void SceneManagerDoDraw(SceneManager *pM)
{
    for(int i=0;i<vtCount(pM->pSceneVt);i++)
    {
        Scene *pScene=vtGet(pM->pSceneVt,i);

        pScene->DoDraw(pScene);
    }
}

void SceneManagerDoEvents(SceneManager *pM)
{
    for(int i=0;i<vtCount(pM->pSceneVt);i++)
    {
        Scene *pScene=vtGet(pM->pSceneVt,i);

        pScene->DoEvents(pScene);
    }
}

void DestorySceneManager(SceneManager *pM)
{
    vtDestory(pM->pSceneVt);
    free(pM);
}

void SpriteDoCal(Sprite *pSprite)
{

}

void SpriteDoDraw(Sprite *pSprite)
{

}

void SpriteDoEvents(Sprite *pSprite)
{

}

Sprite *CreateSprite()
{
    Sprite *pSprite=malloc(sizeof(Sprite));

    pSprite->DoCal=SpriteDoCal;
    pSprite->DoDraw=SpriteDoDraw;
    pSprite->DoEvents=SpriteDoEvents;
}

void DestorySprite(Sprite *pSprite)
{
    free(pSprite);
}

Scene *CreateScene()
{
    Scene *pScene=malloc(sizeof(Scene));

    pScene->DoCal=SceneDoCal;
    pScene->DoDraw=SceneDoDraw;
    pScene->DoEvents=SceneDoEvents;

    return pScene;
}

void SceneDoCal(Scene *pScene)
{

}

void SceneDoDraw(Scene *pScene)
{

}

void SceneDoEvents(Scene *pScene)
{

}

void DestoryScene(Scene *pScene)
{
    vtDestory(pScene->pSpriteVt);
    free(pScene);
}

TextureManager *CreateTextureManager()
{
    TextureManager *pM=malloc(sizeof(TextureManager));

    pM->pTextureVt=vtCreate();
}

void DestoryTextureManager(TextureManager *pM)
{
    vtDestory(pM->pTextureVt);
    free(pM);
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

