#include <GL/gl.h>
#include "Game.h"

Scene *pMainMenuScene;
unsigned int BackgroundTexture;

void InitGame()
{
    TextureManager *pTextureManager=pEngine->pTextureManager;

    pMainMenuScene=CreateScene();

    pMainMenuScene->DoCal=MainMenuSceneDoCal;
    pMainMenuScene->DoDraw=MainMenuSceneDoDraw;
    pMainMenuScene->DoEvents=MainMenuSceneDoEvents;

    Texture *pTexture=CreateTexture();

    LoadTexture(pTexture,"res/Background.RGBA");

    BackgroundTexture=pTextureManager->AddTexture(pTextureManager,pTexture);
}



void MainMenuSceneDoCal(Scene *pScene)
{
  //  TextureManager *pM=pEngine->pTextureManager;

//    pM->UseTexture(pM,BackgroundTexture);
}

void MainMenuSceneDoDraw(Scene *pScene)
{

}

void MainMenuSceneDoEvents(Scene *pScene)
{

}
