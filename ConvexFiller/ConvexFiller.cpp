void drawLine(Point startPoint, Point endPoint)
{
	int ixs = (int)startPoint.x; // converting all double variables to ints, as this algorithm works all integers
	int iys = (int)startPoint.y;
	int ixe = (int)endPoint.x;
	int iye = (int)endPoint.y;

	int deltaX = ixe - ixs;
	int deltaY = iye - iys;

	if (abs(deltaY) <= abs(deltaX))
	{
		if (ixs > ixe)
		{
			swap(ixs, ixe);
			swap(iys, iye);
		}

		deltaX = abs(deltaX);
		deltaY = abs(deltaY);
		int error = 2 * deltaY - deltaX;
		int d1 = 2 * deltaY;
		int d2 = 2 * (deltaY - deltaX);

		int x = ixs;
		int y = iys;

		int increment;
		if (iys < iye)
			increment = 1;
		else
			increment = -1;

		SetPixel(hdc, x, y, RGB(0, 0, 0));
		while (x < ixe)
		{
			if (error < 0)
				error += d1;
			else
			{
				error += d2;
				y += increment;
			}
			x++;
			SetPixel(hdc, x, y, RGB(0, 0, 0));
		}
	}
	else
	{
		if (iys > iye)
		{
			swap(ixs, ixe);
			swap(iys, iye);
		}

		deltaX = abs(deltaX);
		deltaY = abs(deltaY);

		int error = 2 * deltaX - deltaY;
		int d1 = 2 * deltaX;
		int d2 = 2 * (deltaX - deltaY);

		int x = ixs;
		int y = iys;

		int increment;
		if (ixs < ixe)
			increment = 1;
		else
			increment = -1;

		SetPixel(hdc, x, y, RGB(0, 0, 0));
		while (y < iye)
		{
			if (error < 0)
				error += d1;
			else
			{
				error += d2;
				x += increment;
			}
			y++;
			SetPixel(hdc, x, y, RGB(0, 0, 0));
		}
	}
}


void drawCircle(Point center, int radius)
{
	int x = 0;
	int y = radius;

	draw8Points(center, x, y);

	int d = 1 - radius;
	int d1 = 3;
	int d2 = 5 - (2 * radius);

	while (x < y)
	{
		if (d < 0)
		{
			d += d1;
			d2 += 2;
		}
		else
		{
			d += d2;
			d2 += 4;
			y--;
		}
		x++;
		d1 += 2;
		draw8Points(center, x, y);
	}
}


class EdgeRecord
{
public:
	int xLeft;
	int xRight;
	EdgeRecord()
	{
		xLeft = INT_MAX;
		xRight = INT_MIN;
	}
};


void convexFill(Point* points, int numberOfPoints)
{
	EdgeRecord *table = new EdgeRecord[800];
	Point v1 = points[numberOfPoints - 1];
	for (int i = 0;i < numberOfPoints;i++)
	{
		Point v2 = points[i];
		if (v1.y == v2.y)
			goto horizontal;
		if (v1.y > v2.y)
			swap(v1, v2);
		int y = v1.y;
		double x = v1.x;
		double mi = (v2.x - v1.x) / (double)(v2.y - v1.y);
		while (y < v2.y)
		{
			if (x < table[y].xLeft)
				table[y].xLeft = ceil(x);
			if (x > table[y].xRight)
				table[y].xRight = floor(x);
			x += mi;
			y++;
		}
	horizontal:v1 = points[i];
	}

	for (int i = 0;i < 800;i++)
	{
		if (table[i].xLeft < table[i].xRight)
			drawLine(Point(table[i].xLeft, i), Point(table[i].xRight, i));
	}
}

void ConvexFiller::fillCircle(Point center, int radius)
{
	for (int i = radius;i >= 0;i--)
		drawCircle(center, i);
}