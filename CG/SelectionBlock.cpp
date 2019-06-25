#pragma once
#include "BaseIncludes.h"

namespace CustomPrimitives
{
	struct Rectangle
	{
	public:
		int x, y, width, height;
		Rectangle(int x, int y, int width, int height)
		{
			this->x = x;
			this->y = y;
			this->width = width;
			this->height = height;
		}
		bool IsInside(int pointX, int pointY)
		{
			return pointX > x
				&& pointX < x + width
				&& pointY > y
				&& pointY < y + height;
		}
	};
	struct Color
	{
	public:
		float r, g, b;
		Color(float r, float g, float b)
		{
			this->r = r;
			this->g = g;
			this->b = b;
		}
		Color()
		{
			r = g = b = 0;
		}
	};
}

class Resistor
{
private:
	CustomPrimitives::Rectangle* base;
	CustomPrimitives::Color* colors;
	unsigned int colorsLength;
	const int colorPadding = 2;
	const int colorSize = 15;
public:
	Resistor(CustomPrimitives::Rectangle* base, CustomPrimitives::Color* colors, unsigned int colorsLength)
	{
		this->base = base;
		this->colors = colors;
		this->colorsLength = colorsLength;
	}
	Resistor()
	{

	}

	void Draw()
	{
		glColor3f(0.882, 0.737, 0.482);
		glBegin(GL_QUADS);
		glVertex2i(base->x, base->y);
		glVertex2i(base->x + base->width, base->y);
		glVertex2i(base->x + base->width, base->y + base->height);
		glVertex2i(base->x, base->y + base->height);
		glEnd();

		for (int i = 0; i < colorsLength; i++)
		{
			auto color = colors[i];
			auto padding = colorPadding;
			if (i == colorsLength - 1)
				padding = colorPadding + 5;
			glColor3f(color.r, color.g, color.b);
			glBegin(GL_QUADS);
			glVertex2i(base->x + i * (padding + colorSize), base->y);
			glVertex2i(base->x + i * (padding + colorSize) + colorSize, base->y);
			glVertex2i(base->x + i * (padding + colorSize) + colorSize, base->y + base->height);
			glVertex2i(base->x + i * (padding + colorSize), base->y + base->height);
			glEnd();
		}
	}
};

class SelectionBlock
{
private:
	CustomPrimitives::Rectangle* rectangle;
	Resistor* resistor;

public:
	SelectionBlock(CustomPrimitives::Rectangle* rectangle, Resistor* resistor)
	{
		this->rectangle = rectangle;
		this->resistor = resistor;
	}

	void PrintRectangle()
	{
		glColor3f(0.4, 0.4, 0.4);
		glBegin(GL_QUADS);
		glVertex2i(rectangle->x, rectangle->y);
		glVertex2i(rectangle->x + rectangle->width, rectangle->y);
		glVertex2i(rectangle->x + rectangle->width, rectangle->y + rectangle->height);
		glVertex2i(rectangle->x, rectangle->y + rectangle->height);
		glEnd();
	}
	bool IsInside(int pointX, int pointY)
	{
		return rectangle->IsInside(pointX, pointY);
	}

	void Draw()
	{
		PrintRectangle();
		resistor->Draw();
	}


};
