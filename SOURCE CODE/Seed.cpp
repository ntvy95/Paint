#include "Seed.h"

Seed::Seed(int X, int Y) {
	x = X;
	y = Y;
	l = 0;
	r = 0;
	bx = 0;
	by = 0;
	bl = 0;
	br = 0;
}

void Seed::before(const Seed& s) {
	bx = s.x;
	by = s.y;
	bl = s.l;
	br = s.r;
}