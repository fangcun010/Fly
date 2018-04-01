#ifndef SGENGINE_H_INCLUDED
#define SGENGINE_H_INCLUDED

#include "Vector.h"

#define           TRUE                      1
#define           FALSE                     0
#define           FRAMETIME                 33

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

    ObjFunc DoCal;                                            //执行计算
    ObjFunc DoDraw;                                           //执行绘制
    ObjFunc DoEvents;                                        //执行事件　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　//执行事件
} Sprite;

typedef struct tagSpriteManager                      //精灵管理器
{
    Vector *pSpriteVt;                                   //精灵向量
    ObjFunc DoCal;                                        //计算
    ObjFunc DoDraw;                                       //绘制
    ObjFunc DoEvents;                                     //事件
} SpriteManager;

typedef struct tagCallManager                        //回调管理器
{
    Vector *pCallVt;                                     //回调向量
} CallManager;

typedef struct tagTexture
{
    unsigned int ID;
    int Width,Height;                                    //大小
    unsigned int TexID;                                 //纹理ID
} Texture;

typedef struct tagTextureManager                     //纹理管理器
{
    Vector *pTextureVt;                                  //纹理向量

    ObjFuncUInt UseTexture;                             //使用纹理
    UIntObjFuncParam AddTexture;                      //添加纹理
    PointObjFuncUInt GetTexture;                      //获取纹理
} TextureManager;

typedef struct tagSoundManager                       //声音管理器
{
    Vector *pSoundVt;
} SoundManager;

typedef struct tagScene                                    //场景
{
    unsigned int ID;

    SpriteManager *pSpriteManager;                       //精灵向量
    ObjFunc DoCal;                                           //执行计算
    ObjFunc DoDraw;                                          //执行绘制
    ObjFunc DoEvents;                                       //执行事件
} Scene;

typedef struct tagSceneManager                                  //场景管理器
{
    Vector *pSceneVt;                                               //场景向量

    ObjFunc DoCal;                                                      //执行计算
    ObjFunc DoDraw;                                                     //执行绘制
    ObjFunc DoEvents;                                                   //执行事件
} SceneManager;

typedef struct tagEvent                                          //事件
{
    unsigned int ID;
    int nEventID;                                                   //事件ID
    void *pTag;                                                      //事件附加信息
} Event;

typedef struct tagEventManager                                  //事件管理器
{
    Vector *pEventVt;                                               //事件向量

} EventManager;

typedef struct tagShader                                           //着色器
{
    unsigned int ID;
    GLuint shaderID;                                                        //着色器ID
    BOOL bFrag;                                                       //是否是片段着色器
} Shader;

typedef struct tagShderManager                                  //着色器管理器
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
    SceneManager *pSceneManager;                                 //场景管理器
    TextureManager *pTextureManager;                            //纹理管理器
    SoundManager *pSoundManager;                                 //声音管理器

    ObjFunc WaitForFrameTime;                                     //等待刷新时间
    ObjFunc DoScenes;                                               //执行场景操作

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
void                  SceneManagerDoCal(SceneManager *pM);             //计算
void                  SceneManagerDoDraw(SceneManager *pM);            //绘制
void                  SceneManagerDoEvents(SceneManager *pM);          //执行事件

Scene *               CreateScene();                                         //创建场景
void                  DestoryScene(Scene *pScene);                        //销毁场景
void                  SceneDoCal(Scene *pScene);                           //场景计算
void                  SceneDoDraw(Scene *pScene);                          //场景绘制
void                  SceneDoEvents(Scene *pScene);                       //场景执行事件

Sprite *              CreateSprite();
void                   DestorySprite(Sprite *pSprite);
void                   SpriteDoCal(Sprite *pSprite);
void                   SpriteDoDraw(Sprite *Sprite);
void                   SpriteDoEvents(Sprite *Sprite);

SpriteManager *     CreateSpriteManager();                                //创建精灵管理器
void                   DestorySpriteManager(SpriteManager *pM);          //销毁精灵管理器
//void                   SpriteManagerAddSprite()
//Sprite *               SpriteManagerRemoveSprite(SpriteManager *pM,     //移除精灵
//                                           unsigned int ID);
void                   SpriteManagerDoCal(SpriteManager *pM);
void                   SpriteManagerDoDraw(SpriteManager *pM);
void                   SpriteManagerDoEvents(SpriteManager *pM);

TextureManager *   CreateTextureManager();                             //创建纹理管理器
void                  DestoryTextureManager(TextureManager *pM);     //销毁纹理管理器
unsigned int        TextureManagerAddTexture(TextureManager *pM,  //添加纹理
                                                    Texture *pTexture);
Texture *            TextureManagerGetTexture(TextureManager *pM,   //获取纹理
                                                    unsigned int index);
void                  TextureManagerUseTexture(TextureManager *pM,   //使用纹理
                                                    unsigned int index);

Shader *             CreateShader(BOOL bFrag);                            //创建着色器
void                  DestoryShader(Shader *pShader);                    //销毁着色器

ShaderManager *    CreateShaderManager();                               //创建着色器管理器
void                  DestoryShaderManager(ShaderManager *pM);        //销毁着色器管理器
unsigned int        ShaderManagerAddShader(ShaderManager *pM,      //添加着色器
                                           Shader *pShader);
Shader *             ShaderManagerGetShader(ShaderManager *pM,       //获取着色器
                                            unsigned int index);

Program *            CreateProgram();                                   //创建着色器程序
void                  DestoryProgram(Program *pProgram);              //销毁着色器程序

ProgramManager *    CreateProgramManager();                          //创建着色程序管理器
void                  DestoryProgramManager(ProgramManager *pM);    //销毁着色程序管理器
unsigned int         ProgramManagerAddProgram(ProgramManager *pM,  //添加着色器程序
                                        Program *pProgram);
Program *             ProgramManagerGet(ProgramManager *pM,         //着色器程序获取
                                        unsigned int index);
void                  ProgramManagerUseProgram(ProgramManager *pM,  //使用着色器程序
                                            unsigned int index);


SoundManager *      CreateSoundManager();                               //创建声音管理器
void                  DestorySoundManager(SoundManager *pM);          //销毁声音管理器

unsigned int        MakeID();                                            //产生一个不重复的ID值
unsigned long       GetTickCount();                                                     //获取毫秒数
BOOL                  LoadTexture(Texture *pTexture,const char *strFile);        //载入纹理
const char *         LoadTextFile(const char *strFile);                              //读取文本文件
BOOL                  LoadShader(Shader *pShader,const char *strFile,             //载入着色器
                                                    BOOL bFrag);
BOOL                  LoadProgram(Program *pProgram,Shader *pVertexShader,      //载入着色程序
                                        Shader *pFragShader);
void                  ShowImage(TextureManager *pM,unsigned int TexID,            //显示图像
                                        int x,int y,int sx,int sy,int w,int h);

#endif // SGENGINE_H_INCLUDED
