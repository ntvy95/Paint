#include "Pixelsavior.h"
#include "Procedure.h"
#include "graphics.h"
#pragma comment(lib, "graphics.lib")

PixelSavior::PixelSavior(Scrollbar* s) {
	scrollbar = s;
	Item* item = s->parent;
	setviewport(item->layer->startx, item->layer->starty, item->layer->endx, item->layer->endy, 0);
	savior.reserve(item->parent->itemw);
	for (int i = 0; i < savior.capacity(); i++) {
		vector<unsigned char> row;
		savior.push_back(row);
		savior.at(i).reserve(item->parent->itemh);
		for (int j = 0; j < savior.at(i).capacity(); j++) {
			//The WHITE color in general is just an assumption.
			savior.at(i).push_back(WHITE);
		}
	}
	setviewport(0, 0, MAXX, MAXY, 1);
}

void PixelSavior::set_savior() {
	/*for (int i = 0; i < getwidth(); i++) {
		for (int j = 0; j < getheight(); i++) {
			(*(savior.begin() + i)).assign(j, getpixel(i, j));
		}
	}*/
	//I have commented out the above code lines so that the program take less time to start up.
	//I do not use scrollbar for anything else exception Drawing Area anyway.
}

void PixelSavior::extend_col() {
	for (int n = 0; n < (int)(MAXX * 0.1); n++) {
		vector<unsigned char> row;
		savior.push_back(row);
		savior.back().reserve(scrollbar->parent->parent->itemh);
		for (int j = 0; j < savior.at(0).capacity(); j++) {
			savior.back().push_back(WHITE);
		}
	}
}
void PixelSavior::extend_row() {
	for (int i = 0; i < savior.size(); i++) {
		for (int n = 0; n < (int)(MAXX * 0.1); n++) {
			savior.at(i).push_back(WHITE);
		}
	}
}

int PixelSavior::getwidth() {
	return savior.size();
}

int PixelSavior::getheight() {
	return savior.at(0).size();
}

void PixelSavior::set(int i, int j, int c) {
	i = scrollbar->startx + i;
	j = scrollbar->starty + j;
	if (i >= 0 && j >= 0) {
		while (i >= getwidth()) {
			extend_col();
		}
		while (j >= getheight()) {
			extend_row();
		}
		(*(savior.begin() + i))[j] = c;
	}
}
int PixelSavior::get(int i, int j) {
	i = scrollbar->startx + i;
	j = scrollbar->starty + j;
	if (i < getwidth() && j < getheight()) {
		return savior.at(i).at(j);
	}
	return 0;
}

PixelSavior::~PixelSavior() {
	savior.clear();
}