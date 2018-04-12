#ifndef SGENGINE_H_INCLUDED
#define SGENGINE_H_INCLUDED

#include "Vector.h"

#define           TRUE                      1
#define           FALSE                     0
#define           FRAMETIME                 33

#define           EVENT_UNDEFINED           5000
#define           EVENT_CLICK               5001
#define           EVENT_KEY                 5002

#define           KEY_LEFT                  10
#define           KEY_RIGHT                 11
#define           KEY_UP                    12
#define           KEY_DOWN                  13

typedef int BOOL;

typedef void (*Func) ();                                 //函数回调
typedef BOOL (*bFunc) ();
typedef void (*ObjFunc) (void *);
typedef void (*ObjFuncUInt) (void *,
                                    unsigned int);
typedef unsigned int (*UIntObjFunc) (void *);
typedef unsigned int (*UIntObjFuncParam) (void *,
                                            void *);
typedef void *(*PointObjFuncUInt) (void *,
                                    unsigned int);

typedef struct tagSprite                                   //精灵
{
    unsigned int ID;

    ObjFunc DoInit;                                           //执行初始化
    ObjFunc DoCal;                                            //执行计算
    ObjFunc DoDraw;                                           //执行绘制
    ObjFunc DoEvents;                                         //执行事件　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　//执行事件

    void *pTag;                                                //附加信息
} Sprite;

typedef struct tagSpriteManager                        //精灵管理器
{
    Vector *pSpriteVt;                                   //精灵向量

    UIntObjFuncParam AddSprite;                         //添加精灵
    PointObjFuncUInt GetSprite;                         //获取精灵
    PointObjFuncUInt RemoveSprite;                      //移除精灵

    ObjFunc DoInit;
    ObjFunc DoCal;                                        //计算
    ObjFunc DoDraw;                                       //绘制
    ObjFunc DoEvents;                                     //事件
} SpriteManager;

typedef struct tagCall
{
    int ID;
    ObjFunc pFunc;
    void *pData;
} Call;

typedef struct tagCallManager                        //回调管理器
{
    Vector *pCallVt;                                     //回调向量

    PointObjFuncUInt GetCall;                           //获取回调
    PointObjFuncUInt RemoveCall;                        //移除回调
    UIntObjFuncParam AddCall;                           //添加函数回调
    ObjFunc DestoryAllCalls;                            //销毁所有回调
    ObjFunc DoCalls;                                     //执行回调
} CallManager;

typedef struct tagTexture
{
    unsigned int ID;
    int Width,Height;                                    //大小
    unsigned int TexID;                                 //纹理ID
} Texture;

typedef struct tagTextureManager                      //纹理管理器
{
    Vector *pTextureVt;                                  //纹理向量

    ObjFuncUInt UseTexture;                             //使用纹理
    UIntObjFuncParam AddTexture;                      //添加纹理
    PointObjFuncUInt RemoveTexture;                   //移除纹理
    PointObjFuncUInt GetTexture;                      //获取纹理
} TextureManager;

typedef struct tagSoundManager                       //声音管理器
{
    Vector *pSoundVt;
} SoundManager;

typedef struct tagScene                                    //场景
{
    unsigned int ID;

    BOOL bDoEvents;                                          //是否执行事件

    SpriteManager *pSpriteManager;                         //精灵向量

    UIntObjFuncParam AddSprite;                            //添加精灵
    PointObjFuncUInt GetSprite;                            //获取精灵
    PointObjFuncUInt RemoveSprite;                         //移除精灵

    ObjFunc DoInit;                                          //场景初始化
    ObjFunc DoCal;                                           //执行计算
    ObjFunc DoDraw;                                          //执行绘制
    ObjFunc DoEvents;                                       //执行事件
} Scene;

typedef struct tagSceneManager                                  //场景管理器
{
    Vector *pSceneVt;                                               //场景向量

    UIntObjFuncParam AddScene;                                         //添加场景
    PointObjFuncUInt RemoveScene;                                     //移除场景
    ObjFunc DoInit;                                                     //执行初始化
    ObjFunc DoCal;                                                      //执行计算
    ObjFunc DoDraw;                                                     //执行绘制
    ObjFunc DoEvents;                                                   //执行事件
} SceneManager;

typedef struct tagEvent                                             //事件
{
    unsigned int ID;
    int nEventID;                                                    //事件ID
    void *pTag;                                                      //事件附加信息
} Event;

typedef struct tagClickEvent                                       //点击事件
{
    int Button;
    int x,y;
    BOOL bDown;
} ClickEvent;

typedef struct tagKeyEvent
{
    int key;
    BOOL bDown;
} KeyEvent;

typedef struct tagEventManager                                    //事件管理器
{
    Vector *pEventVt;                                               //事件向量

    UIntObjFunc GetEventCount;                                     //获取事件个数

    UIntObjFuncParam AddEvent;                                     //添加事件
    PointObjFuncUInt RemoveEvent;                                 //移除事件
    PointObjFuncUInt GetEvent;                                     //获取事件

    ObjFunc DestoryAllEvents;                                      //销毁所有事件
} EventManager;

typedef struct tagShader                                           //着色器
{
    unsigned int ID;
    GLuint ShaderID;                                                 //着色器ID
    BOOL bFrag;                                                       //是否是片段着色器
} Shader;

typedef struct tagShaderManager                                    //着色器管理器
{
    Vector *pShaderVt;                                              //着色器向量
    UIntObjFuncParam AddShader;                                    //添加着色器
    PointObjFuncUInt GetShader;
} ShaderManager;

typedef struct tagProgram                                         //着色程序
{
    unsigned int ID;
    GLuint ProgramID;
} Program;

typedef struct tagProgramManager                                //着色程序管理器
{
    Vector *pProgramVt;
    UIntObjFuncParam AddProgram;
    PointObjFuncUInt GetProgram;
    ObjFuncUInt UseProgram;
} ProgramManager;

typedef struct tagEngine                                          //引擎
{
    unsigned int VAO;
    unsigned int VBO;

    SceneManager *pSceneManager;                                  //场景管理器
    TextureManager *pTextureManager;                              //纹理管理器
    ShaderManager *pShaderManager;                                //着色器管理器
    ProgramManager *pProgramManager;                              //着色程序管理器
    SoundManager *pSoundManager;                                  //声音管理器
    EventManager *pEventManager;                                  //事件管理器
    CallManager *pCallManager;                                    //回调管理器

    ObjFunc WaitForFrameTime;                                     //等待刷新时间
    ObjFunc DoScenes;                                              //执行场景操作

    unsigned long nLastFrameTime;                                //上一次
    BOOL bLeaveLoop;                                                //是否跳出游戏循环
} Engine;

Engine *             CreateEngine();                                  //创建引擎
void                  DestoryEngine(Engine *pEngine);             //销毁引擎
void                  EngineDoScenes(Engine *pEngine);            //执行场景操作
void                  WaitForFrameTime(Engine *pEngine);         //等待帧时间

SceneManager *      CreateSceneManager();                                //创建场景管理器
void                  DestorySceneManager(SceneManager *pM);           //销毁场景管理器
unsigned int         SceneManagerAddScene(SceneManager *pM,           //添加场景
                                           Scene *pScene);
Scene *               SceneManagerRemoveScene(SceneManager *pM,        //移除场景
                                    unsigned int ID);
void                  SceneManagerDoInit(SceneManager *pM);            //执行初始化
void                  SceneManagerDoCal(SceneManager *pM);             //计算
void                  SceneManagerDoDraw(SceneManager *pM);            //绘制
void                  SceneManagerDoEvents(SceneManager *pM);          //执行事件

Scene *               CreateScene();                                       //创建场景
void                  DestoryScene(Scene *pScene);                        //销毁场景
unsigned int         SceneAddSprite(Scene *pScene,                      //添加精灵
                                        Sprite *pSprite);
Sprite *              SceneGetSprite(Scene *pScene,                     //获取精灵
                                        unsigned int ID);
Sprite *              SceneRemoveSprite(Scene *pScene,                   //移除精灵
                                            unsigned int ID);
void                  SceneDoInit(Scene *pScene);                           //场景初始化
void                  SceneDoCal(Scene *pScene);                           //场景计算
void                  SceneDoDraw(Scene *pScene);                          //场景绘制
void                  SceneDoEvents(Scene *pScene);                       //场景执行事件

Sprite *              CreateSprite();
void                   DestorySprite(Sprite *pSprite);
void                   SpriteDoInit(Sprite *pSprite);
void                   SpriteDoCal(Sprite *pSprite);
void                   SpriteDoDraw(Sprite *Sprite);
void                   SpriteDoEvents(Sprite *Sprite);

SpriteManager *     CreateSpriteManager();                                //创建精灵管理器
void                   DestorySpriteManager(SpriteManager *pM);          //销毁精灵管理器
unsigned int          SpriteManagerAddSprite(SpriteManager *pM,
                                        Sprite *pSprite);
Sprite *               SpriteManagerGetSprite(SpriteManager *pM,        //获取精灵
                                        unsigned int ID);
Sprite *               SpriteManagerRemoveSprite(SpriteManager *pM,     //移除精灵
                                           unsigned int ID);
void                   SpriteManagerDoInit(SpriteManager *pM);
void                   SpriteManagerDoCal(SpriteManager *pM);
void                   SpriteManagerDoDraw(SpriteManager *pM);
void                   SpriteManagerDoEvents(SpriteManager *pM);

TextureManager *   CreateTextureManager();                                  //创建纹理管理器
void                  DestoryTextureManager(TextureManager *pM);           //销毁纹理管理器
unsigned int        TextureManagerAddTexture(TextureManager *pM,          //添加纹理
                                                    Texture *pTexture);
Texture *            TextureManagerRemoveTexture(TextureManager *pM,      //移除纹理
                                                 unsigned int ID);
Texture *            TextureManagerGetTexture(TextureManager *pM,   //获取纹理
                                                    unsigned int ID);
void                  TextureManagerUseTexture(TextureManager *pM,   //使用纹理
                                                    unsigned int ID);

Shader *             CreateShader(BOOL bFrag);                            //创建着色器
void                  DestoryShader(Shader *pShader);                    //销毁着色器

ShaderManager *    CreateShaderManager();                               //创建着色器管理器
void                  DestoryShaderManager(ShaderManager *pM);         //销毁着色器管理器
unsigned int        ShaderManagerAddShader(ShaderManager *pM,         //添加着色器
                                           Shader *pShader);
Shader *             ShaderManagerGetShader(ShaderManager *pM,        //获取着色器
                                            unsigned int ID);

Program *            CreateProgram();                                   //创建着色器程序
void                  DestoryProgram(Program *pProgram);              //销毁着色器程序

ProgramManager *    CreateProgramManager();                          //创建着色程序管理器
void                  DestoryProgramManager(ProgramManager *pM);    //销毁着色程序管理器
unsigned int         ProgramManagerAddProgram(ProgramManager *pM,  //添加着色器程序
                                        Program *pProgram);
Program *             ProgramManagerRemoveProgram(                    //移除着色器程序
                                                  ProgramManager *pM,
                                        unsigned int ID);
Program *             ProgramManagerGetProgram(ProgramManager *pM,         //着色器程序获取
                                        unsigned int ID);
void                  ProgramManagerUseProgram(ProgramManager *pM,  //使用着色器程序
                                            unsigned int ID);

SoundManager *      CreateSoundManager();                                   //创建声音管理器
void                  DestorySoundManager(SoundManager *pM);               //销毁声音管理器

Event *              CreateEvent();                                           //创建事件
void                  DestoryEvent(Event *pEvent);                          //销毁事件

Event *              CreateClickEvent();                                     //创建点击事件
Event *              CreateKeyEvent();                                       //创建按键事件

EventManager *      CreateEventManager();                                   //创建事件管理器
void                 DestoryEventManager();                                  //销毁事件管理器
unsigned int        EventManagerAddEvent(EventManager *pM,                //添加事件
                                          Event *pEvent);
Event *              EventManagerRemoveEvent(EventManager *pM,             //移除事件
                                        unsigned int ID);
Event *              EventManagerGetEvent(EventManager *pM,                //获取事件
                                          unsigned int ID);
void                 EventManagerDestoryAllEvents(EventManager *pM);      //移除所有事件
unsigned int        EventManagerGetEventCount(EventManager *pM);          //获取事件个数

Call *               CreateCall(ObjFunc pFunc,void *pData);                //创建回调
void                 DestoryCall(Call *pCall);                               //销毁回调

CallManager *       CreateCallManager();                                    //创建回调管理器
void                 DestoryCallManager(CallManager *pM);                  //销毁回调管理器
unsigned int        CallManagerAddCall(CallManager *pM,                   //添加回调
                                       Call *pCall);
Call *               CallManagerRemoveCall(CallManager *pM,                //移除回调
                                        unsigned int ID);
Call *               CallManagerGetCall(CallManager *pM,                   //获取回调
                                        unsigned int ID);
void                 CallManagerDoCalls(CallManager *pM);                  //执行回调
void                 CallManagerDestoryAllCalls(CallManager *pM);         //销毁所有回调

unsigned int        MakeID();                                                 //产生一个不重复的ID值
unsigned long       GetTickCount();                                          //获取毫秒数
BOOL                  LoadTexture(Texture *pTexture,const char *strFile); //载入纹理
const char *         LoadTextFile(const char *strFile);                            //读取文本文件
BOOL                  LoadShader(Shader *pShader,const char *strFile,             //载入着色器
                                                    BOOL bFrag);
BOOL                  LoadProgram(Program *pProgram,Shader *pVertexShader,       //载入着色程序
                                        Shader *pFragShader);
void                  ShowImage(Texture *pTexture,                                  //显示图像
                                        int x,int y,int w,int h);
BOOL                  IsInRect(int x,int y,int dx,int dy,int w,int h);            //是否在矩形范围

#endif // SGENGINE_H_INCLUDED
