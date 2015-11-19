/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* STRUCT: Layer.
* DESCRIPTION: This struct is imitation of layer concept in Adobe Photoshop.
When the mouse move over a position, it will only "touch" the most above layer
of that position. Even so, not all the layer of Layer struct type have a chance
to display on the screen: For more information, please make reference to the
Layers struct in Layers.h header file.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma once
#include "Menu.h"

struct Graph;
struct Menu;
struct Item;
typedef struct Layer {
	int startx;
	int starty;
	int endx;
	int endy;
	Menu* menu;
	Item* item;
	Layer* above;
	Layer* below;
	/*METHOD*/
	Layer(Menu* m);
	Layer(Item* i);
	Layer(Graph* g);
	~Layer();
	void init_layer(Menu* m = NULL, Item* i = NULL, Graph* g = NULL);
	bool contain(int x, int y);
} Layer;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* ATTRIBUTES: int startx, int starty, int endx, int endy.
* DESCRIPTION: The item / menu is placed inside a rectangle with startx and
starty for the top left, endx and eny for the bottom right.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* ATTRIBUTES: Menu* menu, Item* item.
* DESCRIPTION: This is the linked menu and item of the layer. Although we have
two data types here but one layer only has one non-NULL of these two (the other
must be NULL).
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* ATTRIBUTES: Layer* above, Layer* below.
* DESCRIPTION: Store the links to the layers that are directly above or
directly below the current layer. If the current layer is not present in any
Layers layers then these two value will be NULL, so the current layer becomes
a place to store the startx, starty, endx, endy of an item / menu.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */