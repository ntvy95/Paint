#pragma once

typedef struct Seed {
	int x;
	int y;
	int l;
	int r;
	int bx;
	int by;
	int bl;
	int br;
	/*PROCEDURE*/
	Seed(int X, int Y);
	void before(const Seed& s);
} Seed;