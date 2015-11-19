/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* STRUCT: ItemEvent.
* DESCRIPTION: Each item have its own events. These events are all related to
mouse events.
* PREFIX:
no prefix : The procedure may be called in whatever mouse handler procedure.
hover_ : The procedure may be called in event_mousemove with is_leftdown has
been set to false. It is called when we hover over the item.
hover_ : The procedure may be called in event_mousemove with is_leftdown has
been set to false. It is called when we do not hover the item anymore.
leftdown_ : The procedure may be called in event_leftdown.
leftdrag_ : The procedure may be called in event_mousemove with is_leftdown has
been set to true.
leftup_ : The procedure may be called in event_leftup.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma once
#include "Item.h"
#include "Global.h"

struct Item;
struct Layers;
typedef struct ItemEvent {
	/*STATIC MEMBER*/
	static void be_active(Item* item);
	/*ARTRIBUTE*/
	Item* item;
	void(ItemEvent::*hover)();
	void(ItemEvent::*hover_inactive)();
	void(ItemEvent::*leftdown)();
	void(ItemEvent::*leftdrag)();
	void(ItemEvent::*leftup)();
	/*PROCEDURE*/
	ItemEvent(Item* i);
	~ItemEvent();
	/*HOVER OPTION*/
	void hover_menu();
	void hover_graph();
	void hover_drawing_area();
	/*HOVER INACTIVE OPTION*/
	void hover_inactive_menu();
	void hover_inactive_graph();
	void hover_inactive_drawing_area();
	/*LEFTCLICK OPTION*/
	void leftdown_keyboard_circle();
	void leftdown_keyboard_square();
	void leftdown_keyboard_stretch();
	void leftdown_keyboard_rotate();
	void leftdown_keyboard_shear();
	void leftdown_crop();
	void leftdown_parabol();
	void leftdown_line();
	void leftdown_circle();
	void leftdown_ellipse();
	void leftdown_square();
	void leftdown_fillcolor();
	void leftdown_draw();
	void leftdrag_draw();
	void leftup_draw();
	void leftup_color();
	void leftdown_character();
	void scroll_down();
	void scroll_up();
	void scroll_up_down();
	void scroll_right();
	void scroll_left();
	void scroll_left_right();
	void leftdown_new();
	void leftdown_graph();
	void leftdrag_graph();
	void leftup_graph();
	void leftdown_select();
	void leftdown_move();
	void leftdown_undo();
	void leftdown_bezier();
} ItemEvent;

void mergelayers(Layers* layers);