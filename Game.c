#include <GL/gl.h>
#include "Engine.h"
#include "Game.h"

Scene *pMainMenuScene;
Texture *pBackgroundTexture;
Texture *pLogoTexture;
Texture *pStartGameTexture;
Texture *pSetGameTexture;
Texture *pAboutGameTexture;
Texture *pExitGameTexture;

void InitGame()
{
    TextureManager *pTextureManager=pEngine->pTextureManager;

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

void MainMenuSceneDoEvents(Scene *pScene)
{

}
