/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* STRUCT: Item.
* DESCRIPTION: This is the smallest unit that we will work on with. Item is
inside a menu or a scrollbar or maybe it does not belong to anyone - a free
item.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma once
#include "Menu.h"
#include "ItemEvent.h"
#include "Layer.h"
#include "Style.h"
#include "Scrollbar.h"
#include "Layers.h"

struct Menu;
struct Layer;
struct Layers;
struct ItemEvent;
struct Style;
struct Scrollbar;
struct Graph;

typedef struct Item {
	/*ARTTRIBUTE*/
	Menu* parent;
	int order;
	Menu* child;
	Graph* graph;
	Layer* layer;
	Layers* layers;
	ItemEvent* mouse_event;
	Style* style;
	Scrollbar* scrollbar;
	Scrollbar* scrollbar_parent;
	bool is_active;
	/*METHOD*/
	Item(Menu* c, char* t, int* p, int N, void(Style::*no)(), void(Style::*ac)());
	void set(Menu* c, char* t, int* p, int N, void(Style::*no)(), void(Style::*ac)());
	~Item();
} Item;

//The Item constructor / set procedure contain arttibutes belongs to the Style struct for convenience.