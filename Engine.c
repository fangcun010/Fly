#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "Engine.h"

Engine *CreateEngine()
{
    Engine *pEngine=malloc(sizeof(Engine));

    pEngine->bLeaveLoop=FALSE;
    pEngine->nLastFrameTime=GetTickCount();

    pEngine->pSceneManager=CreateSceneManager();
    pEngine->pTextureManager=CreateTextureManager();
    pEngine->pSoundManager=CreateSoundManager();

    pEngine->DoScenes=EngineDoScenes;
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

void EngineDoScenes(Engine *pEngine)
{
    SceneManager *pM=pEngine->pSceneManager;

    pM->DoCal(pM);
    pM->DoDraw(pM);
    pM->DoEvents(pM);
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

SpriteManager *CreateSpriteManager()
{
    SpriteManager *pM=malloc(sizeof(SpriteManager));

    pM->pSpriteVt=vtCreate();

    pM->DoCal=SpriteManagerDoCal;
    pM->DoDraw=SpriteManagerDoDraw;
    pM->DoEvents=SpriteManagerDoEvents;

    return pM;
}

void SpriteManagerDoCal(SpriteManager *pM)
{
    for(int i=0;i<vtCount(pM->pSpriteVt);i++)
    {
        Sprite *pSprite=vtGet(pM->pSpriteVt,i);

        pSprite->DoCal(pSprite);
    }
}

void SpriteManagerDoDraw(SpriteManager *pM)
{
    for(int i=0;i<vtCount(pM->pSpriteVt);i++)
    {
        Sprite *pSprite=vtGet(pM->pSpriteVt,i);

        pSprite->DoDraw(pSprite);
    }
}

void SpriteManagerDoEvents(SpriteManager *pM)
{
    for(int i=0;i<vtCount(pM->pSpriteVt);i++)
    {
        Sprite *pSprite=vtGet(pM->pSpriteVt,i);

        pSprite->DoEvents(pSprite);
    }
}

void DestorySpriteManager(SpriteManager *pM)
{
    vtDestory(pM->pSpriteVt);
    free(pM);
}

Scene *CreateScene()
{
    Scene *pScene=malloc(sizeof(Scene));

    pScene->DoCal=SceneDoCal;
    pScene->DoDraw=SceneDoDraw;
    pScene->DoEvents=SceneDoEvents;

    pScene->pSpriteManager=CreateSpriteManager();

    return pScene;
}

void SceneDoCal(Scene *pScene)
{
    SpriteManager *pM=pScene->pSpriteManager;

    pM->DoCal(pM);
}

void SceneDoDraw(Scene *pScene)
{
    SpriteManager *pM=pScene->pSpriteManager;

    pM->DoDraw(pM);
}

void SceneDoEvents(Scene *pScene)
{
    SpriteManager *pM=pScene->pSpriteManager;

    pM->DoEvents(pM);
}

void DestoryScene(Scene *pScene)
{
    DestorySpriteManager(pScene->pSpriteManager);
    free(pScene);
}

Texture *CreateTexture()
{
    Texture *pTexture=malloc(sizeof(Texture));

    return pTexture;
}

void DestoryTexture(Texture *pTexture)
{
    if(pTexture->TexID!=0)
        glDeleteTextures(1,&pTexture->TexID);

    free(pTexture);
}

TextureManager *CreateTextureManager()
{
    TextureManager *pM=malloc(sizeof(TextureManager));

    pM->pTextureVt=vtCreate();

    pM->UseTexture=TextureManagerUseTexture;
    pM->AddTexture=TextureManagerAddTexture;
    pM->GetTexture=TextureManagerGetTexture;
}

unsigned int TextureManagerAddTexture(TextureManager *pM,
                                                Texture *pTexture)
{
    Vector *vt=pM->pTextureVt;

    vtAddBack(vt,pTexture);

    return vtCount(vt)-1;
}

Texture *TextureManagerGetTexture(TextureManager *pM,
                                               unsigned int index)
{
    return vtGet(pM->pTextureVt,index);
}

void TextureManagerUseTexture(TextureManager *pM,
                                        unsigned int index)
{
    Texture *pTexture=pM->GetTexture(,pM,index);

    glBindTexture(GL_TEXTURE_2D,pTexture->TexID);
}

void DestoryTextureManager(TextureManager *pM)
{
    Vector *pTextureVt=pM->pTextureVt;

    for(int i=0;i<vtCount(pTextureVt);i++)
    {
        DestoryTexture(vtGet(pTextureVt,i));
    }

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

BOOL LoadTexture(Texture *pTexture,const char *strFile)
{
    FILE *fp=fopen(strFile,"rb");
    unsigned int w,h;
    GLuint texID;
    unsigned char *pData=NULL;

    if(!fp)
        return FALSE;

    fread(&w,sizeof(w),1,fp);
    fread(&h,sizeof(h),1,fp);

    pData=malloc(w*h*4);

    fread(pData,w*h*4,1,fp);

    glGenTextures(1,&texID);
    glBindTexture(GL_TEXTURE_2D,texID);

    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,w,h,0,GL_RGBA,GL_UNSIGNED_BYTE,pData);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    pTexture->Width=w;
    pTexture->Height=h;

    pTexture->TexID=texID;

    fclose(fp);

    return TRUE;
}
