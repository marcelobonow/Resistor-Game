
#if _MSC_VER
#include <Windows.h>
#define _USE_MATH_DEFINES
#endif
#include <cmath>
#include <iostream>
#include <fstream>
#include "GL/gl.h" 
#include "GL/glu.h" 
#include "GL/glut.h"
#include "SelectionBlock.cpp"

#define WINDOWWIDTH 640
#define WINDOWHEIGHT 480

void DrawLoop();
void ResizeWindow(GLsizei, GLsizei);
void KeyboardInput(unsigned char, int, int);
void MouseInput(int button, int x, int y, int unknown);
void Startup(void);

CustomPrimitives::Rectangle* rectangles[50];

int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WINDOWWIDTH, WINDOWHEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Resistor Match");
	glutDisplayFunc(DrawLoop);
	glutReshapeFunc(ResizeWindow);
	glutKeyboardFunc(KeyboardInput);
	glutMouseFunc(MouseInput);
	Startup();
	glutMainLoop();

	return 0;
}

void Startup(void)
{

	glClearColor(1, 1, 1, 0);
#if !_MSC_VER
	system("clear");
#endif
	printf("Press Q to quit...");

	const int size = 50;
	const int padding = 5;
	const int blocksQuantity = 5;
	int initialPosition = (WINDOWWIDTH - (blocksQuantity * size + (blocksQuantity - 1) * padding)) / 2;
	for (int i = 0; i < blocksQuantity; i++)
	{
		rectangles[i] = new CustomPrimitives::Rectangle(initialPosition + i * (size + padding), 25, size, size);
	}
}


void DrawLoop()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 1);
	for (int i = 0; i < 5; i++)
	{
		glBegin(GL_QUADS);
		auto rectangle = rectangles[i];
		printf("i: %d\n", i);
		printf("x: %d\n", rectangle->x);
		printf("y: %d\n", rectangle->y);
		printf("width: %d\n", rectangle->width);
		printf("height: %d\n", rectangle->height);
		printf("\n\n\n");
		glVertex2i(rectangle->x, rectangle->y);
		glVertex2i(rectangle->x + rectangle->width, rectangle->y);
		glVertex2i(rectangle->x + rectangle->width, rectangle->y + rectangle->height);
		glVertex2i(rectangle->x, rectangle->y + rectangle->height);
		glEnd();
	}
	glFlush();

	/*glBegin(GL_QUADS);
	glVertex2i(0, 0);
	glVertex2i(10, 0);
	glVertex2i(10, 50);
	glVertex2i(0, 50);
	glEnd();
	glBegin(GL_QUADS);
	glVertex2i(15, 0);
	glVertex2i(25, 0);
	glVertex2i(25, 50);
	glVertex2i(15, 50);
	glEnd();
	glFlush();*/

}

void ResizeWindow(GLsizei w, GLsizei h)
{

	if (h == 0)
		h = 1;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
		gluOrtho2D(0, WINDOWWIDTH, 0, WINDOWWIDTH * h / w);
	else
		gluOrtho2D(0, WINDOWHEIGHT * w / h, 0, WINDOWHEIGHT);

}

void KeyboardInput(unsigned char key, int x, int y)
{
	switch (key) {
	case 'Q':
	case 'q':
		exit(0);
		break;
	}

	glutPostRedisplay();
}
void MouseInput(int button, int state, int x, int y)
{
	printf("Button: %d\t", button);
	printf("x: %d\t", x);
	printf("y: %d\t", y);
	printf("state: %d\t", state);

	if (state == GLUT_DOWN)
	{
		printf("Pegou\t");
	}
	else if (state == GLUT_UP)
	{
		printf("Soltou\t");
	}
}