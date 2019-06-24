
#include "BaseIncludes.h"
#include "SelectionBlock.cpp"

#define WINDOWWIDTH 640
#define WINDOWHEIGHT 480

void DrawLoop();
void ResizeWindow(GLsizei, GLsizei);
void KeyboardInput(unsigned char, int, int);
void MouseInput(int button, int x, int y, int unknown);
void Startup(void);

SelectionBlock* blocks[50];

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

	const int size = 100;
	const int padding = 15;
	const int insideBlockPadding = 5;
	const int blocksQuantity = 5;
	int initialPosition = (WINDOWWIDTH - (blocksQuantity * size + (blocksQuantity - 1) * padding)) / 2;
	for (int i = 0; i < blocksQuantity; i++)
	{
		auto selectionPosition = new CustomPrimitives::Rectangle(initialPosition + i * (size + padding), 25, size, size);
		auto resistorPosition = new CustomPrimitives::Rectangle(
			selectionPosition->x + insideBlockPadding,
			selectionPosition->y + selectionPosition->height / 4,	///Para começar 1/4 acima e terminar em 3/4
			selectionPosition->width - 2 * insideBlockPadding,
			selectionPosition->height / 2);

		CustomPrimitives::Color* resistorColors[4];
		resistorColors[0] = new CustomPrimitives::Color(0.6f, 0.46, 0.32);
		resistorColors[1] = new CustomPrimitives::Color(0, 0, 0);
		resistorColors[2] = new CustomPrimitives::Color(1, 0, 0);
		resistorColors[3] = new CustomPrimitives::Color(0.8, 0.6, 0.2);
		auto resistor = new Resistor(resistorPosition, resistorColors, 4);
		blocks[i] = new SelectionBlock(selectionPosition, resistor);
	}
}


void DrawLoop()
{
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < 5; i++)
	{
		if (blocks[i] == nullptr)
			break;
		auto block = blocks[i];
		block->Draw();
	}
	glFlush();
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