/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*COLLECTION: Event.
*DESCRIPTION: This collects the procedures that handles mouse events.
*PREFIX:
no prefix : The procedure may be called in whatever mouse handler procedure.
drag_ : The procedure may be called in event_move.
up_ : The procedure may be called in event_leftup.
down_ : The procedure may be called in event_leftdown.
* HOW TO: When a mouse event is detected, the item will make reference to 
the ItemEvent* mouse_event to call one of the procedure: hover, hover_inactive,
leftdown, leftdrag, leftup. Once called, the ItemEvent procedure may set the
flag or directly call the procedures in Event namespace.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma once
#include "Layers.h"
#include "Item.h"
#include "Global.h"
#include "Graph.h"
#include "graphics.h"
#pragma comment(lib, "graphics.lib")
#include <stack>
using std::stack;

struct Item;
struct Layers;
namespace Event {
	extern Layers layers;
	const enum shape { NONE, ELLIPSE, SHEAR, ROTATE, STRETCH, MOVE, SELECT, CIRCLE, SQUARE, LINE, FILLCOLOR, GRAPH, PARABOL, BEZIER };
	const enum input { INPUT_NONE, INPUT_SHEAR, INPUT_CIRCLE, INPUT_SQUARE, INPUT_STRETCH, INPUT_ROTATE };
	extern shape draw;
	extern Item	*item_current,
				*old_item_current,
				*old_item_current_leftdown,
				*item_drawing_area;
	extern Graph* graph_sample;
	extern int color;
	extern bool is_setviewport;
	extern input KeyboardInput;
	extern stack<void*> saved_screens;

	void event_leftdown(int x, int y);
	void event_move(int x, int y);
	void event_leftup(int x, int y);

	//Draw shape, fill color,v.v...
	void drag_draw_ellipse();
	void up_draw_ellipse();
	void drag_draw_line();
	void up_draw_line();
	void drag_draw_circle();
	void up_draw_circle();
	void drag_draw_square();
	void up_draw_square();
	void drag_select();
	void up_select();
	void up_fillcolor();
	void down_draw_graph();
	void drag_draw_graph();
	void up_draw_graph();
	void down_move_graph();
	void drag_move_graph();
	void up_move_graph();
	void down_crop();
	void up_draw_parabol();
	void drag_draw_parabol();
	void down_draw_bezier();
	void drag_draw_bezier();
	void up_draw_bezier();

	//Scrollbar.
	void scroll_down();
	void scroll_up();
	void scroll_up_down();
	void scroll_right();
	void scroll_left();
	void scroll_left_right();
}