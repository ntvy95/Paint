#include "DrawingAlgorithm.h"
#include "Seed.h"
#include "Procedure.h"
#include <queue>
#include "Global.h"
#include <math.h>
#include "Event.h"
#include "graphics.h"
#pragma comment(lib, "graphics.lib")
using std::queue;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: LineBresenham.
* INPUT: int x1, int y1, int x2, int y2, int color.
* OUTPUT: void.
* DESCRIPTION: This is a line drawing procedure that uses Bresenham algorithm.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void LineBresenham(int x1, int y1, int x2, int y2, int color) {
	int	dx = x2 - x1,
		dy = y2 - y1,
		minx = Min(x1, x2),
		miny = Min(y1, y2),
		maxx = Max(x1, x2),
		maxy = Max(y1, y2); //The cost of this Line is too low compared to the code below
	//(which has so many calls to putpixel procedure)
	//so we will not try to optimize it to keep it clear.

	if (dx) {
		float m = (float)dy / dx;
		if (m == 0) { //parallel to x-axis.
			for (int x = minx; x < maxx; x++) {
				putpixel(x, miny, color);
			}
		}
		else if (m > 1) {
			dy = abs(dy);
			dx = abs(dx);
			int P = 2 * dx - dy, x = minx;
			for (int y = miny; y < maxy; y++) {
				putpixel(x, y, color);
				if (P < 0) {
					P = P + 2 * dx;
				}
				else {
					P = P + 2 * (dx - dy);
					x = x + 1;
				}
			}
		}
		else if (m < -1) {
			dy = abs(dy);
			dx = -abs(dx);
			int P = -2 * dx - dy, x = maxx;
			for (int y = miny; y < maxy; y++) {
				putpixel(x, y, color);
				if (P < 0) {
					P = P - 2 * dx;
				}
				else {
					P = P - 2 * (dx + dy);
					x = x - 1;
				}
			}
		}
		else if (m > 0) { //m > 0 && m < 1
			dy = abs(dy);
			dx = abs(dx);
			int P = 2 * dy - dx, y = miny;
			for (int x = minx; x < maxx; x++) {
				putpixel(x, y, color);
				if (P < 0) {
					P = P + 2 * dy;
				}
				else {
					P = P + 2 * (dy - dx);
					y = y + 1;
				}
			}
		}
		else { //m < 0 && m > -1
			dy = -abs(dy);
			dx = abs(dx);
			int P = -2 * dy - dx, y = maxy;
			for (int x = minx; x < maxx; x++) {
				putpixel(x, y, color);
				if (P < 0) {
					P = P - 2 * dy;
				}
				else {
					P = P - 2 * (dy + dx);
					y = y - 1;
				}
			}
		}
	}
	else { //parallel to y-axis.
		for (int y = miny; y < maxy; y++){
			putpixel(minx, y, color);
		}
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: CircleMidpoint.
* INPUT: int a, int b, int R, int color.
* OUTPUT: void.
* DESCRIPTION: This is a circle drawing procedure that uses Midpoint algorithm.
Inside this procedure, we also use a sub procedure called Put8.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CircleMidpoint(int a, int b, int R, int color) {
	if (R > 0) {
		int x = 0, y = R, f = 1 - R;
		while (y >= x) {
			Put8(a, b, x, y, color);
			if (f < 0) {
				f = f + 2 * x + 1;
			}
			else {
				y = y - 1;
				f = f + 2 * (x - y) + 1;
			}
			x = x + 1;
		}
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: Put8.
* INPUT: int a, int b, int x, int y, int color.
* OUTPUT: void.
* DESCRIPTION: If you can determine one (x, y) point on the circle, you can
determine the other seven points on the circle. This procedure basically
support any circle drawing procedure - which is CircleMidpoint procedure.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void Put8(int a, int b, int x, int y, int color)
{
	putpixel(x + a, y + b, color);
	putpixel(x + a, -y + b, color);
	putpixel(y + a, x + b, color);
	putpixel(y + a, -x + b, color);
	putpixel(-x + a, y + b, color);
	putpixel(-x + a, -y + b, color);
	putpixel(-y + a, x + b, color);
	putpixel(-y + a, -x + b, color);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: CircleMidpoint.
* INPUT: int x1, int y1, int x2, int y2, int color.
* OUTPUT: void.
* DESCRIPTION: Draw a counter-clockwise circle (zero degree base is on the right)
based on its two input points: One point at the 135 degree position, one point
at the 315 degree position. Though, this is an unused procedure in this project.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CircleMidpoint(int x1, int y1, int x2, int y2, int color) {
	int a = (x1 + x2) / 2,
		b = (y1 + y2) / 2,
		R = (int)round(distance(x1, y1, a, b));
	CircleMidpoint(a, b, R, color);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: ArcMidpoint.
* INPUT: int a, int b, int stangle, int endangle, int R, int color.
* OUTPUT: void.
* DESCRIPTION: Draw an arc from stangle angle to endangle angle of a 
counter-clockwise circle (zero degree base is on the right) with (a ; b) as
center point and R as radius.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void ArcMidpoint(int a, int b, int stangle, int endangle, int R, int color) {
	if (R > 0) {
		int x = 0, y = R, f = 1 - R;
		if (stangle < endangle) {
			while (y >= x) {
					ArcPut8right(x, y, a, b, stangle, endangle, R, color);
				if (f < 0) {
					f = f + 2 * x + 1;
				}
				else {
					y = y - 1;
					f = f + 2 * (x - y) + 1;
				}
				x = x + 1;
			}
		}
		else {
			//Sometimes one circle rotation direction is not enough, we have to use
			//a clockwise circle with zero degree base is on the left. At this time,
			//the new degree is symmetric to the old degree through line y = b.
			if (stangle > 180) {
				stangle = 540 - stangle;
			}
			else {
				stangle = 180 - stangle;
			}
			swap(stangle, endangle);
			while (y >= x) {
				ArcPut8left(x, y, a, b, stangle, endangle, R, color);
				if (f < 0) {
					f = f + 2 * x + 1;
				}
				else {
					y = y - 1;
					f = f + 2 * (x - y) + 1;
				}
				x = x + 1;
			}
		}
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: ArcPut8right.
* INPUT: int x, int y, int a, int b, int stangle, int endangle, int R, int color.
* OUTPUT: void.
* DESCRIPTION: Determine if the examining point and its seven other symmetric
points are on the arc. It is used for counter-clockwise circle (zero degree
base is on the right). In this project, this procedure supports ArcMidpoint
procedure.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void ArcPut8right(int x, int y, int a, int b, int stangle, int endangle, int R, int color) {
	int angle = (int)(toDegree((float)atan2(y, x)));

	//0 to 45
	if (90 - angle >= stangle && 90 - angle <= endangle) {
		putpixel(y + a, - x + b, color);
	}

	//45 to 90
	if (angle >= stangle && angle <= endangle) {
		putpixel(x + a, - y + b, color);
	}

	//90 to 135
	if (180 - angle >= stangle && 180 - angle <= endangle) {
		putpixel(- x + a, - y + b, color);
	}

	//135 to 180
	if (angle + 90 >= stangle && angle + 90 <= endangle) {
		putpixel(- y + a, - x + b, color);
	}

	//180 to 225
	if (270 - angle >= stangle && 270 - angle <= endangle) {
		putpixel(- y + a, x + b, color);
	}

	//225 to 270
	if (angle + 180 >= stangle && angle + 180 <= endangle) {
		putpixel(- x + a, y + b, color);
	}

	//270 to 315
	if (360 - angle >= stangle && 360 - angle <= endangle) {
		putpixel(x + a, y + b, color);
	}

	//315 to 360
	if (angle + 270 >= stangle && angle + 270 <= endangle) {
		putpixel(y + a, x + b, color);
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: ArcPut8left.
* INPUT: int x, int y, int a, int b, int stangle, int endangle, int R, int color.
* OUTPUT: void.
* DESCRIPTION: Determine if the examining point and its seven other symmetric
points are on the arc. It is used for clockwise circle (zero degree
base is on the left). In this project, this procedure supports ArcMidpoint
procedure.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void ArcPut8left(int x, int y, int a, int b, int stangle, int endangle, int R, int color) {
	int angle = (int)(toDegree((float)atan2(y, x)));

	//0 to 45
	if (90 - angle >= stangle && 90 - angle <= endangle) {
		putpixel(a - y, b - x, color);
	}

	//45 to 90
	if (angle >= stangle && angle <= endangle) {
		putpixel(a - x, b - y, color);
	}

	//90 to 135
	if (180 - angle >= stangle && 180 - angle <= endangle) {
		putpixel(a + x, b - y, color);
	}

	//135 to 180
	if (angle + 90 >= stangle && angle + 90 <= endangle) {
		putpixel(a + y, b - x, color);
	}

	//180 to 225
	if (270 - angle >= stangle && 270 - angle <= endangle) {
		putpixel(a + y, b + x, color);
	}

	//225 to 270
	if (angle + 180 >= stangle && angle + 180 <= endangle) {
		putpixel(a + x, b + y, color);
	}

	//270 to 315
	if (360 - angle >= stangle && 360 - angle <= endangle) {
		putpixel(a - x, b + y, color);
	}

	//315 to 360
	if (angle + 270 >= stangle && angle + 270 <= endangle) {
		putpixel(a - y, b + x, color);
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: SquareBresenham.
* INPUT: int x1, int y1, int a, int color.
* OUTPUT: void.
* DESCRIPTION: Drawing a square based on its top left point position and its
edge width. This use LineBresenham procedure.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void SquareBresenham(int x1, int y1, int a, int color) {
	int x2 = x1 + a,
		y2 = y1 + a;
	LineBresenham(x1, y1, x2, y1, color);
	LineBresenham(x1, y2, x2, y2, color);
	LineBresenham(x1, y1, x1, y2, color);
	LineBresenham(x2, y1, x2, y2, color);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: SquareBresenham.
* INPUT: int x1, int y1, int x2, int y2, int color.
* OUTPUT: void.
* DESCRIPTION: Drawing a square based on its top left point position and a point
that may not be on the square but its coordination determines the square size.
This use LineBresenham procedure.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void SquareBresenham(int x1, int y1, int x2, int y2, int color) {
	//Here as we can see, (x1 ; y1) is the top left point while (x2 ; y2)
	//is responsible for square size.
	int dx = abs(x1 - x2), dy = abs(y1 - y2);
	if (dx < dy) {
		if (y2 > y1) {
			y2 = y1 + dx;
		}
		else {
			y2 = y1 - dx;
		}
	}
	else {
		if (x2 > x1) {
			x2 = x1 + dy;
		}
		else {
			x2 = x1 - dy;
		}
	}
	LineBresenham(x1, y1, x2, y1, color);
	LineBresenham(x1, y2, x2, y2, color);
	LineBresenham(x1, y1, x1, y2, color);
	LineBresenham(x2, y1, x2, y2, color);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: Fill.
* INPUT: int x, int y, int fillcolor.
* OUTPUT: void.
* DESCRIPTION: This procedure fill an area with fillcolor until it meets some
arbitrary bound that is determined by the background color difference between
the (x ; y) pixel and boundary pixel. I have thought of this algorithm myself
so I do not know what its name is: Someone said that it is Scanline, the other
said it is Boundary Fill, I am too busy to check what its name is also.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void Fill(int x, int y, int fillcolor, Scrollbar* scrollbar) {
	PixelSavior* wholeview = scrollbar->wholeview;
	int bgcolor = wholeview->get(x, y),
		startx = scrollbar->startx,
		starty = scrollbar->starty,
		endx = scrollbar->wholeview->getwidth() - 1,
		endy = scrollbar->wholeview->getheight() - 1;
	if (bgcolor != fillcolor) {
		//Here I use the seed point idea.
		queue<Seed> seed;
		Seed exam(x, y);
		seed.push(exam);
		int count = 0;
		while (seed.empty() == false) {
			exam = seed.front();
			seed.pop();
			//I fill color on the horizontal line that the seed point is on.
			x = exam.x;
			y = exam.y;
			putpixel(x, y, fillcolor);
			wholeview->set(x, y, fillcolor);

			int l = x - 1,
				r = Max(x + 1, exam.r);
			while (l + startx >= 0 && wholeview->get(l, y) == bgcolor) {
				putpixel(l, y, fillcolor);
				wholeview->set(l, y, fillcolor);
				l = l - 1;
			}
			while (r + startx <= endx && wholeview->get(r, y) == bgcolor) {
				putpixel(r, y, fillcolor);
				wholeview->set(r, y, fillcolor);
				r = r + 1;
			}
			exam.l = l;
			exam.r = r;
			//I check wheter there exists a point of the current line
			//that above it is a pixel that can be used as a seed point.
			for (int i = l + 1; i < r; i++) {
				if (y + starty > 0 && wholeview->get(i, y - 1) == bgcolor) {
					Seed child(i, y - 1);
					child.before(exam);
					seed.push(child);
					break;
				}
			}
			//I check wheter there exists a point of the current line
			//that below it is a pixel that can be used as a seed point.
			for (int i = l + 1; i < r; i++) {
				if (y + starty < endy && wholeview->get(i, y + 1) == bgcolor) {
					Seed child(i, y + 1);
					child.before(exam);
					seed.push(child);
					break;
				}
			}
			//If the current line right bound is smaller than its
			//parent's right bound then that means there may still
			//exist a seed point on its parent line so we will
			//push that parent line back to the seed point queue.
			if (exam.r < exam.br) {
				Seed temp(r, exam.by);
				temp.r = exam.br;
				seed.push(temp);
			}
		}
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: LineBresenhamSavior.
* INPUT: int x1, int y1, int x2, int y2, int color, Scrollbar* scrollbar.
* OUTPUT: void.
* DESCRIPTION: This procedure is an imitation of LineBresenham procedure with
additional feature: It will save the drawn line into a PixelSavior* wholeview
of a Scrollbar* scrollbar.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void LineBresenhamSavior(int x1, int y1, int x2, int y2, int color, Scrollbar* scrollbar) {
	int	dx = x2 - x1,
		dy = y2 - y1,
		minx = Min(x1, x2),
		miny = Min(y1, y2),
		maxx = Max(x1, x2),
		maxy = Max(y1, y2); //The cost of this Line is too low compared to the code below
	//(which has so many calls to putpixel procedure)
	//so we will not try to optimize it to keep it clear.
	PixelSavior* wholeview = scrollbar->wholeview;

	if (dx) {
		float m = (float)dy / dx;
		if (m == 0) { //parallel to x-axis.
			for (int x = minx; x < maxx; x++) {
				putpixel(x, miny, color);
				wholeview->set(x, miny, color);
			}
		}
		else if (m > 1) {
			dy = abs(dy);
			dx = abs(dx);
			int P = 2 * dx - dy, x = minx;
			for (int y = miny; y < maxy; y++) {
				putpixel(x, y, color);
				wholeview->set(x, y, color);
				if (P < 0) {
					P = P + 2 * dx;
				}
				else {
					P = P + 2 * (dx - dy);
					x = x + 1;
				}
			}
		}
		else if (m < -1) {
			dy = abs(dy);
			dx = -abs(dx);
			int P = -2 * dx - dy, x = maxx;
			for (int y = miny; y < maxy; y++) {
				putpixel(x, y, color);
				wholeview->set(x, y, color);
				if (P < 0) {
					P = P - 2 * dx;
				}
				else {
					P = P - 2 * (dx + dy);
					x = x - 1;
				}
			}
		}
		else if (m > 0) { //m > 0 && m < 1
			dy = abs(dy);
			dx = abs(dx);
			int P = 2 * dy - dx, y = miny;
			for (int x = minx; x < maxx; x++) {
				putpixel(x, y, color);
				wholeview->set(x, y, color);
				if (P < 0) {
					P = P + 2 * dy;
				}
				else {
					P = P + 2 * (dy - dx);
					y = y + 1;
				}
			}
		}
		else { //m < 0 && m > -1
			dy = -abs(dy);
			dx = abs(dx);
			int P = -2 * dy - dx, y = maxy;
			for (int x = minx; x < maxx; x++) {
				putpixel(x, y, color);
				wholeview->set(x, y, color);
				if (P < 0) {
					P = P - 2 * dy;
				}
				else {
					P = P - 2 * (dy + dx);
					y = y - 1;
				}
			}
		}
	}
	else { //parallel to y-axis.
		for (int y = miny; y < maxy; y++){
			putpixel(minx, y, color);
			wholeview->set(minx, y, color);
		}
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: SquareBresenhamSavior.
* INPUT: int x1, int y1, int x2, int y2, int color, Scrollbar* scrollbar.
* OUTPUT: void.
* DESCRIPTION: This procedure is an imitation of SquareBresenham procedure with
additional feature: It will save the drawn square into a PixelSavior* wholeview
of a Scrollbar* scrollbar.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void SquareBresenhamSavior(int x1, int y1, int x2, int y2, int color, Scrollbar* scrollbar) {
	int dx = abs(x1 - x2), dy = abs(y1 - y2);
	if (dx < dy) {
		if (y2 > y1) {
			y2 = y1 + dx;
		}
		else {
			y2 = y1 - dx;
		}
	}
	else {
		if (x2 > x1) {
			x2 = x1 + dy;
		}
		else {
			x2 = x1 - dy;
		}
	}
	LineBresenhamSavior(x1, y1, x2, y1, color, scrollbar);
	LineBresenhamSavior(x1, y2, x2, y2, color, scrollbar);
	LineBresenhamSavior(x1, y1, x1, y2, color, scrollbar);
	LineBresenhamSavior(x2, y1, x2, y2, color, scrollbar);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: SquareBresenhamSavior.
* INPUT: int x1, int y1, int a, int color, Scrollbar* scrollbar.
* OUTPUT: void.
* DESCRIPTION: This procedure is an imitation of SquareBresenham procedure with
additional feature: It will save the drawn square into a PixelSavior* wholeview
of a Scrollbar* scrollbar.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void SquareBresenhamSavior(int x1, int y1, int a, int color, Scrollbar* scrollbar) {
	int x2 = x1 + a,
		y2 = y1 + a;
	LineBresenhamSavior(x1, y1, x2, y1, color, scrollbar);
	LineBresenhamSavior(x1, y2, x2, y2, color, scrollbar);
	LineBresenhamSavior(x1, y1, x1, y2, color, scrollbar);
	LineBresenhamSavior(x2, y1, x2, y2, color, scrollbar);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: Put8Savior.
* INPUT: int a, int b, int x, int y, int color, Scrollbar* scrollbar.
* OUTPUT: void.
* DESCRIPTION: This procedure is an imitation of Put8 procedure with
additional feature: It will save the drawn points into a PixelSavior* wholeview
of a Scrollbar* scrollbar.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void Put8Savior(int a, int b, int x, int y, int color, Scrollbar* scrollbar) {
	PixelSavior* wholeview = scrollbar->wholeview;

	putpixel(x + a, y + b, color);
	putpixel(x + a, -y + b, color);
	putpixel(y + a, x + b, color);
	putpixel(y + a, -x + b, color);
	putpixel(-x + a, y + b, color);
	putpixel(-x + a, -y + b, color);
	putpixel(-y + a, x + b, color);
	putpixel(-y + a, -x + b, color);

	wholeview->set(x + a, y + b, color);
	wholeview->set(x + a, -y + b, color);
	wholeview->set(y + a, x + b, color);
	wholeview->set(y + a, -x + b, color);
	wholeview->set(-x + a, y + b, color);
	wholeview->set(-x + a, -y + b, color);
	wholeview->set(-y + a, x + b, color);
	wholeview->set(-y + a, -x + b, color);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: CircleMidpointSavior.
* INPUT: int a, int b, int R, int color, Scrollbar* scrollbar.
* OUTPUT: void.
* DESCRIPTION: This procedure is an imitation of CircleMidpoint procedure with
additional feature: It will save the drawn square into a PixelSavior* wholeview
of a Scrollbar* scrollbar.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CircleMidpointSavior(int a, int b, int R, int color, Scrollbar* scrollbar) {
	if (R > 0) {
		int x = 0, y = R, f = 1 - R;
		while (y >= x) {
			Put8Savior(a, b, x, y, color, scrollbar);
			if (f < 0) {
				f = f + 2 * x + 1;
			}
			else {
				y = y - 1;
				f = f + 2 * (x - y) + 1;
			}
			x = x + 1;
		}
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: CircleMidpointSavior.
* INPUT: int x1, int y1, int x2, int y2, int color, Scrollbar* scrollbar.
* OUTPUT: void.
* DESCRIPTION: This procedure is an imitation of CircleMidpoint procedure with
additional feature: It will save the drawn square into a PixelSavior* wholeview
of a Scrollbar* scrollbar.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CircleMidpointSavior(int x1, int y1, int x2, int y2, int color, Scrollbar* scrollbar) {
	int a = (x1 + x2) / 2,
		b = (y1 + y2) / 2,
		R = (int)round(distance(x1, y1, a, b));
	CircleMidpointSavior(a, b, R, color, scrollbar);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: ArcMidpointSavior.
* INPUT: int a, int b, int stangle, int endangle, int R, int color, Scrollbar* scrollbar.
* OUTPUT: void.
* DESCRIPTION: Savior version.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void ArcMidpointSavior(int a, int b, int stangle, int endangle, int R, int color, Scrollbar* scrollbar) {
	if (R > 0) {
		int x = 0, y = R, f = 1 - R;
		if (stangle < endangle) {
			while (y >= x) {
				ArcPut8rightSavior(x, y, a, b, stangle, endangle, R, color, scrollbar);
				if (f < 0) {
					f = f + 2 * x + 1;
				}
				else {
					y = y - 1;
					f = f + 2 * (x - y) + 1;
				}
				x = x + 1;
			}
		}
		else {
			if (stangle > 180) {
				stangle = 540 - stangle;
			}
			else {
				stangle = 180 - stangle;
			}
			swap(stangle, endangle);
			while (y >= x) {
				ArcPut8leftSavior(x, y, a, b, stangle, endangle, R, color, scrollbar);
				if (f < 0) {
					f = f + 2 * x + 1;
				}
				else {
					y = y - 1;
					f = f + 2 * (x - y) + 1;
				}
				x = x + 1;
			}
		}
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: ArcPut8rightSavior.
* INPUT: int x, int y, int a, int b, int stangle, int endangle, int R, int color, Scrollbar* scrollbar.
* OUTPUT: void.
* DESCRIPTION: Savior version.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void ArcPut8rightSavior(int x, int y, int a, int b, int stangle, int endangle, int R, int color, Scrollbar* scrollbar) {
	PixelSavior* wholeview = scrollbar->wholeview;
	int angle = (int)(toDegree((float)atan2(y, x)));

	//0 to 45
	if (90 - angle >= stangle && 90 - angle <= endangle) {
		putpixel(y + a, -x + b, color);
		wholeview->set(y + a, -x + b, color);
	}

	//45 to 90
	if (angle >= stangle && angle <= endangle) {
		putpixel(x + a, -y + b, color);
		wholeview->set(x + a, -y + b, color);
	}

	//90 to 135
	if (180 - angle >= stangle && 180 - angle <= endangle) {
		putpixel(-x + a, -y + b, color);
		wholeview->set(-x + a, -y + b, color);
	}

	//135 to 180
	if (angle + 90 >= stangle && angle + 90 <= endangle) {
		putpixel(-y + a, -x + b, color);
		wholeview->set(-y + a, -x + b, color);
	}

	//180 to 225
	if (270 - angle >= stangle && 270 - angle <= endangle) {
		putpixel(-y + a, x + b, color);
		wholeview->set(-y + a, x + b, color);
	}

	//225 to 270
	if (angle + 180 >= stangle && angle + 180 <= endangle) {
		putpixel(-x + a, y + b, color);
		wholeview->set(-x + a, y + b, color);
	}

	//270 to 315
	if (360 - angle >= stangle && 360 - angle <= endangle) {
		putpixel(x + a, y + b, color);
		wholeview->set(x + a, y + b, color);
	}

	//315 to 360
	if (angle + 270 >= stangle && angle + 270 <= endangle) {
		putpixel(y + a, x + b, color);
		wholeview->set(y + a, x + b, color);
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: ArcPut8left.
* INPUT: int x, int y, int a, int b, int stangle, int endangle, int R, int color, Scrollbar* scrollbar.
* OUTPUT: void.
* DESCRIPTION: Savior version.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void ArcPut8leftSavior(int x, int y, int a, int b, int stangle, int endangle, int R, int color, Scrollbar* scrollbar) {
	PixelSavior* wholeview = scrollbar->wholeview;
	int angle = (int)(toDegree((float)atan2(y, x)));

	//0 to 45
	if (90 - angle >= stangle && 90 - angle <= endangle) {
		putpixel(a - y, b - x, color);
		wholeview->set(a - y, b - x, color);
	}

	//45 to 90
	if (angle >= stangle && angle <= endangle) {
		putpixel(a - x, b - y, color);
		wholeview->set(a - x, b - y, color);
	}

	//90 to 135
	if (180 - angle >= stangle && 180 - angle <= endangle) {
		putpixel(a + x, b - y, color);
		wholeview->set(a + x, b - y, color);
	}

	//135 to 180
	if (angle + 90 >= stangle && angle + 90 <= endangle) {
		putpixel(a + y, b - x, color);
		wholeview->set(a + y, b - x, color);
	}

	//180 to 225
	if (270 - angle >= stangle && 270 - angle <= endangle) {
		putpixel(a + y, b + x, color);
		wholeview->set(a + y, b + x, color);
	}

	//225 to 270
	if (angle + 180 >= stangle && angle + 180 <= endangle) {
		putpixel(a + x, b + y, color);
		wholeview->set(a + x, b + y, color);
	}

	//270 to 315
	if (360 - angle >= stangle && 360 - angle <= endangle) {
		putpixel(a - x, b + y, color);
		wholeview->set(a - x, b + y, color);
	}

	//315 to 360
	if (angle + 270 >= stangle && angle + 270 <= endangle) {
		putpixel(a - y, b + x, color);
		wholeview->set(a - y, b + x, color);
	}
}

void EllipseMidpoint(int h, int k, int a, int b, int color) {
	int a2 = a * a, b2 = b * b,
		x = 0, y = b,
		xb2 = x * b2, ya2 = y * a2,
		f = a2 / 4 - a2 * b + b2;
	while (xb2 <= ya2) {
		EllipsePut4(x, y, h, k, color);
		if (f < 0) {
			f = f + b2 * (2 * x + 3);
		}
		else {
			f = f + b2 * (2 * x + 3) + a2 * (2 - 2 * y);
			y = y - 1;
			ya2 = ya2 - a2;
		}
		x = x + 1;
		xb2 = xb2 + b2;
	}
	f = (b2) / 4 - 2 * a2 * b + a2;
	while (y >= 0) {
		EllipsePut4(x, y, h, k, color);
		if (f > 0) {
			f = f + a2 * (3 - 2 * y);
		}
		else {
			f = f + a2 * (3 - 2 * y) + b2 * (2 * x + 2);
			x = x + 1;
		}
		y = y - 1;
	}
}

void EllipsePut4(int x, int y, int h, int k, int color) {
	putpixel(x + h, y + k, color);
	putpixel(-x + h, y + k, color);
	putpixel(x + h, -y + k, color);
	putpixel(-x + h, -y + k, color);
}

void EllipseMidpointSavior(int h, int k, int a, int b, int color, Scrollbar* scrollbar) {
	int a2 = a * a, b2 = b * b,
		x = 0, y = b,
		xb2 = x * b2, ya2 = y * a2,
		f = a2 / 4 - a2 * b + b2;
	while (xb2 <= ya2) {
		EllipsePut4Savior(x, y, h, k, color, scrollbar);
		if (f < 0) {
			f = f + b2 * (2 * x + 3);
		}
		else {
			f = f + b2 * (2 * x + 3) + a2 * (2 - 2 * y);
			y = y - 1;
			ya2 = ya2 - a2;
		}
		x = x + 1;
		xb2 = xb2 + b2;
	}
	f = (b2) / 4 - 2 * a2 * b + a2;
	while (y >= 0) {
		EllipsePut4Savior(x, y, h, k, color, scrollbar);
		if (f > 0) {
			f = f + a2 * (3 - 2 * y);
		}
		else {
			f = f + a2 * (3 - 2 * y) + b2 * (2 * x + 2);
			x = x + 1;
		}
		y = y - 1;
	}
}

void EllipsePut4Savior(int x, int y, int h, int k, int color, Scrollbar* scrollbar) {
	PixelSavior* wholeview = scrollbar->wholeview;

	putpixel(x + h, y + k, color);
	wholeview->set(x + h, y + k, color);
	putpixel(-x + h, y + k, color);
	wholeview->set(-x + h, y + k, color);
	putpixel(x + h, -y + k, color);
	wholeview->set(x + h, -y + k, color);
	putpixel(-x + h, -y + k, color);
	wholeview->set(-x + h, -y + k, color);
}

void Parabol(float a, int h, int k, int x, int color) {
	x = x - h;
	int y = (int)(x * x * a);
	float limit = 1 / (2 * a);
	if (x > 0) {
		x = -x;
	}
	if (a > 0) {
		limit = -limit;
		float f = a * x * (x + 1) + a / 4 - y + 1;
		while (x <= limit) {
			ParabolPut2(x, y, h, k, color);
			if (f > 0) {
				f = f + a * (2 * x + 2) + 1;
				x = x + 1;
			}
			else {
				f = f + 1;
			}
			y = y - 1;
		}
		f = a * (x + 1) * (x + 1) - y + 1;
		while (x <= 0) {
			ParabolPut2(x, y, h, k, color);
			if (f < 0) {
				f = f + a * (2 * x + 1) + 1;
				y = y - 1;
			}
			else {
				f = f + a * (2 * x + 1);
			}
			x = x + 1;
		}
	}
	else {
		float f = a * x * (x + 1) + a / 4 - y - 1;
		while (x <= limit) {
			ParabolPut2(x, y, h, k, color);
			if (f < 0) {
				f = f + a * (2 * x + 2) - 1;
				x = x + 1;
			}
			else {
				f = f - 1;
			}
			y = y + 1;
		}
		f = a * (x + 1) * (x + 1) - y;
		while (x <= 0) {
			ParabolPut2(x, y, h, k, color);
			if (f > 0) {
				f = f + a * (2 * x + 1) - 1;
				y = y + 1;
			}
			else {
				f = f + a * (2 * x + 1);
			}
			x = x + 1;
		}
	}
}

void ParabolPut2(int x, int y, int h, int k, int color) {
	putpixel(x + h, y + k, color);
	putpixel(-x + h, y + k, color);
}

void ParabolSavior(float a, int h, int k, int x, int color, Scrollbar* scrollbar) {
	x = x - h;
	int y = (int)(x * x * a);
	float limit = 1 / (2 * a);
	if (x > 0) {
		x = -x;
	}
	if (a > 0) {
		limit = -limit;
		float f = a * x * (x + 1) + a / 4 - y + 1;
		while (x <= limit) {
			ParabolPut2Savior(x, y, h, k, color, scrollbar);
			if (f > 0) {
				f = f + a * (2 * x + 2) + 1;
				x = x + 1;
			}
			else {
				f = f + 1;
			}
			y = y - 1;
		}
		f = a * (x + 1) * (x + 1) - y + 1;
		while (x <= 0) {
			ParabolPut2Savior(x, y, h, k, color, scrollbar);
			if (f < 0) {
				f = f + a * (2 * x + 1) + 1;
				y = y - 1;
			}
			else {
				f = f + a * (2 * x + 1);
			}
			x = x + 1;
		}
	}
	else {
		float f = a * x * (x + 1) + a / 4 - y - 1;
		while (x <= limit) {
			ParabolPut2Savior(x, y, h, k, color, scrollbar);
			if (f < 0) {
				f = f + a * (2 * x + 2) - 1;
				x = x + 1;
			}
			else {
				f = f - 1;
			}
			y = y + 1;
		}
		f = a * (x + 1) * (x + 1) - y;
		while (x <= 0) {
			ParabolPut2Savior(x, y, h, k, color, scrollbar);
			if (f > 0) {
				f = f + a * (2 * x + 1) - 1;
				y = y + 1;
			}
			else {
				f = f + a * (2 * x + 1);
			}
			x = x + 1;
		}
	}
}

void ParabolPut2Savior(int x, int y, int h, int k, int color, Scrollbar* scrollbar) {
	PixelSavior* wholeview = scrollbar->wholeview;

	putpixel(x + h, y + k, color);
	wholeview->set(x + h, y + k, color);
	putpixel(-x + h, y + k, color);
	wholeview->set(-x + h, y + k, color);
}

void Bezier(vector<Point> control, int color) {
	vector<Point> lines;
	for (double t = 0; t < 1; t = t + 0.05) {
		BezierPut(t, control, lines, color);
	}
	int n = lines.size() - 1;
	for (int i = 0; i < n; i++) {
		LineBresenham(lines.at(i).x, lines.at(i).y, lines.at(i + 1).x, lines.at(i + 1).y, color);
	}
}

void BezierPut(double t, vector<Point> control, vector<Point>& lines, int color) {
	int n = control.size();
	if (n == 1) {
		putpixel(control.at(0).x, control.at(0).y, color);
		lines.push_back(control.at(0));
	}
	else {
		vector<Point> temp;
		n = n - 1;
		for (int i = 0; i < n; i++) {
			Point ptemp;
			ptemp.x = (int)((1 - t) * control.at(i).x + t * control.at(i + 1).x);
			ptemp.y = (int)((1 - t) * control.at(i).y + t * control.at(i + 1).y);
			temp.push_back(ptemp);
		}
		BezierPut(t, temp, lines, color);
	}
}

void BezierSavior(vector<Point> control, int color, Scrollbar* scrollbar) {
	vector<Point> lines;
	for (double t = 0; t < 1; t = t + 0.05) {
		BezierPutSavior(t, control, lines, color, scrollbar);
	}
	int n = lines.size() - 1;
	for (int i = 0; i < n; i++) {
		LineBresenhamSavior(lines.at(i).x, lines.at(i).y, lines.at(i + 1).x, lines.at(i + 1).y, color, scrollbar);
	}
}

void BezierPutSavior(double t, vector<Point> control, vector<Point>& lines, int color, Scrollbar* scrollbar) {
	int n = control.size();
	if (n == 1) {
		PixelSavior* wholeview = scrollbar->wholeview;
		putpixel(control.at(0).x, control.at(0).y, color);
		wholeview->set(control.at(0).x, control.at(0).y, color);
		lines.push_back(control.at(0));
	}
	else {
		vector<Point> temp;
		n = n - 1;
		for (int i = 0; i < n; i++) {
			Point ptemp;
			ptemp.x = (int)((1 - t) * control.at(i).x + t * control.at(i + 1).x);
			ptemp.y = (int)((1 - t) * control.at(i).y + t * control.at(i + 1).y);
			temp.push_back(ptemp);
		}
		BezierPutSavior(t, temp, lines, color, scrollbar);
	}
}
