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
Scene *pAboutScene;
Texture *pAboutBackgroundTexture;

//游戏场景
Scene *pGameScene;

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

    pGameScene->DoCal=GameSceneDoCal;
    pGameScene->DoDraw=GameSceneDoDraw;
    pGameScene->DoEvents=GameSceneDoEvents;
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
}

void GameSceneDoDraw(Scene *pScene)
{

}

void GameSceneDoEvents(Scene *pScene)
{

}
