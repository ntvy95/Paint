#include "Affine.h"
#include "Procedure.h"
#include "Global.h"

Affine::Affine() {
	matrix = NULL;
	initAffine();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*NAME: Affine::initAffine.
*INPUT: none.
*OUTPUT: void.
*DESCRIPTION: This procedure is part of Affine constructor. Though, sometimes
we want to init an Affine with no reference to its constructor.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void Affine::initAffine() {
	matrix = initmatrix();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*NAME: Affine::initmatrix.
*INPUT: none.
*OUTPUT: void.
*DESCRIPTION: This procedure initialize a standard Affine identity matrix.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
float** Affine::initmatrix() {
	float** m = initzero(n, n);
	for (int i = 0; i < n; i++) {
		m[i][i] = 1;
	}
	return m;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*NAME: Affine::delAffine.
*INPUT: none.
*OUTPUT: void.
*DESCRIPTION: This procedure is part of Affine destructor. Though, sometimes
we want to delete an Affine with no reference to its destructor.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void Affine::delAffine() {
	delarray(matrix, n, n);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*NAME: Affine::transform.
*INPUT: Point p.
*OUTPUT: Point.
*DESCRIPTION: Use Affine matrix to transform point p.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
Point Affine::transform(Point p) {
	Point np;
	np.x = p.x * matrix[0][0] + p.y * matrix[1][0] + matrix[2][0];
	np.y = p.x * matrix[0][1] + p.y * matrix[1][1] + matrix[2][1];
	return np;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*NAME: Affine::translation.
*INPUT: Point from, Point to.
*OUTPUT: void.
*DESCRIPTION: Build and combine the Affine matrix for translation from Point
from to Poin to with the current Affine matrix.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void Affine::translation(Point from, Point to) {
	float** tm = initmatrix();
	tm[2][0] = to.x - from.x;
	tm[2][1] = to.y - from.y;
	join(tm);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*NAME: Affine::resize.
*INPUT: Point base, float xsize, float ysize.
*OUTPUT: void.
*DESCRIPTION: Build and combine the Affine matrix for resizing the Graph
on the base Point base with two parameters: 0 < xsize, ysize < 1.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void Affine::resize(Point base, float xsize, float ysize) {
	float** rm = initmatrix();
	rm[0][0] = rm[0][0] * xsize;
	rm[1][1] = rm[1][1] * ysize;
	rm[2][0] = (1 - xsize) * base.x;
	rm[2][1] = (1 - ysize) * base.y;
	join(rm);
}

void Affine::rotate(Point base, int degree) {
	float rdeg = toRadian(degree % 360),
		**rm = initmatrix(),
		c = cos(rdeg), s = sin(rdeg);
	rm[0][0] = c;
	rm[1][0] = s;
	rm[2][0] = -base.x * c - base.y * s + base.x;
	rm[0][1] = - s;
	rm[1][1] = c;
	rm[2][1] = base.x * s - base.y * c + base.y;
	join(rm);
}

void Affine::shear(Point base, float g, float h) {
	float **dm = initmatrix();
	dm[0][0] = 1;
	dm[1][0] = g;
	dm[2][0] = - g * base.y;
	dm[0][1] = h;
	dm[1][1] = 1;
	dm[2][1] = - h * base.x;
	join(dm);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*NAME: Affine::join.
*INPUT: float** jm.
*OUTPUT: void.
*DESCRIPTION: We combine the Affine matrix jm with the current Affine matrix.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void Affine::join(float** jm) {
	float** temp = multiply(matrix, jm, n, n, n);
	delarray(matrix, n, n);
	delarray(jm, n, n);
	matrix = temp;
}

Affine::~Affine() {
	delAffine();
}