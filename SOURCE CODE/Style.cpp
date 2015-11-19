#include "Style.h"
#include "Event.h"
#include "DrawingAlgorithm.h"
#include "graphics.h"
#pragma comment(lib, "graphics.lib")
char* Style::InputText = new char[nInputText];

Style::Style() {
	item = NULL;
	menu = NULL;
	scrollbar = NULL;
	text = NULL;
	parameters = NULL;
	npara = 0;
	normal = NULL;
	active = NULL;
	ntext = 0;
}

Style::Style(Item* i) {
	set(i, NULL, NULL, NULL, NULL, 0, NULL, NULL);
}

Style::Style(Menu* m) {
	set(NULL, m, NULL, NULL, NULL, 0, NULL, NULL);
}

Style::Style(Scrollbar* s) {
	set(NULL, NULL, s, NULL, NULL, 0, NULL, NULL);
}

void Style::set(Item* i, Menu* m, Scrollbar* s, char* t, int* p, int N, void(Style::*no)(), void(Style::*ac)()) {
	item = i;
	menu = m;
	scrollbar = s;
	text = t;
	parameters = p;
	npara = N;
	normal = no;
	active = ac;
	ntext = 0;
}

Style::~Style() {
	if (text) {
		//delete[] text;
		//We have commented out the above code line because text attribute will never be assigned by new operator.
		text = NULL;
		ntext = 0;
	}
	if (parameters) {
		delete[] parameters;
		parameters = NULL;
		npara = 0;
	}
}

void Style::graybg() {
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	if (item) {
		bar(item->layer->startx + 1, item->layer->starty + 1, item->layer->endx, item->layer->endy);
	}
	else if (menu) {
		bar(menu->layer->startx + 1, menu->layer->starty + 1, menu->layer->endx, menu->layer->endy);
	}
}

void Style::normal_outtext() {
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	setcolor(BLACK);
	setfillstyle(SOLID_FILL, WHITE);
	setbkcolor(WHITE);
	if (item) {
		rectangle(item->layer->startx, item->layer->starty, item->layer->endx, item->layer->endy);
		bar(item->layer->startx + 1, item->layer->starty + 1, item->layer->endx, item->layer->endy);
		outtextxy((item->layer->endx + item->layer->startx - textwidth(text)) / 2, (item->layer->endy + item->layer->starty - textheight(text)) / 2, text);
	}
}

void Style::active_outtext() {
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	setcolor(BLACK);
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	setbkcolor(LIGHTGRAY);
	rectangle(item->layer->startx, item->layer->starty, item->layer->endx, item->layer->endy);
	bar(item->layer->startx + 1, item->layer->starty + 1, item->layer->endx, item->layer->endy);
	outtextxy((item->layer->endx + item->layer->startx - textwidth(text)) / 2, (item->layer->endy + item->layer->starty - textheight(text)) / 2, text);
	setbkcolor(WHITE);
	setfillstyle(EMPTY_FILL, WHITE);
}

void Style::normal_bezier() {
	if (npara == 3) {
		setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
		setfillstyle(SOLID_FILL, WHITE);
		if (item) {
			bar(item->layer->startx + 1, item->layer->starty + 1, item->layer->endx, item->layer->endy);
		}
		int centerx, centery, a = parameters[2];
		if (item) {
			centerx = item->layer->startx + parameters[0];
			centery = item->layer->starty + parameters[1];
		}
		setcolor(BLACK);
		if (item) {
			rectangle(item->layer->startx, item->layer->starty, item->layer->endx, item->layer->endy);
		}
		vector<Point> control;
		control.push_back(Point(centerx, item->layer->starty));
		control.push_back(Point(item->layer->startx, centery - a / 2));
		control.push_back(Point(item->layer->endx, centery + a / 2));
		control.push_back(Point(centerx, item->layer->endy));
		Bezier(control, BLACK);
	}
}

void Style::active_bezier() {
	if (npara == 3) {
		graybg();
		int centerx, centery, a = parameters[2];
		if (item) {
			centerx = item->layer->startx + parameters[0];
			centery = item->layer->starty + parameters[1];
		}
		setcolor(BLACK);
		if (item) {
			rectangle(item->layer->startx, item->layer->starty, item->layer->endx, item->layer->endy);
		}
		vector<Point> control;
		control.push_back(Point(centerx, item->layer->starty));
		control.push_back(Point(item->layer->startx, centery - a / 2));
		control.push_back(Point(item->layer->endx, centery + a / 2));
		control.push_back(Point(centerx, item->layer->endy));
		Bezier(control, BLACK);
	}
}

void Style::normal_parabol() {
	if (npara == 3) {
		setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
		setfillstyle(SOLID_FILL, WHITE);
		if (item) {
			bar(item->layer->startx + 1, item->layer->starty + 1, item->layer->endx, item->layer->endy);
		}
		int centerx, centery, a = parameters[2];
		if (item) {
			centerx = item->layer->startx + parameters[0];
			centery = item->layer->starty + parameters[1];
		}
		setcolor(BLACK);
		if (item) {
			rectangle(item->layer->startx, item->layer->starty, item->layer->endx, item->layer->endy);
		}
		int x = centerx - a, y = centery - a,
			h = centerx, k = centery + a;
		float aprime = - 2 * a / float(a * a);
		Parabol(aprime, h, k, x, BLACK);
	}
}

void Style::active_parabol() {
	if (npara == 3) {
		graybg();
		int centerx, centery, a = parameters[2];
		if (item) {
			centerx = item->layer->startx + parameters[0];
			centery = item->layer->starty + parameters[1];
		}
		setcolor(BLACK);
		if (item) {
			rectangle(item->layer->startx, item->layer->starty, item->layer->endx, item->layer->endy);
		}
		int x = centerx - a, y = centery - a,
			h = centerx, k = centery + a;
		float aprime = -2 * a / float(a * a);
		Parabol(aprime, h, k, x, BLACK);
	}
}

void Style::normal_line() {
	if (npara == 3) {
		setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
		setfillstyle(SOLID_FILL, WHITE);
		if (item) {
			bar(item->layer->startx + 1, item->layer->starty + 1, item->layer->endx, item->layer->endy);
		}
		int centerx, centery, a = parameters[2];
		if (item) {
			centerx = item->layer->startx + parameters[0];
			centery = item->layer->starty + parameters[1];
		}
		setcolor(BLACK);
		if (item) {
			rectangle(item->layer->startx, item->layer->starty, item->layer->endx, item->layer->endy);
		}
		line(centerx - a, centery - a, centerx + a, centery + a);
	}
}
void Style::active_line() {
	if (npara == 3) {
		graybg();
		int centerx, centery, a = parameters[2];
		if (item) {
			centerx = item->layer->startx + parameters[0];
			centery = item->layer->starty + parameters[1];
		}
		setcolor(BLACK);
		if (item) {
			rectangle(item->layer->startx, item->layer->starty, item->layer->endx, item->layer->endy);
		}
		line(centerx - a, centery - a, centerx + a, centery + a);
	}
}

void Style::normal_circle() {
	if (npara == 3) {
		setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
		setfillstyle(SOLID_FILL, WHITE);
		if (item) {
			bar(item->layer->startx + 1, item->layer->starty + 1, item->layer->endx, item->layer->endy);
		}
		setcolor(BLACK);
		if (item) {
			rectangle(item->layer->startx, item->layer->starty, item->layer->endx, item->layer->endy);
			circle(item->layer->startx + parameters[0], item->layer->starty + parameters[1], parameters[2]);
		}

	}
}

void Style::active_circle() {
	if (npara == 3) {
		graybg();
		setcolor(BLACK);
		if (item) {
			rectangle(item->layer->startx, item->layer->starty, item->layer->endx, item->layer->endy);
			circle(item->layer->startx + parameters[0], item->layer->starty + parameters[1], parameters[2]);
		}
	}
}

void Style::normal_ellipse() {
	if (npara == 3) {
		setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
		setfillstyle(SOLID_FILL, WHITE);
		if (item) {
			bar(item->layer->startx + 1, item->layer->starty + 1, item->layer->endx, item->layer->endy);
		}
		setcolor(BLACK);
		if (item) {
			rectangle(item->layer->startx, item->layer->starty, item->layer->endx, item->layer->endy);
			ellipse(item->layer->startx + parameters[0], item->layer->starty + parameters[1], 0, 360, parameters[2], (int)(0.5 * parameters[2]));
		}

	}
}

void Style::active_ellipse() {
	if (npara == 3) {
		graybg();
		setcolor(BLACK);
		if (item) {
			rectangle(item->layer->startx, item->layer->starty, item->layer->endx, item->layer->endy);
			ellipse(item->layer->startx + parameters[0], item->layer->starty + parameters[1], 0, 360, parameters[2], (int)(0.5 * parameters[2]));
		}
	}
}

void Style::normal_square() {
	if (npara == 3) {
		setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
		setfillstyle(SOLID_FILL, WHITE);
		if (item) {
			bar(item->layer->startx + 1, item->layer->starty + 1, item->layer->endx, item->layer->endy);
		}
		int centerx, centery, a = parameters[2];
		if (item) {
			centerx = item->layer->startx + parameters[0];
			centery = item->layer->starty + parameters[1];
		}
		setcolor(BLACK);
		if (item) {
			rectangle(item->layer->startx, item->layer->starty, item->layer->endx, item->layer->endy);
		}
		rectangle(centerx - a, centery - a, centerx + a, centery + a);

	}
}

void Style::active_square() {
	if (npara == 3) {
		graybg();
		int centerx, centery, a = parameters[2];
		if (item) {
			centerx = item->layer->startx + parameters[0];
			centery = item->layer->starty + parameters[1];
		}
		setcolor(BLACK);
		if (item) {
			rectangle(item->layer->startx, item->layer->starty, item->layer->endx, item->layer->endy);
		}
		rectangle(centerx - a, centery - a, centerx + a, centery + a);
	}
}

void Style::normal_fill() {
	if (npara == 3) {
		setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
		setfillstyle(SOLID_FILL, WHITE);
		if (item) {
			bar(item->layer->startx + 1, item->layer->starty + 1, item->layer->endx, item->layer->endy);
		}
		int centerx, centery, a = parameters[2];
		if (item) {
			centerx = item->layer->startx + parameters[0];
			centery = item->layer->starty + parameters[1];
		}
		setcolor(BLACK);
		if (item) {
			rectangle(item->layer->startx, item->layer->starty, item->layer->endx, item->layer->endy);
		}
		rectangle(centerx - a, centery - a, centerx + a, centery + a);
		setfillstyle(SOLID_FILL, BLACK);
		floodfill(centerx, centery, BLACK);
		circle(centerx, centery - a, a);
	}
}

void Style::active_fill() {
	if (npara == 3) {
		graybg();
		int centerx, centery, a = parameters[2];
		if (item) {
			centerx = item->layer->startx + parameters[0];
			centery = item->layer->starty + parameters[1];
		}
		setcolor(BLACK);
		if (item) {
			rectangle(item->layer->startx, item->layer->starty, item->layer->endx, item->layer->endy);
		}
		rectangle(centerx - a, centery - a, centerx + a, centery + a);
		setfillstyle(SOLID_FILL, BLACK);
		floodfill(centerx, centery, BLACK);
		circle(centerx, centery - a, a);
	}
}

void Style::normal_line_style() {
	if (npara == 1) {
		setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
		setfillstyle(SOLID_FILL, WHITE);
		if (item) {
			bar(item->layer->startx + 1, item->layer->starty + 1, item->layer->endx, item->layer->endy);
		}
		setcolor(BLACK);
		if (item) {
			rectangle(item->layer->startx, item->layer->starty, item->layer->endx, item->layer->endy);
		}
		setlinestyle(parameters[0], 0, THICK_WIDTH);
		if (item) {
			line(item->layer->startx + 10, item->layer->starty + 5, item->layer->endx - 10, item->layer->endy - 5);
		}
	}
}

void Style::active_line_style() {
	if (npara == 1) {
		graybg();
		setcolor(BLACK);
		if (item) {
			rectangle(item->layer->startx, item->layer->starty, item->layer->endx, item->layer->endy);
		}
		setlinestyle(parameters[0], 0, THICK_WIDTH);
		if (item) {
			line(item->layer->startx + 10, item->layer->starty + 5, item->layer->endx - 10, item->layer->endy - 5);
		}
	}
}

void Style::normal_color() {
	if (npara == 1) {
		setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
		setfillstyle(SOLID_FILL, WHITE);
		if (item) {
			bar(item->layer->startx + 1, item->layer->starty + 1, item->layer->endx, item->layer->endy);
		}
		setfillstyle(SOLID_FILL, parameters[0]);
		if (item) {
			bar(item->layer->startx + 5, item->layer->starty + 5, item->layer->endx - 5, item->layer->endy - 5);
		}
	}
}

void Style::active_color() {
	if (npara == 1) {
		graybg();
		setfillstyle(SOLID_FILL, parameters[0]);
		if (item) {
			bar(item->layer->startx + 5, item->layer->starty + 5, item->layer->endx - 5, item->layer->endy - 5);
		}
	}
}

void Style::normal_rectangle_border() {
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	setcolor(BLACK);
	if (menu) {
		rectangle(menu->layer->startx, menu->layer->starty, menu->layer->endx, menu->layer->endy);
	}
	else if (item) {
		rectangle(item->layer->startx, item->layer->starty, item->layer->endx, item->layer->endy);
	}
	else if (scrollbar) {
		if (scrollbar->h_left && scrollbar->h_right) {
			rectangle(scrollbar->h_left->layer->endx, scrollbar->h_left->layer->starty, scrollbar->h_right->layer->startx, scrollbar->h_right->layer->endy);
		}
		if (scrollbar->v_top && scrollbar->v_bottom) {
			rectangle(scrollbar->v_top->layer->startx, scrollbar->v_top->layer->endy, scrollbar->v_bottom->layer->endx, scrollbar->v_bottom->layer->starty);
		}
	}
	setfillstyle(SOLID_FILL, WHITE);
	if (menu) {
		bar(menu->layer->startx + 1, menu->layer->starty + 1, menu->layer->endx, menu->layer->endy);
	}
	else if (item) {
		bar(item->layer->startx + 1, item->layer->starty + 1, item->layer->endx, item->layer->endy);
	}
	else if (scrollbar) {
		if (scrollbar->h_left) {
			bar(scrollbar->h_left->layer->endx + 1, scrollbar->h_left->layer->starty + 1, scrollbar->h_right->layer->startx, scrollbar->h_right->layer->endy);
		}
		if (scrollbar->v_top) {
			bar(scrollbar->v_top->layer->startx + 1, scrollbar->v_top->layer->endy + 1, scrollbar->v_bottom->layer->endx, scrollbar->v_bottom->layer->starty);
		}
	}
	setfillstyle(EMPTY_FILL, WHITE);
}

void Style::active_rectangle_border() {
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	setcolor(BLACK);
	if (menu) {
		rectangle(menu->layer->startx, menu->layer->starty, menu->layer->endx, menu->layer->endy);
	}
	else if (item) {
		rectangle(item->layer->startx, item->layer->starty, item->layer->endx, item->layer->endy);
	}
	else if (scrollbar) {
		if (scrollbar->h_left && scrollbar->h_right) {
			rectangle(scrollbar->h_left->layer->endx, scrollbar->h_left->layer->starty, scrollbar->h_right->layer->startx, scrollbar->h_right->layer->endy);
		}
		if (scrollbar->v_top && scrollbar->v_bottom) {
			rectangle(scrollbar->v_top->layer->startx, scrollbar->v_top->layer->endy, scrollbar->v_bottom->layer->endx, scrollbar->v_bottom->layer->starty);
		}
	}
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	if (menu) {
		bar(menu->layer->startx + 1, menu->layer->starty + 1, menu->layer->endx, menu->layer->endy);
	}
	else if (item) {
		bar(item->layer->startx + 1, item->layer->starty + 1, item->layer->endx, item->layer->endy);
	}
	else if (scrollbar) {
		if (scrollbar->h_left) {
			bar(scrollbar->h_left->layer->endx + 1, scrollbar->h_left->layer->starty + 1, scrollbar->h_right->layer->startx, scrollbar->h_right->layer->endy);
		}
		if (scrollbar->v_top) {
			bar(scrollbar->v_top->layer->startx + 1, scrollbar->v_top->layer->endy + 1, scrollbar->v_bottom->layer->endx, scrollbar->v_bottom->layer->starty);
		}
	}
	setfillstyle(EMPTY_FILL, WHITE);
}

void Style::hide_KEY() {
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	int sx = Event::item_drawing_area->layer->startx, sy = MAXY - 75, ex = Event::item_drawing_area->layer->endx + 1, ey = MAXY - 49;
	setfillstyle(SOLID_FILL, WHITE);
	bar(sx, sy, ex, ey);
	setfillstyle(EMPTY_FILL, WHITE);
}

void Style::normal_KEY_Circle() {
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	setcolor(BLACK);
	int sx = Event::item_drawing_area->layer->startx, sy = MAXY - 75, ex = Event::item_drawing_area->layer->endx, ey = MAXY - 50;
	rectangle(sx, sy, ex, ey);
	setfillstyle(SOLID_FILL, WHITE);
	bar(sx + 1, sy + 1, ex, ey);
	int textw = 0, texth = textheight("a"), y = (sy + ey - texth) / 2, x = sx + y - sy,
		lx = x + textw;
	setbkcolor(WHITE);
	outtextxy(x + textw, y, "a = ");
	textw = textw + textwidth("a = ");
	outtextxy(x + textw, y, InputText);
	textw = textw + textwidth(InputText);
	if (POS < 85) {
		lx = x + textw;
	}
	outtextxy(x + textw, y, " b = ");
	textw = textw + textwidth(" b = ");
	outtextxy(x + textw, y, InputText + 85);
	textw = textw + textwidth(InputText + 85);
	if (POS >= 85 && POS < 170) {
		lx = x + textw;
	}
	outtextxy(x + textw, y, " r = ");
	textw = textw + textwidth(" r = ");
	outtextxy(x + textw, y, InputText + 170);
	textw = textw + textwidth(InputText + 170);
	if (POS >= 170) {
		lx = x + textw;
	}
	line(lx, y, lx, y + texth);
	setfillstyle(EMPTY_FILL, WHITE);
}

void Style::normal_KEY_Square() {
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	setcolor(BLACK);
	int sx = Event::item_drawing_area->layer->startx, sy = MAXY - 75, ex = Event::item_drawing_area->layer->endx, ey = MAXY - 50;
	rectangle(sx, sy, ex, ey);
	setfillstyle(SOLID_FILL, WHITE);
	bar(sx + 1, sy + 1, ex, ey);
	int textw = 0, texth = textheight("a"), y = (sy + ey - texth) / 2, x = sx + y - sy,
		lx = x + textw;
	setbkcolor(WHITE);
	outtextxy(x + textw, y, "x = ");
	textw = textw + textwidth("x = ");
	outtextxy(x + textw, y, InputText);
	textw = textw + textwidth(InputText);
	if (POS < 85) {
		lx = x + textw;
	}
	outtextxy(x + textw, y, " y = ");
	textw = textw + textwidth(" y = ");
	outtextxy(x + textw, y, InputText + 85);
	textw = textw + textwidth(InputText + 85);
	if (POS >= 85 && POS < 170) {
		lx = x + textw;
	}
	outtextxy(x + textw, y, " a = ");
	textw = textw + textwidth(" a = ");
	outtextxy(x + textw, y, InputText + 170);
	textw = textw + textwidth(InputText + 170);
	if (POS >= 170) {
		lx = x + textw;
	}
	line(lx, y, lx, y + texth);
	setfillstyle(EMPTY_FILL, WHITE);
}

void Style::normal_KEY_Stretch() {
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	setcolor(BLACK);
	int sx = Event::item_drawing_area->layer->startx, sy = MAXY - 75, ex = Event::item_drawing_area->layer->endx, ey = MAXY - 50;
	rectangle(sx, sy, ex, ey);
	setfillstyle(SOLID_FILL, WHITE);
	bar(sx + 1, sy + 1, ex, ey);
	int textw = 0, texth = textheight("a"), y = (sy + ey - texth) / 2, x = sx + y - sy,
		lx = x + textw;
	setbkcolor(WHITE);
	outtextxy(x + textw, y, "X ratio = ");
	textw = textw + textwidth("X ratio = ");
	outtextxy(x + textw, y, InputText);
	textw = textw + textwidth(InputText);
	if (POS < 85) {
		lx = x + textw;
	}
	outtextxy(x + textw, y, " Y ratio = ");
	textw = textw + textwidth(" Y ratio = ");
	outtextxy(x + textw, y, InputText + 85);
	textw = textw + textwidth(InputText + 85);
	if (POS >= 85 && POS < 170) {
		lx = x + textw;
	}
	line(lx, y, lx, y + texth);
	setfillstyle(EMPTY_FILL, WHITE);
}

void Style::normal_KEY_Rotation() {
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	setcolor(BLACK);
	int sx = Event::item_drawing_area->layer->startx, sy = MAXY - 75, ex = Event::item_drawing_area->layer->endx, ey = MAXY - 50;
	rectangle(sx, sy, ex, ey);
	setfillstyle(SOLID_FILL, WHITE);
	bar(sx + 1, sy + 1, ex, ey);
	int textw = 0, texth = textheight("a"), y = (sy + ey - texth) / 2, x = sx + y - sy,
		lx = x + textw;
	setbkcolor(WHITE);
	outtextxy(x + textw, y, "Rotation = ");
	textw = textw + textwidth("Rotation = ");
	outtextxy(x + textw, y, InputText);
	textw = textw + textwidth(InputText);
	if (POS < 85) {
		lx = x + textw;
	}
	line(lx, y, lx, y + texth);
	setfillstyle(EMPTY_FILL, WHITE);
}

void Style::normal_KEY_Shear() {
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	setcolor(BLACK);
	int sx = Event::item_drawing_area->layer->startx, sy = MAXY - 75, ex = Event::item_drawing_area->layer->endx, ey = MAXY - 50;
	rectangle(sx, sy, ex, ey);
	setfillstyle(SOLID_FILL, WHITE);
	bar(sx + 1, sy + 1, ex, ey);
	int textw = 0, texth = textheight("a"), y = (sy + ey - texth) / 2, x = sx + y - sy,
		lx = x + textw;
	setbkcolor(WHITE);
	outtextxy(x + textw, y, "X shear = ");
	textw = textw + textwidth("X shear = ");
	outtextxy(x + textw, y, InputText);
	textw = textw + textwidth(InputText);
	if (POS < 85) {
		lx = x + textw;
	}
	outtextxy(x + textw, y, " Y shear = ");
	textw = textw + textwidth(" Y shear = ");
	outtextxy(x + textw, y, InputText + 85);
	textw = textw + textwidth(InputText + 85);
	if (POS >= 85 && POS < 170) {
		lx = x + textw;
	}
	line(lx, y, lx, y + texth);
	setfillstyle(EMPTY_FILL, WHITE);
}

void Style::normal_select() {
	if (npara == 3) {
		setlinestyle(DASHED_LINE, 0, NORM_WIDTH);
		setfillstyle(SOLID_FILL, WHITE);
		if (item) {
			bar(item->layer->startx + 1, item->layer->starty + 1, item->layer->endx, item->layer->endy);
		}
		int centerx, centery, a = parameters[2];
		if (item) {
			centerx = item->layer->startx + parameters[0];
			centery = item->layer->starty + parameters[1];
		}
		setcolor(BLACK);
		if (item) {
			rectangle(item->layer->startx, item->layer->starty, item->layer->endx, item->layer->endy);
		}
		rectangle(centerx - a, centery - a, centerx + a, centery + a);
		setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	}
}

void Style::active_select() {
	if (npara == 3) {
		graybg();
		setlinestyle(DASHED_LINE, 0, NORM_WIDTH);
		int centerx, centery, a = parameters[2];
		if (item) {
			centerx = item->layer->startx + parameters[0];
			centery = item->layer->starty + parameters[1];
		}
		setcolor(BLACK);
		if (item) {
			rectangle(item->layer->startx, item->layer->starty, item->layer->endx, item->layer->endy);
		}
		rectangle(centerx - a, centery - a, centerx + a, centery + a);
		setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	}
}