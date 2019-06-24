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
}


class SelectionBlock
{
private:
	CustomPrimitives::Rectangle* rectangle;
public:
	SelectionBlock(CustomPrimitives::Rectangle* rectangle)
	{
		this->rectangle = rectangle;
	}


	/*SelectionBlock(CustomPrimitives::Rectangle rectangle)
	{
		this->rectangle = rectangle;
	}*/
	bool IsInside(int pointX, int pointY)
	{
		return rectangle->IsInside(pointX, pointY);
	}

	void Draw()
	{

	}


};
