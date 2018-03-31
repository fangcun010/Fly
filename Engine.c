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
    Texture *pTexture=pM->GetTexture(pM,index);

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

Shader *CreateShader(BOOL bFrag)
{
    Shader *pShader=malloc(sizeof(Shader));

    pShader->bFrag=bFrag;

    return pShader;
}

void DestoryShader(Shader *pShader)
{
    if(pShader->ID)
        glDeleteShader(pShader->ID);

    free(pShader);
}

ShaderManager *CreateShaderManager()
{
    ShaderManager *pM=malloc(sizeof(ShaderManager));

    pM->pShaderVt=vtCreate();

    pM->AddShader=ShaderManagerAddShader;
    pM->GetShader=ShaderManagerGetShader;

    return pM;
}

void DestoryShaderManager(ShaderManager *pM)
{
    Vector *pVt=pM->pShaderVt;

    for(int i=0;i<vtCount(pVt);i++)
        DestoryShader(vtGet(pVt,i));

    vtDestory(pVt);

    free(pM);
}

unsigned int ShaderManagerAddShader(ShaderManager *pM,
                                    Shader *pShader)
{
    unsigned int ret;
    Vector *pVt=pM->pShaderVt;

    ret=vtCount(pVt);

    vtAddBack(pVt,pShader);

    return ret;
}

Shader *ShaderManagerGetShader(ShaderManager *pM,
                                unsigned int index)
{
    Vector *pVt=pM->pShaderVt;

    return vtGet(pVt,index);
}

SoundManager *CreateSoundManager()
{
}

void DestorySoundManager(SoundManager *pM)
{

}

Program *CreateProgram()
{
    Program *program=malloc(sizeof(Program));

    return program;
}

void DestoryProgram(Program *pProgram)
{
    if(pProgram->ID)
        glDeleteProgram(pProgram->ID);
    free(pProgram);
}

ProgramManager *CreateProgramManager()
{
    ProgramManager *pM=malloc(sizeof(ProgramManager));

    pM->pProgramVt=vtCreate();

    pM->AddProgram=ProgramManagerAddProgram;
    pM->GetProgram=ProgramManagerGet;
    pM->UseProgram=ProgramManagerUseProgram;

    return pM;
}

void DestoryProgramManager(ProgramManager *pM)
{
    Vector *pVt=pM->pProgramVt;

    for(int i=0;vtCount(pVt);i++)
        DestoryProgram(vtGet(pVt,i));

    free(pM);
}

unsigned int ProgramManagerAddProgram(ProgramManager *pM,
                              Program *pProgram)
{
    Vector *pVt=pM->pProgramVt;

    unsigned int ret;

    ret=vtCount(pVt);

    vtAddBack(pVt,pProgram);

    return ret;
}

Program *ProgramManagerGet(ProgramManager *pM,
                           unsigned int index)
{
    Vector *pVt=pM->pProgramVt;

    return vtGet(pVt,index);
}

void ProgramManagerUseProgram(ProgramManager *pM,
                              unsigned int index)
{
    Vector *pVt=pM->pProgramVt;
    Program *program=vtGet(pVt,index);

    glUseProgram(program->ID);
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

BOOL LoadShader(Shader *pShader,const char *strFile,BOOL bFrag)
{
    const char *pText=LoadTextFile(strFile);

    GLuint shader;

    if(bFrag) shader=glCreateShader(GL_FRAGMENT_SHADER);
    else shader=glCreateShader(GL_VERTEX_SHADER);

    if(!shader)
        return FALSE;


    glShaderSource(shader,1,&pText,NULL);
    glCompileShader(shader);

    GLuint err;

    glGetShaderiv(shader,GL_COMPILE_STATUS,&err);

    if(!err)
    {
        GLchar *log[1024];

        glGetShaderInfoLog(shader,sizeof(log),NULL,log);
        printf("%s\n%s\n",strFile,log);
        return FALSE;
    }

    free(pText);

    pShader->ID=shader;

    return TRUE;
}

BOOL LoadProgram(Program *pProgram,Shader *pVertexShader,Shader *pFragShader)
{
    GLuint program=glCreateProgram();

    if(!program) return FALSE;

    glAttachShader(program,pVertexShader->ID);
    glAttachShader(program,pFragShader->ID);

    glLinkProgram(program);

    GLuint err;

    glGetProgramiv(program,GL_LINK_STATUS,&err);

    if(!err)
    {
        GLchar *log[1024];

        glGetProgramInfoLog(program,sizeof(log),NULL,log);
        printf("%s\n",log);
        return FALSE;
    }

    pProgram->ID=program;

    return TRUE;
}

const char *LoadTextFile(const char *strFile)
{
    FILE *fp=fopen(strFile,"rb");
    char *pMem=NULL;

    if(!fp) return NULL;

    fseek(fp,0,SEEK_END);

    long int sz=ftell(fp);

    pMem=malloc(sz+1);

    if(!pMem) return NULL;

    fseek(fp,0,SEEK_SET);

    fread(pMem,sz,1,fp);

    pMem[sz]=0;

    fclose(fp);

    return pMem;
}

static GLfloat ShowImageVts[4]=
{
    0.0f,0.0f           ,0.0f,0.0f,
    0.0f,0.0f           ,1.0f,0.0f,
    0.0f,0.0f           ,1.0f,1.0f,
    0.0f,0.0f           ,0.0f,1.0f
};

void ShowImage(TextureManager *pM,unsigned int TexID,int x,int y,
                    int sx,int sy,int w,int h)
{

}
