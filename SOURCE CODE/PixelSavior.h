#pragma once
#include <vector>
#include "Scrollbar.h"

using std::vector;
struct Scrollbar;

typedef struct PixelSavior { //We should give our hero a name, lolz.
	/*ARTRIBUTE*/
	Scrollbar* scrollbar;
	vector<vector<unsigned char>> savior;
	/*METHOD*/
	PixelSavior(Scrollbar* s);
	int getwidth();
	int getheight();
	void set_savior();
	void extend_col();
	void extend_row();
	void set(int i, int j, int c);
	int get(int i, int j);
	~PixelSavior();
} PixelSavior;