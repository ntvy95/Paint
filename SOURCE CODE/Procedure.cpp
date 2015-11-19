#define _USE_MATH_DEFINES
#include <math.h>
#include "Procedure.h"
#include "graphics.h"
#pragma comment(lib, "graphics.lib")

int input(char* Request, int min, int max) {
	printf("%s\n", Request);
	int n = 0;
	do {
		fflush(stdin);
		scanf_s("%d", &n);
		if (n < min || n > max) {
			printf("So ban nhap khong hop le! Xin vui long nhap lai: ");
		}
	} while (n < min || n > max);
	return n;
}

float toDegree(float Radian) {
	return Radian * 180 / (float)M_PI;
}

float toRadian(float Degree) {
	return Degree * (float)M_PI / 180;
}

float** initzero(int m, int n) {
	float** matrix = new float*[n];
	for (int i = 0; i < n; i++) {
		matrix[i] = new float[n];
		for (int j = 0; j < n; j++) {
			matrix[i][j] = 0;
		}
	}
	return matrix;
}

void delarray(float**& arr, int m, int n) {
	if (arr != NULL) {
		for (int i = 0; i < n; i++) {
			delete[] arr[i];
		}
		delete[] arr;
		arr = NULL;
	}
}

double distance(int x1, int y1, int x2, int y2) {
	return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}

float** multiply(float** A, float** B, int m, int n, int k) {
	float** C = new float*[m];
	for (int i = 0; i < m; i++) {
		C[i] = new float[k];
		for (int j = 0; j < k; j++) {
			C[i][j] = 0;
			for (int x = 0; x < n; x++) {
				C[i][j] = C[i][j] + A[i][x] * B[x][j];
			}
		}
	}
	return C;
}

int minx(vector<Point> list) {
	int min = getmaxwidth();
	for (int i = 0; i < list.size(); i++) {
		if (min > list.at(i).x) {
			min = list.at(i).x;
		}
	}
	return min;
}

int maxx(vector<Point> list) {
	int max = 0;
	for (int i = 0; i < list.size(); i++) {
		if (max < list.at(i).x) {
			max = list.at(i).x;
		}
	}
	return max;
}

int miny(vector<Point> list) {
	int min = getmaxheight();
	for (int i = 0; i < list.size(); i++) {
		if (min > list.at(i).y) {
			min = list.at(i).y;
		}
	}
	return min;
}

int maxy(vector<Point> list) {
	int max = 0;
	for (int i = 0; i < list.size(); i++) {
		if (max < list.at(i).y) {
			max = list.at(i).y;
		}
	}
	return max;
}