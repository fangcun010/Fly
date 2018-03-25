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

typedef struct tagSprite                               //精灵
{
    Func DoCal;                                            //执行计算
    Func DoDraw;                                           //执行绘制
    Func DoEvents;                                        //执行事件　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　//执行事件
} Sprite;

typedef struct tagSpriteManager                      //精灵管理器
{
    Vector *pSpriteVt;                                   //精灵向量
} SpriteManager;

typedef struct tagCallManager                        //回调管理器
{
    Vector *pCallVt;                                     //回调向量
} CallManager;

typedef struct tagTextureManager                     //纹理管理器
{
    Vector *pTextureVt;                                  //纹理向量
} TextureManager;

typedef struct tagSoundManager                       //声音管理器
{
    Vector *pSoundVt;
} SoundManager;

typedef struct tagScene                                //场景
{
    Vector *pSpriteVt;                                   //精灵向量
    ObjFunc DoCal;                                           //执行计算
    ObjFunc DoDraw;                                          //执行绘制
    ObjFunc DoEvents;                                       //执行事件
} Scene;

typedef struct tagSceneManager                                  //场景管理器
{
    Vector *pSceneVt;                                               //场景向量

    ObjFunc DoCal;                                                      //执行计算
    ObjFunc DoDraw;                                                     //执行绘制
    ObjFunc DoEvents;                                                  //执行事件
} SceneManager;

typedef struct tagEvent                                          //事件
{
    int nEventID;                                                   //事件ID
    void *pTag;                                                      //事件附加信息
} Event;

typedef struct tagEventManager                                  //事件管理器
{
    Vector *pEventVt;                                               //事件向量

} EventManager;

typedef struct tagShader                                           //着色器
{

} Shader;

typedef struct tagShderManager                                  //着色器管理器
{
    Vector *pShaderVt;                                              //着色器向量
} ShaderManager;

typedef struct tagEngine                                          //引擎
{
    SceneManager *pSceneManager;                                 //场景管理器
    TextureManager *pTextureManager;                            //纹理管理器
    SoundManager *pSoundManager;                                 //声音管理器

    ObjFunc WaitForFrameTime;                                     //等待刷新时间

    unsigned long nLastFrameTime;                                //上一次
    BOOL bLeaveLoop;                                                //是否跳出游戏循环
} Engine;

Engine *             CreateEngine();                                  //创建引擎
void                  DestoryEngine(Engine *pEngine);             //销毁引擎
void                  WaitForFrameTime(Engine *pEngine);         //等待帧时间

SceneManager *      CreateSceneManager();                                //创建场景管理器
void                  DestorySceneManager(SceneManager *pM);           //销毁场景管理器
void                  SceneManagerDoCal(SceneManager *pM);             //计算
void                  SceneManagerDoDraw(SceneManager *pM);            //绘制
void                  SceneManagerDoEvents(SceneManager *pM);          //执行事件

TextureManager *   CreateTextureManager();                             //创建纹理管理器
void                  DestoryTextureManager(TextureManager *pM);     //销毁纹理管理器

SoundManager *      CreateSoundManager();                               //创建声音管理器
void                  DestorySoundManager(SoundManager *pM);          //销毁声音管理器

unsigned long       GetTickCount();                              //获取毫秒数

#endif // SGENGINE_H_INCLUDED
