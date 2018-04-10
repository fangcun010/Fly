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
    pEngine->pShaderManager=CreateShaderManager();
    pEngine->pProgramManager=CreateProgramManager();
    pEngine->pSoundManager=CreateSoundManager();
    pEngine->pEventManager=CreateEventManager();
    pEngine->pCallManager=CreateCallManager();

    pEngine->DoScenes=EngineDoScenes;
    pEngine->WaitForFrameTime=WaitForFrameTime;

    glGenVertexArrays(1,&pEngine->VAO);
    glGenBuffers(1,&pEngine->VBO);
    glBindVertexArray(&pEngine->VAO);
    glBindBuffer(GL_ARRAY_BUFFER,pEngine->VBO);

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

    pM->AddScene=SceneManagerAddScene;
    pM->RemoveScene=SceneManagerRemoveScene;

    pM->DoInit=SceneManagerDoInit;
    pM->DoCal=SceneManagerDoCal;
    pM->DoDraw=SceneManagerDoDraw;
    pM->DoEvents=SceneManagerDoEvents;

    return pM;
}

Scene *SceneManagerRemoveScene(SceneManager *pM,
                               unsigned int ID)
{
    Vector *pVt=pM->pSceneVt;

    for(int i=0;i<vtCount(pVt);i++)
    {
        Scene *pScene=vtGet(pVt,i);

        if(pScene->ID==ID)
        {
            vtRemove(pVt,i);
            return pScene;
        }
    }

    return NULL;
}

unsigned int SceneManagerAddScene(SceneManager *pM,
                                  Scene *pScene)
{
    Vector *pVt=pM->pSceneVt;

    vtAddBack(pVt,pScene);

    return pScene->ID;
}

void SceneManagerDoInit(SceneManager *pM)
{
    Vector *pVt=pM->pSceneVt;

    for(int i=0;i<vtCount(pM->pSceneVt);i++)
    {
        Scene *pScene=vtGet(pM->pSceneVt,i);

        pScene->DoInit(pScene);
    }
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

void SpriteDoInit(Sprite *pSprite)
{

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

    pSprite->ID=MakeID();

    pSprite->DoInit=SpriteDoInit;
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

    pM->AddSprite=SpriteManagerAddSprite;
    pM->GetSprite=SpriteManagerGetSprite;
    pM->RemoveSprite=SpriteManagerRemoveSprite;

    pM->DoInit=SpriteManagerDoInit;
    pM->DoCal=SpriteManagerDoCal;
    pM->DoDraw=SpriteManagerDoDraw;
    pM->DoEvents=SpriteManagerDoEvents;

    return pM;
}

Sprite *SpriteManagerRemoveSprite(SpriteManager *pM,
                            unsigned int ID)
{
    Vector *pVt=pM->pSpriteVt;

    for(int i=0;i<vtCount(pVt);i++)
    {
        Sprite *pSprite=vtGet(pVt,i);

        if(pSprite->ID==ID) return pSprite;
    }

    return NULL;
}

Sprite *SpriteManagerGetSprite(SpriteManager *pM,
                            unsigned int ID)
{
    Vector *pVt=pM->pSpriteVt;

    for(int i=0;i<vtCount(pVt);i++)
    {
        Sprite *pSprite=vtGet(pVt,i);

        if(pSprite->ID==ID)
            return pSprite;
    }

    return NULL;
}

unsigned int SpriteManagerAddSprite(SpriteManager *pM,
                            Sprite *pSprite)
{
    Vector *pVt=pM->pSpriteVt;

    vtAddBack(pVt,pSprite);

    return pSprite->ID;
}

void SpriteManagerDoInit(SpriteManager *pM)
{
    for(int i=0;i<vtCount(pM->pSpriteVt);i++)
    {
        Sprite *pSprite=vtGet(pM->pSpriteVt,i);

        pSprite->DoInit(pSprite);
    }
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

    pScene->ID=MakeID();

    pScene->AddSprite=SceneAddSprite;

    pScene->bDoEvents=TRUE;

    pScene->DoInit=SceneDoInit;
    pScene->DoCal=SceneDoCal;
    pScene->DoDraw=SceneDoDraw;
    pScene->DoEvents=SceneDoEvents;

    pScene->pSpriteManager=CreateSpriteManager();

    return pScene;
}

unsigned int SceneAddSprite(Scene *pScene,Sprite *pSprite)
{
    SpriteManager *pM=pScene->pSpriteManager;

    pM->AddSprite(pM,pSprite);

    return pSprite->ID;
}

Sprite *SceneGetSprite(Scene *pScene,unsigned int ID)
{
    SpriteManager *pM=pScene->pSpriteManager;

    return pM->GetSprite(pM,ID);
}

Sprite *SceneRemoveSprite(Scene *pScene,unsigned int ID)
{
    SpriteManager *pM=pScene->pSpriteManager;

    return pM->RemoveSprite(pM,ID);
}

void SceneDoInit(Scene *pScene)
{
    SpriteManager *pM=pScene->pSpriteManager;

    pM->DoInit(pM);
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

    pTexture->ID=MakeID();

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
    pM->RemoveTexture=TextureManagerRemoveTexture;
    pM->GetTexture=TextureManagerGetTexture;
}

unsigned int TextureManagerAddTexture(TextureManager *pM,
                                                Texture *pTexture)
{
    Vector *pVt=pM->pTextureVt;

    vtAddBack(pVt,pTexture);

    return pTexture->ID;
}

Texture *TextureManagerRemoveTexture(TextureManager *pM,
                                            unsigned int ID)
{
    Vector *pVt=pM->pTextureVt;

    for(int i=0;i<vtCount(pVt);i++)
    {
        Texture *pTexture=vtGet(pVt,i);

        if(pTexture->ID==ID)
        {
            vtRemove(pVt,i);
            return pTexture;
        }
    }

    return NULL;
}

Texture *TextureManagerGetTexture(TextureManager *pM,
                                               unsigned int ID)
{
    Vector *pVt=pM->pTextureVt;

    for(int i=0;i<vtCount(pVt);i++)
    {
        Texture *pTexture=vtGet(pVt,i);

        if(pTexture->ID==ID)
        {
            return pTexture;
        }
    }

    return NULL;
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

    pShader->ID=MakeID();
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

    program->ID=MakeID();

    return program;
}

void DestoryProgram(Program *pProgram)
{
    if(pProgram->ProgramID)
        glDeleteProgram(pProgram->ProgramID);
    free(pProgram);
}

ProgramManager *CreateProgramManager()
{
    ProgramManager *pM=malloc(sizeof(ProgramManager));

    pM->pProgramVt=vtCreate();

    pM->AddProgram=ProgramManagerAddProgram;

    pM->GetProgram=ProgramManagerGetProgram;
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

    vtAddBack(pVt,pProgram);

    return pProgram->ID;
}

Program *ProgramManagerRemoveProgram(ProgramManager *pM,
                                unsigned int ID)
{
    Vector *pVt=pM->pProgramVt;

    for(int i=0;i<vtCount(pVt);i++)
    {
        Program *pProgram=vtGet(pVt,i);

        if(pProgram->ID==ID)
            return pProgram;
    }

    return NULL;
}

Program *ProgramManagerGetProgram(ProgramManager *pM,
                           unsigned int ID)
{
    Vector *pVt=pM->pProgramVt;

    for(int i=0;i<vtCount(pVt);i++)
    {
        Program *pProgram=vtGet(pVt,i);

        if(pProgram->ID==ID)
            return pProgram;
    }

    return NULL;
}

void ProgramManagerUseProgram(ProgramManager *pM,
                              unsigned int ID)
{
    Program *program=ProgramManagerGetProgram(pM,ID);

    glUseProgram(program->ProgramID);
}

Event *CreateEvent()
{
    Event *pEvent=malloc(sizeof(Event));

    pEvent->ID=MakeID();
    pEvent->nEventID=EVENT_UNDEFINED;

    return pEvent;
}

void DestoryEvent(Event *pEvent)
{
    if(pEvent->pTag) free(pEvent->pTag);
    free(pEvent);
}

Event *CreateClickEvent()
{
    Event *pEvent=CreateEvent();
    ClickEvent *pClickEvent=malloc(sizeof(ClickEvent));

    pEvent->nEventID=EVENT_CLICK;
    pEvent->pTag=pClickEvent;

    return pEvent;
}

EventManager *CreateEventManager()
{
    EventManager *pM=malloc(sizeof(EventManager));

    pM->pEventVt=vtCreate();

    pM->GetEventCount=EventManagerGetEventCount;
    pM->AddEvent=EventManagerAddEvent;
    pM->GetEvent=EventManagerGetEvent;
    pM->RemoveEvent=EventManagerRemoveEvent;
    pM->DestoryAllEvents=EventManagerDestoryAllEvents;

    return pM;
}

unsigned int EventManagerAddEvent(EventManager *pM,
                                  Event *pEvent)
{
    Vector *pVt=pM->pEventVt;

    vtAddBack(pVt,pEvent);

    return pEvent->ID;
}

Event *EventManagerRemoveEvent(EventManager *pM,
                               unsigned int ID)
{
    Vector *pVt=pM->pEventVt;

    for(int i=0;i<vtCount(pVt);i++)
    {
        Event *pEvent=vtGet(pVt,i);

        if(pEvent->ID==ID)
        {
            vtRemove(pVt,i);
            return pEvent;
        }
    }

    return NULL;
}

Event *EventManagerGetEvent(EventManager *pM,
                            unsigned int ID)
{
    Vector *pVt=pM->pEventVt;

    for(int i=0;i<vtCount(pVt);i++)
    {
        Event *pEvent=vtGet(pVt,i);

        if(pEvent->ID==ID)
            return pEvent;
    }

    return NULL;
}

void EventManagerDestoryAllEvents(EventManager *pM)
{
    Vector *pVt=pM->pEventVt;

    for(int i=0;i<vtCount(pVt);i++)
        DestoryEvent(vtGet(pVt,i));

    pVt->nCount=0;
}

unsigned int EventManagerGetEventCount(EventManager *pM)
{
    Vector *pVt=pM->pEventVt;

    return vtCount(pVt);
}

void DestoryEventManager(EventManager *pM)
{
    Vector *pVt=pM->pEventVt;
    vtDestory(pVt);
    free(pM);
}

Call *CreateCall(ObjFunc pFunc,void *pData)
{
    Call *pCall=malloc(sizeof(Call));

    pCall->ID=MakeID();
    pCall->pFunc=pFunc;
    pCall->pData=pData;

    return pCall;
}

void DestoryCall(Call *pCall)
{
    free(pCall);
}

CallManager *CreateCallManager()
{
    CallManager *pCallManager=malloc(sizeof(CallManager));

    pCallManager->pCallVt=vtCreate();

    pCallManager->AddCall=CallManagerAddCall;
    pCallManager->GetCall=CallManagerGetCall;
    pCallManager->RemoveCall=CallManagerRemoveCall;
    pCallManager->DestoryAllCalls=CallManagerDestoryAllCalls;
    pCallManager->DoCalls=CallManagerDoCalls;

    return pCallManager;
}

unsigned int CallManagerAddCall(CallManager *pM,Call *pCall)
{
    Vector *pVt=pM->pCallVt;

    vtAddBack(pVt,pCall);

    return pCall->ID;
}

Call *CallManagerGetCall(CallManager *pM,unsigned int ID)
{
    Vector *pVt=pM->pCallVt;

    for(int i=0;i<vtCount(pVt);i++)
    {
        Call *pCall=vtGet(pVt,i);

        if(pCall->ID==ID) return pCall;
    }

    return NULL;
}

Call *CallManagerRemoveCall(CallManager *pM,unsigned int ID)
{
    Vector *pVt=pM->pCallVt;

    for(int i=0;i<vtCount(pVt);i++)
    {
        Call *pCall=vtGet(pVt,i);

        if(pCall->ID==ID)
        {
            DestoryCall(pCall);
            return pCall;
        }
    }

    return NULL;
}

void CallManagerDestoryAllCalls(CallManager *pM)
{
    Vector *pVt=pM->pCallVt;

    for(int i=0;i<vtCount(pVt);i++)
        DestoryCall(vtGet(pVt,i));

    pVt->nCount=0;
}

void CallManagerDoCalls(CallManager *pM)
{
    Vector *pVt=pM->pCallVt;

    for(int i=0;i<vtCount(pVt);i++)
    {
        Call *pCall=vtGet(pVt,i);

        pCall->pFunc(pCall->pData);
    }
}

void DestoryCallManager(CallManager *pM)
{
    vtDestory(pM->pCallVt);
    free(pM);
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

    pShader->ShaderID=shader;

    return TRUE;
}

unsigned int MakeID()
{
    static unsigned int id;

    return id++;
}

BOOL LoadProgram(Program *pProgram,Shader *pVertexShader,Shader *pFragShader)
{
    GLuint program=glCreateProgram();

    if(!program) return FALSE;

    glAttachShader(program,pVertexShader->ShaderID);
    glAttachShader(program,pFragShader->ShaderID);

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

    pProgram->ProgramID=program;

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

static GLfloat ShowImageVts[]=
{
    0.0f,0.0f           ,0.0f,0.0f,
    200.0f,0.0f           ,1.0f,0.0f,
    200.0f,200.0f           ,1.0f,1.0f,
    0.0f,200.0f           ,0.0f,1.0f
};

void ShowImage(Texture *pTexture,int x,int y,int w,int h)
{
    glBindTexture(GL_TEXTURE_2D,pTexture->TexID);

    ShowImageVts[0]=x;
    ShowImageVts[1]=y;
    ShowImageVts[4]=x+w;
    ShowImageVts[5]=y;
    ShowImageVts[8]=x+w;
    ShowImageVts[9]=y+h;
    ShowImageVts[12]=x;
    ShowImageVts[13]=y+h;

    glBufferData(GL_ARRAY_BUFFER,sizeof(ShowImageVts),
                    ShowImageVts,GL_STATIC_DRAW);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,4*sizeof(GLfloat),(GLvoid *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,4*sizeof(GLfloat),(GLvoid *)(2*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_TRIANGLE_FAN,0,4);
}

BOOL IsInRect(int x,int y,int dx,int dy,int w,int h)
{
    if(x>=dx && x<=dx+w-1 && y>=dy && y<=dy+h-1)
        return TRUE;
    return FALSE;
}
