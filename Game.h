#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "Engine.h"

#define 				WND_W						400
#define				WND_H						600

extern Engine *pEngine;                                    //游戏引擎

extern Scene *pMainMenuScene;                            //主菜单场景
extern unsigned int BackgroundTexture;                 //背景纹理

void InitEnv();                                              //初始化环境
void InitGame();                                             //初始化游戏

void MainMenuSceneDoCal(Scene *pScene);                //主菜单场景计算
void MainMenuSceneDoDraw(Scene *pScene);               //主菜单场景绘制
void MainMenuSceneDoEvents(Scene *pScene);            //主菜单场景执行事件

#endif // GAME_H_INCLUDED
