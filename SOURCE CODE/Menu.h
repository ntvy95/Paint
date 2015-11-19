#pragma once
#include "Item.h"
#include <vector>
#include "Layer.h"
#include "graphics.h"
#pragma comment(lib, "graphics.lib")

using std::vector;
struct Item;
struct Layer;
struct Style;
typedef struct Menu {
	/*ARTTRIBUTE*/
	Style* style;
	void* below;
	Layer* layer;
	Item* parent;
	vector<Item*> menu;
	vector<Item*> active;	
	int max_active;
	int itemw;
	int itemh;
	int width;
	int height;
	bool iswidthdecisive;
	struct viewporttype viewport;
	/*METHOD*/
	Menu();
	Menu(int sx, int sy, int iw, int ih, int w, int h, bool d);
	void set(int sx, int sy, int iw, int ih, int w, int h, bool d);
	void add(Item* item);
	void setbelow();
	void normal();
	void hide();
	void changestate(int a, char* state);
	int getitem(int x, int y);
	~Menu();
} Menu;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* ARTTRIBUTE: int max_active.
* DESCRIPTION: This is the max number of items are on the active style state
(of course, it is the max number of items allowed to be stored in
vector<Item*> active). -1 for none, 0 for no limit. Also, menu with
max_active == -1 will be treated as a hover-dropdown menu. With this, we have
a convetion that the multi-active-items menu is only available for click not
for hover. For your information, there is no multi-active-items menu at the
moment.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */