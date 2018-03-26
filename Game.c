#include <GL/gl.h>
#include "Game.h"

Scene *pMainMenuScene;

void InitGame()
{
    pMainMenuScene=CreateScene();

    pMainMenuScene->DoCal=MainMenuSceneDoCal;
    pMainMenuScene->DoDraw=MainMenuSceneDoDraw;
    pMainMenuScene->DoEvents=MainMenuSceneDoEvents;
}

void MainMenuSceneDoCal(Scene *pScene)
{

}

void MainMenuSceneDoDraw(Scene *pScene)
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void MainMenuSceneDoEvents(Scene *pScene)
{

}



