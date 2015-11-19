#include "Relation.h"
#include "DrawingAlgorithm.h"
#include "Procedure.h"
#define NULL 0

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: Relation::set.
* INPUT: none.
* OUTPUT: none.
* DESCRIPTION: The constructor code is clear enough that it does not need any
explanation.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
Relation::Relation() {
	relate = NULL;
	relate_savior = NULL;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: Relation::set.
* INPUT: none.
* OUTPUT: void.
* DESCRIPTION: The procedure code is clear enough that it does not need any
explanation.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void Relation::set(Point P1, Point P2) {
	p1 = P1;
	p2 = P2;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: Relation::set.
* INPUT: none.
* OUTPUT: void.
* DESCRIPTION: The procedure code is clear enough that it does not need any
explanation.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void Relation::set(Point P1, Point P2, void(Relation::*r)()) {
	set(P1, P2);
	relate = r;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: Relation::set.
* INPUT: none.
* OUTPUT: void.
* DESCRIPTION: The procedure code is clear enough that it does not need any
explanation.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void Relation::set(Point P1, Point P2, void(Relation::*r)(), void(Relation::*rs)(Scrollbar* scrollbar), int c) {
	set(P1, P2, r);
	relate_savior = rs;
	color = c;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: Relation::line.
* INPUT: none.
* OUTPUT: void.
* DESCRIPTION: We will draw a line from p1 to p2.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void Relation::line() {
	LineBresenham(p1.x, p1.y, p2.x, p2.y, color);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: Relation::arc270to90.
* INPUT: none.
* OUTPUT: void.
* DESCRIPTION: We will draw an arc from p1 to p2, with p1 at the 270 degree of
the counter-clockwise circle, p2 at the 90 degree of the counter-clockwise
circle.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void Relation::arc270to90() {
	int a = p1.x, b = (p1.y + p2.y) / 2, R = p1.y - b;
	ArcMidpoint(a, b, 270, 90, R, color);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: Relation::arc45to315.
* INPUT: none.
* OUTPUT: void.
* DESCRIPTION: We will draw an arc from p1 to p2, with p1 at the 45 degree of
the counter-clockwise circle, p2 at the 315 degree of the counter-clockwise
circle.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void Relation::arc45to315() {
	if (p1.y > p2.y) {
		swap(p1, p2);
	}
	//Solve the equation:
	//a + b = p1.x + p1.y
	//a - b = p2.x - p2.y
	int n = 2;
	float** inverseA = initzero(n, n);
	inverseA[0][0] = (float)1 / 2;
	inverseA[0][1] = (float)1 / 2;
	inverseA[1][0] = (float)1 / 2;
	inverseA[1][1] = (float)-1 / 2;
	float** B = initzero(n, n);
	B[0][0] = (float)(p1.x + p1.y);
	B[1][0] = (float)(p2.x - p2.y);
	float** result = ::multiply(inverseA, B, n, n, n);
	int a = (int)(result[0][0]),
		b = (int)(result[1][0]);
	delarray(inverseA, n, n);
	delarray(B, n, n);
	delarray(result, n, n);
	//Draw the arc.
	ArcMidpoint(a, b, 45, 315, (int)(distance(a, b, p1.x, p1.y)), color);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: Relation::line_savior.
* INPUT: Scrollbar* scrollbar.
* OUTPUT: void.
* DESCRIPTION: Savior version of Relation::line.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void Relation::line_savior(Scrollbar* scrollbar) {
	LineBresenhamSavior(p1.x, p1.y, p2.x, p2.y, color, scrollbar);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: Relation::arc270to90_savior.
* INPUT: Scrollbar* scrollbar.
* OUTPUT: void.
* DESCRIPTION: Savior version of Relation::arc270to90.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void Relation::arc270to90_savior(Scrollbar* scrollbar) {
	int a = p1.x, b = (p1.y + p2.y) / 2, R = p1.y - b;
	ArcMidpointSavior(a, b, 270, 90, R, color, scrollbar);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: Relation::arc45to315_savior.
* INPUT: none.
* OUTPUT: void.
* DESCRIPTION: Savior version of Relation::arc45to315.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void Relation::arc45to315_savior(Scrollbar* scrollbar) {
	if (p1.y > p2.y) {
		swap(p1, p2);
	}
	//Solve the equation:
	//a + b = p1.x + p1.y
	//a - b = p2.x - p2.y
	int n = 2;
	float** inverseA = initzero(n, n);
	inverseA[0][0] = (float)1 / 2;
	inverseA[0][1] = (float)1 / 2;
	inverseA[1][0] = (float)1 / 2;
	inverseA[1][1] = (float)-1 / 2;
	float** B = initzero(n, n);
	B[0][0] = (float)(p1.x + p1.y);
	B[1][0] = (float)(p2.x - p2.y);
	float** result = ::multiply(inverseA, B, n, n, n);
	int a = (int)(result[0][0]),
		b = (int)(result[1][0]);
	delarray(inverseA, n, n);
	delarray(B, n, n);
	delarray(result, n, n);
	//Draw the arc.
	ArcMidpointSavior(a, b, 45, 315, (int)(distance(a, b, p1.x, p1.y)), color, scrollbar);
}

void Relation::circle135and315() {
	int a = (p1.x + p2.x) / 2,
		b = (p1.y + p2.y) / 2,
		R = (int)round(distance(p1.x, p1.y, a, b));
	CircleMidpoint(a, b, R, color);
}

void Relation::circle135and315_savior(Scrollbar* scrollbar) {
	int a = (p1.x + p2.x) / 2,
		b = (p1.y + p2.y) / 2,
		R = (int)round(distance(p1.x, p1.y, a, b));
	CircleMidpointSavior(a, b, R, color, scrollbar);
}