#include "Point.h"

Point::Point() {
	x = 0;
	y = 0;
}

Point::Point(const Point& A) {
	x = A.x;
	y = A.y;
}

Point::Point(int X, int Y) {
	set(X, Y);
}

void Point::set(int X, int Y) {
	x = X;
	y = Y;
}