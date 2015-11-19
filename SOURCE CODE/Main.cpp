/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* PROGRAM TITLE: Paint.
* PROGRAM DESCRIPTION: This program is an effort to make a copy of MS Paint.
* DEVELOPER: Nguyen Thuy Vy / 13521064.
* UNIVERSITY: University of Information Technology.
* PROGRAMMING LANGUAGE: C / C++.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* PROGRAMMING NOTES
* As you may see, this program is not built on functional programming paradigm as you may expect
* nor it is a good use of object-oriented paradigm, that is: The encapsulation of this program
* is weak leading to a large amount of possibly unhandled corruptions. Along with that, there
* are those that you may find it can be improved much better, those that you may find them twisted
* or unnatural. However, the time for this project is limited so I have to make a choice between
* perfect coding or so-so coding but "good enough" to represent my basic ideas. (basic ideas, not
* whole ideas, also due to the limited time or twisted mind at that time or just... a lack of
* programming skill)
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* SIDE NOTES
* Also, "Object-oriented programming is for stupid people." quote may be right, still I prefers
* myself to be such stupid people in this program: less works to do after some weak encapsulations,
* despite the fact that I hate object-oriented programming.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* CORRECTIONS
* Due to the twisted mind at that time, I commented that a member procedure of a struct may have
no input, and that is totally wrong. Here is the correction: A member procedure of a struct
always has an implicit parameter and that is the "this" pointer of the current object. Though,
the time is limit so I will make this a convention without fixing the old comments.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Global.h"
#include "MenuList.h"
#include "ItemEvent.h"
#include "Event.h"
#include "Procedure.h"
#include "KeyboardInput.h"
#include "graphics.h"
#pragma comment(lib, "graphics.lib")

using std::stack;

Layers Event::layers;
Event::shape Event::draw = Event::NONE;
Item *Event::item_current = NULL,
	 *Event::old_item_current = NULL,
	 *Event::old_item_current_leftdown = NULL,
	 *Event::item_drawing_area;
int Event::color;
bool Event::is_setviewport = false;
int MAXX, MAXY;
Graph* Event::graph_sample = NULL;
Event::input Event::KeyboardInput = Event::INPUT_NONE;
int Style::POS = 0;

void main() {
	//The width and height of the program is customable.
	MAXX = input("Nhap chieu rong cua window (>= 500): ", 500);
	MAXY = input("Nhap chieu dai cua window (>= 500): ", 500);
	int grd, grm;
	detectgraph(&grd, &grm);
	initwindow(MAXX + 1, MAXY + 1, "Paint");

	//We transfer the mouse handler to three custom mouse handler procedure.
	registermousehandler(WM_MOUSEMOVE, Event::event_move);
	registermousehandler(WM_LBUTTONDOWN, Event::event_leftdown);
	registermousehandler(WM_LBUTTONUP, Event::event_leftup);
	
	//We draw the menu.
	Menu* menu[8];
	menu[0] = MenuBar(menu);
	menu[1] = ToolPanel(menu);
	menu[2] = DrawingArea(menu);
	menu[3] = StyleMenu(menu);
	menu[4] = ColorMenu(menu);

	setbkcolor(WHITE);
	cleardevice();
	setbkcolor(WHITE);

	menu[0]->normal();
	menu[1]->normal();
	menu[2]->normal();
	menu[3]->normal();
	ItemEvent::be_active(menu[3]->menu.at(0));
	menu[4]->normal();
	ItemEvent::be_active(menu[4]->menu.at(0));
	Event::color = menu[4]->menu.at(0)->style->parameters[0];

	//If we omit this loop, we will gain a paint program with little CPU utilization.
	//Though this loop is here to catch the user input event.
	//Wish that the registerkeyboardhandler exists.
	while (true) {
		switch (Event::KeyboardInput) {
		case Event::INPUT_CIRCLE:
			KeyboardInput_INPUT_CIRCLE();
			break;
		case Event::INPUT_SQUARE:
			KeyboardInput_INPUT_SQUARE();
			break;
		case Event::INPUT_STRETCH:
			KeyboardInput_INPUT_STRETCH();
			break;
		case Event::INPUT_ROTATE:
			KeyboardInput_INPUT_ROTATE();
			break;
		case Event::INPUT_SHEAR:
			KeyboardInput_INPUT_SHEAR();
			break;
		}
	}
	getch();
	closegraph();
}