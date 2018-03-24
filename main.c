#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include "Engine.h"

#define 				WND_W						400
#define				WND_H						600

Engine *pEngine;

void Display()
{
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);

	glutSwapBuffers();
}

int main(int argc,char *argv[])
{
	glutInit(&argc,argv);

	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);

	glutInitWindowSize(WND_W,WND_H);
	glutCreateWindow("Fly");

	glutDisplayFunc(Display);

	glewInit();

	glutMainLoop();

    return 0;
}
