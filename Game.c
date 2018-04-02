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

   // glBindTexture(GL_TEXTURE_2D,pTexture->TexID);
   glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
glPointSize(10);
glEnable (GL_POINT_SMOOTH);
glHint (GL_POINT_SMOOTH, GL_NICEST);
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
