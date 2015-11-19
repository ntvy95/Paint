#pragma once
#include "Point.h"

struct Scrollbar;
typedef struct Relation {
	Point p1;
	Point p2;
	int color;
	void(Relation::*relate)();
	void(Relation::*relate_savior)(Scrollbar* scrollbar);
	/*PROCEDURE*/
	Relation();
	void set(Point P1, Point P2);
	void set(Point P1, Point P2, void(Relation::*r)());
	void set(Point P1, Point P2, void(Relation::*r)(), void(Relation::*rs)(Scrollbar* scrollbar), int c);
	//relate function options.
	void line();
	void arc270to90();
	void arc45to315();
	void circle135and315();
	//relate_savior function options.
	void line_savior(Scrollbar* scrollbar);
	void arc270to90_savior(Scrollbar* scrollbar);
	void arc45to315_savior(Scrollbar* scrollbar);
	void circle135and315_savior(Scrollbar* scrollbar);
} Relation;