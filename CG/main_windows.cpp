
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

#define TAMJANELA 500
#define POSJANELA 50
#define TAMQUADRADO 50
#define POSINICIAL 20

int tx = 0, ty = 0, inc = 3;

void Inicializa(void)
{

	glClearColor(1, 1, 1, 0);
	system("clear");
	printf("Tecle:\n\n");
	printf("   [t] para translacao do desenho\n");
	printf("   [s] para sair do programa\n\n");
	printf("   [V] para aumentar a velocidade\n\n");
	printf("   [v] para diminuir a velocidade\n\n");

}

void Desenha(void) {

	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0, 0, 1);

	glBegin(GL_QUADS);
	glVertex2i(POSINICIAL + tx, POSINICIAL + ty);  // P0
	glVertex2i(POSINICIAL + TAMQUADRADO + tx, POSINICIAL + ty);  // P1
	glVertex2i(POSINICIAL + TAMQUADRADO + tx, POSINICIAL + TAMQUADRADO + ty);  // P2
	glVertex2i(POSINICIAL + tx, POSINICIAL + TAMQUADRADO + ty);  // P3
	glEnd();

	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);
	glVertex2i(250, 150);
	glVertex2i(300, 150);
	glVertex2i(300, 350);
	glVertex2i(250, 350);
	glEnd();

	glFlush();

}

void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{

	if (h == 0)
		h = 1;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
		gluOrtho2D(0, TAMJANELA, 0, TAMJANELA * h / w);
	else
		gluOrtho2D(0, TAMJANELA * w / h, 0, TAMJANELA);

}

void GerenciaTeclado(unsigned char tecla, int x, int y) {

	int realX = tx + POSINICIAL;
	int realY = ty + POSINICIAL;
	switch (tecla) {

	case 'D':
	case 'd':  if (realX <= (TAMJANELA - TAMQUADRADO) - inc &&
		(realX < (250 - TAMQUADRADO - inc) || realX > 300 || realY < (150 - TAMQUADRADO) || realY > 350))
		tx += inc;
		break;

	case 'E':
	case 'e':  if ((realX >= inc) &&
		(realX < (250 - TAMQUADRADO) || realX >(300 + inc) || realY < (150 - TAMQUADRADO) || realY > 350))
		tx -= inc;
		break;

	case 'C':
	case 'c':  if (realY <= (TAMJANELA - TAMQUADRADO - inc) &&
		(realX < (250 - TAMQUADRADO) || realX > 300 || realY < (150 - TAMQUADRADO - inc) || realY > 350))
		ty += inc;
		break;

	case 'B':
	case 'b':  if (realY >= inc &&
		(realX < (250 - TAMQUADRADO) || realX > 300 || realY < (150 - TAMQUADRADO) || realY >(350 + inc)))
		ty -= inc;
		break;

	case 'V':  inc += 2;
		break;

	case 'v':  if (inc >= 3)
		inc -= 2;
		break;

	case 'S':
	case 's':  exit(0);
		break;

	}

	glutPostRedisplay();

}


int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(TAMJANELA, TAMJANELA);
	glutInitWindowPosition(POSJANELA, POSJANELA);
	glutCreateWindow("TRANSLACAO");
	glutDisplayFunc(Desenha);
	glutReshapeFunc(AlteraTamanhoJanela);
	glutKeyboardFunc(GerenciaTeclado);
	Inicializa();
	glutMainLoop();

	return 0;
}