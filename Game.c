#include <GL/gl.h>
#include "Engine.h"
#include "Game.h"

//主菜单场景
Scene *pMainMenuScene;
Texture *pBackgroundTexture;
Texture *pLogoTexture;
Texture *pStartGameTexture;
Texture *pSetGameTexture;
Texture *pAboutGameTexture;
Texture *pExitGameTexture;

//设置游戏
Scene *pSetScene;
Texture *pSetBackgroundTexture;

//关于场景
Scene *pAboutScene=NULL;
Texture *pAboutBackgroundTexture;

//游戏场景
Scene *pGameScene;
Texture *pCurPlayerTexture;
Texture *pPlayerTexture[2];
Texture *pBulletTexture;
Sprite *pPlayer;
PlayerTag *pPlayerTag;
Texture *pEnemy1Texture;

int KeyState[256];

void InitGame()
{
    TextureManager *pTextureManager=pEngine->pTextureManager;

    //主菜单场景
    pMainMenuScene=CreateScene();

    pMainMenuScene->DoCal=MainMenuSceneDoCal;
    pMainMenuScene->DoDraw=MainMenuSceneDoDraw;
    pMainMenuScene->DoEvents=MainMenuSceneDoEvents;

    pBackgroundTexture=CreateTexture();
    pLogoTexture=CreateTexture();
    pStartGameTexture=CreateTexture();
    pSetGameTexture=CreateTexture();
    pAboutGameTexture=CreateTexture();
    pExitGameTexture=CreateTexture();

    LoadTexture(pBackgroundTexture,"res/Background.RGBA");
    LoadTexture(pLogoTexture,"res/Logo.RGBA");
    LoadTexture(pStartGameTexture,"res/StartGame.RGBA");
    LoadTexture(pSetGameTexture,"res/SetGame.RGBA");
    LoadTexture(pAboutGameTexture,"res/AboutGame.RGBA");
    LoadTexture(pExitGameTexture,"res/ExitGame.RGBA");

    pTextureManager->AddTexture(pTextureManager,pBackgroundTexture);
    pTextureManager->AddTexture(pTextureManager,pLogoTexture);
    pTextureManager->AddTexture(pTextureManager,pStartGameTexture);
    pTextureManager->AddTexture(pTextureManager,pSetGameTexture);
    pTextureManager->AddTexture(pTextureManager,pAboutGameTexture);
    pTextureManager->AddTexture(pTextureManager,pExitGameTexture);

    //设置游戏场景
    pSetScene=CreateScene();

    pSetScene->DoCal=SetGameSceneDoCal;
    pSetScene->DoDraw=SetGameSceneDoDraw;
    pSetScene->DoEvents=SetGameSceneDoEvents;

    pSetBackgroundTexture=CreateTexture();
    LoadTexture(pSetBackgroundTexture,"res/SetGameScene.RGBA");

    pTextureManager->AddTexture(pTextureManager,pSetBackgroundTexture);

    //关于游戏场景

    pAboutScene=CreateScene();

    pAboutScene->DoCal=AboutGameSceneDoCal;
    pAboutScene->DoDraw=AboutGameSceneDoDraw;
    pAboutScene->DoEvents=AboutGameSceneDoEvents;

    pAboutBackgroundTexture=CreateTexture();
    LoadTexture(pAboutBackgroundTexture,"res/AboutGameScene.RGBA");

    pTextureManager->AddTexture(pTextureManager,pAboutBackgroundTexture);

    //游戏场景
    pGameScene=CreateScene();

    pGameScene->DoInit=GameSceneDoInit;
    pGameScene->DoCal=GameSceneDoCal;
    pGameScene->DoDraw=GameSceneDoDraw;
    pGameScene->DoEvents=GameSceneDoEvents;

    pPlayerTexture[0]=CreateTexture();
    pPlayerTexture[1]=CreateTexture();

    LoadTexture(pPlayerTexture[0],"res/Player1.RGBA");
    LoadTexture(pPlayerTexture[1],"res/Player2.RGBA");

    pTextureManager->AddTexture(pTextureManager,pPlayerTexture[0]);
    pTextureManager->AddTexture(pTextureManager,pPlayerTexture[1]);

    pPlayer=CreateSprite();

    pPlayer->DoInit=PlayerDoInit;
    pPlayer->DoCal=PlayerDoCal;
    pPlayer->DoDraw=PlayerDoDraw;
    pPlayer->DoEvents=PlayerDoEvents;

    pPlayerTag=CreatePlayerTag();
    pPlayerTag->x=(WND_W-PLAYER_W)/2;
    pPlayerTag->y=50;

    pBulletTexture=CreateTexture();

    LoadTexture(pBulletTexture,"res/Bullet.RGBA");

    pGameScene->AddSprite(pGameScene,pPlayer);

    pEnemy1Texture=CreateTexture();
    LoadTexture(pEnemy1Texture,"res/Enemy1.RGBA");
}

void MainMenuSceneDoCal(Scene *pScene)
{
  //  TextureManager *pM=pEngine->pTextureManager;

//    pM->UseTexture(pM,BackgroundTexture);
}

void MainMenuSceneDoDraw(Scene *pScene)
{
    TextureManager *pM=pEngine->pTextureManager;

    ShowImage(pBackgroundTexture,0,0,WND_W,WND_H);
    ShowImage(pLogoTexture,70,500,256,64);

    ShowImage(pStartGameTexture,130,350,
              pStartGameTexture->Width,pStartGameTexture->Height);
    ShowImage(pSetGameTexture,130,300,
              pSetGameTexture->Width,pSetGameTexture->Height);
    ShowImage(pAboutGameTexture,130,250,
              pAboutGameTexture->Width,pAboutGameTexture->Height);
    ShowImage(pExitGameTexture,130,200,
              pExitGameTexture->Width,pExitGameTexture->Height);
}

static void NewGame(void *pData)
{
    puts("New Game");
    pSceneManager->RemoveScene(pSceneManager,pMainMenuScene->ID);
    pSceneManager->AddScene(pSceneManager,pGameScene);
}

static void SetGame(void *pData)
{
    puts("Set Game");
}

static void AboutGame(void *pData)
{
    puts("About Game");
    pMainMenuScene->bDoEvents=FALSE;

    pSceneManager->AddScene(pSceneManager,pAboutScene);
}

static void ExitGame(void *pData)
{
    puts("Exit Game");

    pEngine->bLeaveLoop=TRUE;
}

void SetGameSceneDoCal(Scene *pScene)
{

}

void SetGameSceneDoDraw(Scene *pScene)
{
    ShowImage(pBackgroundTexture,0,0,WND_W,WND_H);
}

void SetGameSceneDoEvents(Scene *pScene)
{

}

void AboutGameSceneDoCal(Scene *pScene)
{

}

void AboutGameSceneDoDraw(Scene *pScene)
{
    ShowImage(pAboutBackgroundTexture,100,250,
                pAboutBackgroundTexture->Width,pAboutBackgroundTexture->Height);
}

static void RemoveAboutScene(void *pData)
{
    Scene *pScene=pSceneManager->RemoveScene(pSceneManager,pAboutScene->ID);
    pMainMenuScene->bDoEvents=TRUE;
}

void AboutGameSceneDoEvents(Scene *pScene)
{
    Vector *pVt=pEventManager->pEventVt;

    for(int i=0;i<vtCount(pVt);i++)
    {
        Event *pEvent=vtGet(pVt,i);

        if(pEvent->nEventID==EVENT_CLICK)
        {
            ClickEvent *pClickEvent=pEvent->pTag;

            if(pClickEvent->bDown)
            {
                Call *pCall=CreateCall(RemoveAboutScene,NULL);
                pCallManager->AddCall(pCallManager,pCall);
            }
        }
    }
}

void MainMenuSceneDoEvents(Scene *pScene)
{
    if(!pScene->bDoEvents) return;

    Vector *pVt=pEventManager->pEventVt;

    for(int i=0;i<vtCount(pVt);i++)
    {
        Event *pEvent=vtGet(pVt,i);

        if(pEvent->nEventID==EVENT_CLICK)
        {
            ClickEvent *pClickEvent=pEvent->pTag;
            int x=pClickEvent->x;
            int y=pClickEvent->y;

            if(pClickEvent->bDown)
            {
                if(IsInRect(x,y,130,350,140,30))//新的游戏
                {
                    Call *pCall=CreateCall(NewGame,NULL);
                    pCallManager->AddCall(pCallManager,pCall);
                }
                else if(IsInRect(x,y,130,300,140,30))//游戏设置
                {
                    Call *pCall=CreateCall(SetGame,NULL);
                    pCallManager->AddCall(pCallManager,pCall);
                }
                else if(IsInRect(x,y,130,250,140,30))//关于游戏
                {
                    Call *pCall=CreateCall(AboutGame,NULL);
                    pCallManager->AddCall(pCallManager,pCall);
                }
                else if(IsInRect(x,y,130,200,140,30))//退出游戏
                {
                    Call *pCall=CreateCall(ExitGame,NULL);
                    pCallManager->AddCall(pCallManager,pCall);
                }
            }
        }
    }
}

void GameSceneDoInit(Scene *pScene)
{
}

void GameSceneDoCal(Scene *pScene)
{
    static unsigned long lasttime;

    SpriteManager *pM=pScene->pSpriteManager;

    if(GetTickCount()-lasttime>800)
    {
        lasttime=GetTickCount();
    }

    pM->DoCal(pM);
}

void GameSceneDoDraw(Scene *pScene)
{
    static unsigned long lasttime;
    static int lastpos=0;
    SpriteManager *pM=pScene->pSpriteManager;

    if(GetTickCount()-lasttime>300)
    {
        lastpos-=5;

        if(lastpos<=-WND_H) lastpos=0;
    }

    ShowImage(pBackgroundTexture,0,lastpos,WND_W,WND_H);
    ShowImage(pBackgroundTexture,0,lastpos+WND_H,WND_W,WND_H);

    pM->DoDraw(pM);
}

void GameSceneDoEvents(Scene *pScene)
{
    SpriteManager *pM=pScene->pSpriteManager;

    pM->DoEvents(pM);
}

void PlayerDoInit(Sprite *pSprite)
{

}

static void PlayerUseBullet(void *pData)
{
    Sprite *pBullet=CreateBullet(pPlayerTag->x+4,pPlayerTag->y+35,0,10);
    pGameScene->AddSprite(pGameScene,pBullet);
    pBullet=CreateBullet(pPlayerTag->x+44,pPlayerTag->y+35,0,10);
    pGameScene->AddSprite(pGameScene,pBullet);
}

void PlayerDoCal(Sprite *pSprite)
{
    if(KeyState[KEY_LEFT])
    {
        pPlayerTag->x-=5;
    }
    if(KeyState[KEY_RIGHT])
    {
        pPlayerTag->x+=5;
    }
    if(KeyState[KEY_UP])
    {
        pPlayerTag->y+=5;
    }
    if(KeyState[KEY_DOWN])
    {
        pPlayerTag->y-=5;
    }

    if(pPlayerTag->x<0) pPlayerTag->x=0;
    if(pPlayerTag->x+PLAYER_W>WND_W) pPlayerTag->x=WND_W-PLAYER_W;
    if(pPlayerTag->y<0) pPlayerTag->y=0;
    if(pPlayerTag->y+PLAYER_H>WND_H) pPlayerTag->y=WND_H-PLAYER_H;

    if(KeyState['a'])
    {
        static unsigned long lasttime;

        if(GetTickCount()-lasttime>100)
        {
            Call *pCall=CreateCall(PlayerUseBullet,NULL);
            pCallManager->AddCall(pCallManager,pCall);
            lasttime=GetTickCount();
        }
    }
}

void PlayerDoDraw(Sprite *pSprite)
{
    static unsigned long lasttime;

    if(pPlayerTag->State==0)
    {
        static int index=0;

        if(GetTickCount()-lasttime>100)
        {
            index++;
            index%=2;
            lasttime=GetTickCount();
        }
        ShowImage(pPlayerTexture[index],pPlayerTag->x,pPlayerTag->y
                ,PLAYER_W,PLAYER_H);
    }
}

void PlayerDoEvents(Sprite *pSprite)
{
    Vector *pVt=pEventManager->pEventVt;

    for(int i=0;i<vtCount(pVt);i++)
    {
        Event *pEvent=vtGet(pVt,i);

        if(pEvent->nEventID==EVENT_KEY)
        {
            KeyEvent *pKeyEvent=pEvent->pTag;

            if(pKeyEvent->bDown)
            {
                KeyState[pKeyEvent->key]=TRUE;
            }
            else
            {
                KeyState[pKeyEvent->key]=FALSE;
            }
        }
    }
}

PlayerTag *CreatePlayerTag()
{
    PlayerTag *pPlayerTag=malloc(sizeof(PlayerTag));

    pPlayerTag->State=0;
    pPlayerTag->x=0;
    pPlayerTag->y=0;

    return pPlayerTag;
}

Sprite *CreateBullet(int x,int y,int vx,int vy)
{
    Sprite *pSprite=CreateSprite();
    BulletTag *pBulletTag=malloc(sizeof(BulletTag));

    pBulletTag->x=x;pBulletTag->y=y;
    pBulletTag->vx=vx;pBulletTag->vy=vy;

    pSprite->pTag=pBulletTag;

    pSprite->DoInit=BulletDoInit;
    pSprite->DoCal=BulletDoCal;
    pSprite->DoDraw=BulletDoDraw;
    pSprite->DoEvents=BulletDoEvents;

    return pSprite;
}

void BulletDoInit(Sprite *pSprite)
{

}

static void RemoveBullet(void *pData)
{
    Sprite *pSprite=pData;

    pGameScene->RemoveSprite(pGameScene,pSprite->ID);
    DestorySprite(pSprite);
}

void BulletDoCal(Sprite *pSprite)
{
    BulletTag *pTag=pSprite->pTag;

    pTag->x+=pTag->vx;
    pTag->y+=pTag->vy;

    if(pTag->y<-50 || pTag->y>WND_H+50 || pTag->x<-50 || pTag->x>WND_W+50)
    {
        Call *pCall=CreateCall(RemoveBullet,pSprite);

        pCallManager->AddCall(pCallManager,pCall);
    }

}

void BulletDoDraw(Sprite *pSprite)
{
    BulletTag *pTag=pSprite->pTag;

    ShowImage(pBulletTexture,pTag->x,pTag->y,
              pBulletTexture->Width,pBulletTexture->Height);
}

void BulletDoEvents(Sprite *pSprite)
{

}

Sprite *CreateEnemey(Texture *pTexture,int HP,int x,int y,int vx,int vy)
{
    Sprite *pSprite=CreateSprite();
    EnemyTag *pTag=malloc(sizeof(EnemyTag));

    pTag->HP=HP;
    pTag->pTexture=pTexture;
    pTag->State=0;
    pTag->x=x;
    pTag->y=y;
    pTag->vx=vx;
    pTag->vy=vy;

    pSprite->pTag=pTag;

    pSprite->DoInit=EnemyDoInit;
    pSprite->DoCal=EnemyDoCal;
    pSprite->DoDraw=EnemyDoDraw;
    pSprite->DoEvents=EnemyDoEvents;

    return pSprite;
}

void EnemyDoInit(Sprite *pSprite)
{

}

void EnemyDoCal(Sprite *pSprite)
{

}

void EnemyDoDraw(Sprite *pSprite)
{

}

void EnemyDoEvents(Sprite *pSprite)
{

}

void ResetKeyState()
{
    memset(KeyState,0,sizeof(KeyState));
}

