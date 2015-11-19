#pragma once
#include "Point.h"
#include <stdio.h>
#include <limits>
#include <vector>
using std::vector;
#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

int minx(vector<Point> list);
int maxx(vector<Point> list);
int miny(vector<Point> list);
int maxy(vector<Point> list);

double distance(int x1, int y1, int x2, int y2);
float** initzero(int m, int n);

float** multiply(float** A, float** B, int m, int n, int k);
void delarray(float**& arr, int m, int n);

/*Conversion*/
float toDegree(float Radian);
float toRadian(float Degree);

/* General function */
template<class T>
T Min(T a, T b) { //Return a if a < b, return b if otherwise.
	if (a < b) {
		return a;
	}
	return b;
}

template<class T>
T Max(T a, T b) { //Return b if a < b, return a if otherwise.
	if (a < b) {
		return b;
	}
	return a;
}

template<class T>
void swap(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}

int input(char* Request, int min = std::numeric_limits<int>::min(), int max = std::numeric_limits<int>::max());