#pragma once

typedef struct Point {
	int x;
	int y;
	/*PROCEDURE*/
	Point();
	Point(const Point& A);
	Point(int X, int Y);
	void set(int X, int Y);
} Point;