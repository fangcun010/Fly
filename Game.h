#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "Engine.h"

#define 				WND_W						400
#define				WND_H						600

#define              PLAYER_W                 60
#define              PLAYER_H                 80

#define              KEY_LEFT                 'j'
#define              KEY_RIGHT                'l'
#define              KEY_UP                   'i'
#define              KEY_DOWN                 'k'

typedef struct tagPlayer                                  //玩家信息
{
    int x,y;                                                //坐标
    int State;                                              //状态
} PlayerTag;

typedef struct tagEnemy                                   //敌人信息
{
    int x,y;                                                //坐标
    int vx,vy;
    int State;                                              //状态
    unsigned long lasttime;                               //上次时间
    int HP;                                                 //生命值
    Texture *pTexture;                                     //纹理
} EnemyTag;

typedef struct tagBullet                                  //子弹信息
{
    int State;
    int x,y;                                                //坐标
    int vx,vy;                                              //速度
    unsigned long lasttime;                               //上次时间
    int EnemyID;
    BOOL bEnemy;                                            //是否是敌人的子弹
} BulletTag;

extern Engine *pEngine;                                    //游戏引擎
extern SceneManager *pSceneManager;                      //场景管理器
extern EventManager *pEventManager;                      //事件管理器
extern CallManager *pCallManager;                        //回调管理器

extern Scene *pMainMenuScene;                            //主菜单场景
extern unsigned int BackgroundTexture;                  //背景纹理

extern int KeyState[256];                                 //按键状态

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

void PlayerDoInit(Sprite *pSprite);                     //执行玩家初始化
void PlayerDoCal(Sprite *pSprite);                      //执行玩家计算
void PlayerDoDraw(Sprite *pSprite);                     //执行玩家绘制
void PlayerDoEvents(Sprite *pSprite);                   //执行玩家事件

PlayerTag *CreatePlayerTag();                            //创建玩家信息
Sprite *CreateBullet(int x,int y,int vx,int vy);       //创建子弹
Sprite *CreateEnemey(Texture *pTexture,int HP          //创建敌人
                     ,int x,int y,int vx,int vy);
Sprite *CreateEnemyBullet(int x,int y,                  //创建敌人子弹
                            int vx,int vy);

void BulletDoInit(Sprite *pSprite);                     //子弹初始化
void BulletDoCal(Sprite *pSprite);                       //子弹计算
void BulletDoDraw(Sprite *pSprite);                     //子弹绘制
void BulletDoEvents(Sprite *pSprite);                   //子弹处理事件

void EnemyDoInit(Sprite *pSprite);                      //执行初始化
void EnemyDoCal(Sprite *pSprite);                       //执行计算
void EnemyDoDraw(Sprite *pSprite);                      //执行绘制
void EnemyDoEvents(Sprite *pSprite);                    //执行事件

void EnemyBulletDoInit(Sprite *pSprite);                //执行敌人子弹初始化
void EnemyBulletDoCal(Sprite *pSprite);                 //执行敌人子弹计算
void EnemyBulletDoDraw(Sprite *pSprite);                //执行敌人子弹绘制
void EnemyBulletDoEvents(Sprite *pSprite);              //执行敌人子弹事件

void ResetKeyState();                                     //重置按键状态

void GameOverSceneDoCal(Scene *pScene);
void GameOverSceneDoDraw(Scene *pScene);
void GameOverSceneDoEvents(Scene *pScene);

#endif // GAME_H_INCLUDED
