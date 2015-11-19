/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*COLLECTION: Affine.
*DESCRIPTION: The struct name says everything. This Affine is used mainly
in Graph struct even though it is not a member of it.
Because the Affine matrix is in floating-point data type so it may distort
the Graph if you keep transform it. For more information, please check the
comment in void Event::drag_draw_graph() procedure [File: Event.cpp].
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma once
#include "Point.h"

typedef struct Affine {
	static int const n = 3;
	float** matrix;
	/*PROCEDURE*/
	Affine();
	Point transform(Point p);
	void translation(Point from, Point to);
	void resize(Point base, float xsize, float ysize);
	void rotate(Point base, int degree);
	void shear(Point base, float g, float h);
	void join(float** jm);
	void initAffine();
	void delAffine();
	~Affine();
	static float** initmatrix();
} Affine;