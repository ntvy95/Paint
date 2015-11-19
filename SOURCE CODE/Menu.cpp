#include "Procedure.h"
#include "Menu.h"
#include "Exceptions.h"
#include "Global.h"
#include "Event.h"

Menu::Menu() {
	parent = NULL;
	layer = new Layer(this);
	max_active = 0;
	style = new Style(this);
	style->normal = &Style::normal_rectangle_border;
	getviewsettings(&viewport);
	set(0, 0, 0, 0, 0, 0, 0);
}

Menu::Menu(int sx, int sy, int iw, int ih, int w, int h, bool d) {
	parent = NULL;
	layer = new Layer(this);
	max_active = 0;
	style = new Style(this);
	style->normal = &Style::normal_rectangle_border;
	set(sx, sy, iw, ih, w, h, d);
}

void Menu::set(int sx, int sy, int iw, int ih, int w, int h, bool d) {
	layer->startx = sx;
	layer->starty = sy;
	itemw = iw;
	itemh = ih;
	width = w;
	height = h;
	iswidthdecisive = d;
}

void Menu::add(Item* item) {
	if (width == 0 && height == 0) {
		throw InvalidArgument();
	}
	int col = 0,
		row = 0,
		size = menu.size();
	if (iswidthdecisive) { //If width is the decisive parameter: Menu width will never change.
		int total = size * itemw;
		col = total % width / itemw;
		row = total / width;
		layer->endx = layer->startx + width;
		if (height == 0) { //if height is auto.
			layer->endy = layer->starty + (row + 1) * itemh;
		}
		else {
			layer->endy = layer->starty + height;
		}
	}
	else { //If height is the decisive parameter: Menu height will never change.
		int total = size * itemh;
		col = total / height;
		row = total % height / itemh;
		layer->endy = layer->starty + height;
		if (width == 0) { //if width is auto.
			layer->endx = layer->startx + (col + 1) * itemw;
		}
		else {
			layer->endx = layer->startx + width;
		}
	}
	if (item->layer == NULL) {
		item->layer = new Layer(item);
	}
	item->layer->startx = layer->startx + col * itemw;
	item->layer->starty = layer->starty + row * itemh;
	item->layer->endx = item->layer->startx + itemw;
	item->layer->endy = item->layer->starty + itemh;
	item->parent = this;
	item->order = size;
	menu.push_back(item);
}

int Menu::getitem(int x, int y) {
	int rx = x - layer->startx, ry = y - layer->starty, row, col;
	int index;
	if (iswidthdecisive) {
		row = ry / itemh, col = rx / itemw;
		index = row * (width / itemw) + col;
	}
	else {
		row = rx / itemw, col = ry / itemh;
		index = row * (height / itemh) + col;
	}
	return index;
}

void Menu::setbelow() {
	below = malloc(imagesize(layer->startx, layer->starty, layer->endx, layer->endy));
	getimage(layer->startx, layer->starty, layer->endx, layer->endy, below);
	Event::layers.add(layer);
}

void Menu::normal() {
	setbelow();

	if (parent && parent->style) {
		(parent->style->*(parent->style->active))();
	}

	if (style && style->normal) {
		(style->*(style->normal))();
	}

	vector<Item*>::iterator end = menu.end();
	for (vector<Item*>::iterator i = menu.begin(); i != end; i++) {
		if ((*i)->style && (*i)->style->normal) {
			changestate((*i)->order, "normal");
		}
		if ((*i)->scrollbar) {
			(*i)->scrollbar->wholeview->set_savior();
			(*i)->scrollbar->show();
		}
	}

}

void Menu::hide() {
	if (below != NULL) {
		vector<Item*>::iterator end = menu.end();
		for (vector<Item*>::iterator i = menu.begin(); i != end; i++) {
			if ((*i)->child != NULL) {
				(*i)->child->hide();
			}
		}

		if (parent && parent->parent && parent->parent->max_active == -1) {
			parent->parent->hide();
		}
		putimage(layer->startx, layer->starty, below, 0);
		free(below);
		below = NULL;
		Event::layers.remove(layer);
	}
}

void Menu::changestate(int a, char* state) {
	Item* item = menu.at(a);
	if (state == "normal") {
		(item->style->*(item->style->normal))();
	}
	if (state == "active") {
		(item->style->*(item->style->active))();
	}
}

Menu::~Menu() {
	if (layer) {
		delete layer;
		layer = NULL;
	}
	if (style) {
		delete style;
		style = NULL;
	}
	vector<Item*>::iterator end = menu.end();
	for (vector<Item*>::iterator i = menu.begin(); i != end; i++) {
		(*i)->~Item();
		delete (*i);
	}
	menu.clear();
	active.clear();
}