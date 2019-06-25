
#include "BaseIncludes.h"
#include "SelectionBlock.cpp"

#define WINDOWWIDTH 640
#define WINDOWHEIGHT 480

void DrawLoop();
void SetQuestion();
void ResizeWindow(GLsizei, GLsizei);
void KeyboardInput(unsigned char, int, int);
void MouseInput(int button, int x, int y, int unknown);
void Startup(void);

SelectionBlock* blocks[3];
const int blocksQuantity = 3;
int correctResistor = 0;
std::string text;
int gameState = 0;

void DrawtextCustom(const char* text, int length, int x, int y)
{
	glMatrixMode(GL_PROJECTION);
	double* matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(0, WINDOWWIDTH, 0, WINDOWHEIGHT, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y);
	for (int i = 0; i < length; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
}


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

	glClearColor(0, 0, 0, 0);
#if !_MSC_VER
	system("clear");
#endif
	printf("Pressione Q para sair!\n");

	const int size = 100;
	const int padding = 15;
	const int insideBlockPadding = 5;

	SetQuestion();
	int initialPosition = (WINDOWWIDTH - (blocksQuantity * size + (blocksQuantity - 1) * padding)) / 2;
	for (int i = 0; i < blocksQuantity; i++)
	{
		auto selectionPosition = new CustomPrimitives::Rectangle(initialPosition + i * (size + padding), 25, size, size);
		auto resistorPosition = new CustomPrimitives::Rectangle(
			selectionPosition->x + insideBlockPadding,
			selectionPosition->y + selectionPosition->height / 4,	///Para começar 1/4 acima e terminar em 3/4
			selectionPosition->width - 2 * insideBlockPadding,
			selectionPosition->height / 2);

		auto resistorColors = new CustomPrimitives::Color[4];
		if (i == 0)
		{
			resistorColors[0].r = 0.6;
			resistorColors[0].g = 0.46;
			resistorColors[0].b = 0.32;
			resistorColors[2].r = 1;
			resistorColors[3].r = 0.8;
			resistorColors[3].g = 0.6;
			resistorColors[3].b = 0.2;
		}
		else if (i == 2)
		{
			resistorColors[0].r = 1;
			resistorColors[0].g = 0.65;
			resistorColors[0].b = 0.3;
			resistorColors[1].r = 1;
			resistorColors[1].g = 0.65;
			resistorColors[1].b = 0.3;
			resistorColors[2].r = 1;
			resistorColors[3].r = 0.8;
			resistorColors[3].g = 0.6;
			resistorColors[3].b = 0.2;
		}
		else
		{
			resistorColors[0].b = 1;
			resistorColors[1].r = 0.5;
			resistorColors[1].g = 0.5;
			resistorColors[1].b = 0.5;
			resistorColors[2].r = 1;
			resistorColors[3].r = 0.8;
			resistorColors[3].g = 0.6;
			resistorColors[3].b = 0.2;
		}

		auto resistor = new Resistor(resistorPosition, resistorColors, 4);
		blocks[i] = new SelectionBlock(selectionPosition, resistor);
	}
}

void SetQuestion()
{
	srand(time(NULL));
	auto random = rand() % 3;
	printf("Questão escolhida: %d\n", random);
	switch (random)
	{
	case 0:
	{
		text = "Qual resistor produzira 100mA numa tensao de 100V?";
		break;
	}
	case 1:
	{
		text = "Qual resistor numa tensao de 306V possui uma corrente de 45mA?";
		break;
	}
	case 2:
	{
		text = "Qual resistor produzira 20mA numa tensao de 66V?";
		break;
	}
	}
	correctResistor = random;
}


void DrawLoop()
{
	glClear(GL_COLOR_BUFFER_BIT);

	switch (gameState)
	{
	case 0:
		glColor3f(1, 1, 1);
		break;
	case 1:
		glColor3f(0, 1, 0);
		break;
	case 2:
		glColor3f(1, 0, 0);
		break;
	}
	DrawtextCustom(text.data(), text.size(), WINDOWWIDTH / 2 - text.size() * 5, WINDOWHEIGHT / 2 + 120);

	for (int i = 0; i < blocksQuantity; i++)
	{
		if (blocks[i] == NULL)
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
	y = 480 - y;
	if (state == GLUT_DOWN)
	{
		/*printf("Pegou\t");*/
	}
	else if (state == GLUT_UP)
	{
		if (gameState > 0)
		{
			gameState = 0;
			SetQuestion();
		}
		else
		{
			for (int i = 0; i < blocksQuantity; i++)
			{
				if (blocks[i]->IsInside(x, y))
				{
					if (i == correctResistor)
					{
						text = "Voce acertou!";
						gameState = 1;
					}
					else
					{
						text = "Errou, nao era o resistor certo!";
						gameState = 2;
					}

					DrawLoop();
					break;
				}
			}
		}
		//printf("Soltou\t");
	}
}