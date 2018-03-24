#ifndef SGENGINE_H_INCLUDED
#define SGENGINE_H_INCLUDED

#include "Vector.h"

typedef void (*Func) ();                                 //函数回调

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
}

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
    Func DoCal;                                           //执行计算
    Func DoDraw;                                          //执行绘制
    Func DoEvents;                                       //执行事件
} Scene;

typedef struct tagSceneManager                                  //场景管理器
{
    Vector *pSceneVt;                                               //场景向量

    Func DoCal;                                                      //执行计算
    Func DoDraw;                                                     //执行绘制
    Func DoEvents;                                                  //执行事件
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
} Engine;

Engine *             CreateEngine();                              //创建引擎
void                  DestoryEngine(Engine *pEngine);          //销毁引擎

#endif // SGENGINE_H_INCLUDED
