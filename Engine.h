#ifndef SGENGINE_H_INCLUDED
#define SGENGINE_H_INCLUDED

#include "Vector.h"

typedef void (*Func) ();                                 //函数回调

typedef struct tagSprite
{
    int x,y;
    Func DoCal;                                            //执行计算
    Func DoDraw;                                           //执行绘制
    Func DoEvents;                                         //执行事件
} Sprite;

typedef struct tagScene
{
    Vector *pSpriteVt;                                  //精灵向量
} Scene;

#endif // SGENGINE_H_INCLUDED
