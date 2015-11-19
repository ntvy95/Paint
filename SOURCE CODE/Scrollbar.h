/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* STRUCT: Scrollbar.
* DESCRIPTION: Every item (excluding those scroll navigators in Scrollbar struct)
can own itself a scrollbar. This Scrollbar work well only with those
non-child-menu items.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma once
#include "PixelSavior.h"
#include "Item.h"
#include <vector>

struct Style;
struct PixelSavior;
using std::vector;
typedef struct Scrollbar {
	/*ARTRIBUTE*/
	Item* parent;
	PixelSavior* wholeview;
	int startx;
	int starty;
	Item* h_left;
	Item* h_right;
	Item* h_scroll;
	Item* v_top;
	Item* v_bottom;
	Item* v_scroll;
	int scrollthick;
	Style* style;
	/*METHOD*/
	Scrollbar(Item* p);
	void show();
	void update_show();
	void update_h_scroll_width();
	void update_h_scroll_position();
	void update_v_scroll_height();
	void update_v_scroll_position();
	~Scrollbar();
} Scrollbar;

void HorizontalScroll(Scrollbar* scrollbar);
void VerticalScroll(Scrollbar* scrollbar);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* ARTTRIBUTE: Item* parent.
* DESCRIPTION: It points to the item that owns the scrollbar. 
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* ARTTRIBUTE: PixelSavior* wholeview.
* DESCRIPTION: The one that you see at some moment may not be the full picture.
This PixelSavior* wholeview is the place to save the full picture for later
full view or partial view.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */