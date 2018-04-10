#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "Engine.h"

#define 				WND_W						400
#define				WND_H						600

extern Engine *pEngine;                                    //游戏引擎
extern SceneManager *pSceneManager;                      //场景管理器
extern EventManager *pEventManager;                      //事件管理器
extern CallManager *pCallManager;                        //回调管理器

extern Scene *pMainMenuScene;                            //主菜单场景
extern unsigned int BackgroundTexture;                  //背景纹理

void InitEnv();                                              //初始化环境
void InitGame();                                             //初始化游戏

void MainMenuSceneDoCal(Scene *pScene);                //主菜单场景计算
void MainMenuSceneDoDraw(Scene *pScene);               //主菜单场景绘制
void MainMenuSceneDoEvents(Scene *pScene);            //主菜单场景执行事件

void SetGameSceneDoCal(Scene *pScene);                 //设置游戏场景计算
void SetGameSceneDoDraw(Scene *pScene);                //设置游戏场景绘制
void SetGameSceneDoEvents(Scene *pScene);              //设置游戏执行事件

void AboutGameSceneDoCal(Scene *pScene);               //关于游戏计算
void AboutGameSceneDoDraw(Scene *pScene);              //关于游戏绘制
void AboutGameSceneDoEvents(Scene *pScene);            //关于游戏执行事件

void GameSceneDoInit(Scene *pScene);                    //游戏场景初始化
void GameSceneDoCal(Scene *pScene);                     //游戏场景计算
void GameSceneDoDraw(Scene *pScene);                    //游戏场景绘制
void GameSceneDoEvents(Scene *pScene);                  //游戏场景执行事件

#endif // GAME_H_INCLUDED
