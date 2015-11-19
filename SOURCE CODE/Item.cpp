#include "Item.h"
#include "graphics.h"
#pragma comment(lib, "graphics.lib")

Item::Item(Menu* c, char* t, int* p, int N, void(Style::*no)(), void(Style::*ac)()) {
	graph = NULL;
	scrollbar = NULL;
	layer = NULL;
	layers = NULL;
	style = new Style(this);
	mouse_event = new ItemEvent(this);
	is_active = false;
	parent = NULL;
	scrollbar_parent = NULL;
	set(c, t, p, N, no, ac);
}

void Item::set(Menu* c, char* t, int* p, int N, void(Style::*no)(), void(Style::*ac)()) {
	child = c;
	if (child != NULL) {
		child->parent = this;
	}
	style->text = t;
	style->parameters = p;
	style->npara = N;
	style->normal = no;
	style->active = ac;
}

Item::~Item() {
	if (layers) {
		delete layers;
		layers = NULL;
	}
	if (layer) {
		if (parent && parent->parent && parent->parent->layers) {
			parent->parent->layers->remove(layer);
		}
		delete layer;
		layer = NULL;
	}
	if (child) {
		delete child;
		child = NULL;
	}
	if (mouse_event) {
		delete mouse_event;
		mouse_event = NULL;
	}
	if (style) {
		delete style;
		style = NULL;
	}
	if (scrollbar) {
		delete scrollbar;
		scrollbar = NULL;
	}
}