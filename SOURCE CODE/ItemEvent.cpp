#include "ItemEvent.h"
#include "Event.h"
#include "Procedure.h"
#include "KeyboardInput.h"
#include "DrawingAlgorithm.h"

using std::stack;
stack<void*> Event::saved_screens;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: ItemEvent::ItemEvent.
* INPUT: Item* i.
* OUTPUT: none.
* DESCRIPTION: This is a constructor of ItemEvent struct.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
ItemEvent::ItemEvent(Item* i) {
	item = i;
	hover = NULL;
	hover_inactive = NULL;
	leftdown = NULL;
	leftdrag = NULL;
	leftup = NULL;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: ItemEvent::be_active.
* INPUT: Item* item.
* OUTPUT: void.
* DESCRIPTION: This is the procedure to check whether the item is legal to be in
active style state on the menu. If it is or there is a parent item of it that
is legal to be in active style state, we will turn it or its parent item into
active style state in the way that makes sure the direct parent menu does not
have number of items in active style state exceeds the number stored in
max_active attribute.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void ItemEvent::be_active(Item* item) {
	Item* traverse = item;

	//If the direct parent menu of the traverse is a hover-dropdown menu so the item will not be legal to be in active style state.
	//So we will try to find the upper non-hover-dropdown menu if there is one.
	while (traverse && traverse->parent && traverse->parent->max_active == -1 && traverse->parent->parent) {
		traverse->parent->hide();
		traverse = traverse->parent->parent;
	}

	Menu* menu = traverse->parent;

	//If there is one, we will activate the parent item of the input item that have direct parent menu is non-hover-dropdown menu.
	if (menu) {
		if (menu->active.size() < (unsigned)(menu->max_active)) {
			if (traverse->is_active == false) {
				menu->changestate(traverse->order, "active");
				menu->active.push_back(traverse);
			}
		}
		else {
			Item* inact = menu->active.back();
			inact->is_active = false;
			menu->changestate(inact->order, "normal");
			menu->active.pop_back();
			menu->changestate(traverse->order, "active");
			menu->active.push_back(traverse);
		}
		traverse->is_active = true;
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: ItemEvent::hover_menu.
* INPUT: none.
* OUTPUT: void.
* DESCRIPTION: Turn the current item into active style state and show its
child hover-dropdown menu if there is one.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void ItemEvent::hover_menu() {
	(item->style->*(item->style->active))();
	if (item->child && item->child->max_active == -1) {
		item->child->normal();
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: ItemEvent::hover_inactive_menu.
* INPUT: none.
* OUTPUT: void.
* DESCRIPTION: Hide the item's child hover-dropdown menu if there is one and
turn the item into normal style state if the item is not set as an hold-active
item on the menu.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void ItemEvent::hover_inactive_menu() {
	if (item->child && item->child->max_active == -1) {
		item->child->hide();
	}

	if (item->is_active == false) {
		(item->style->*(item->style->normal))();
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: ItemEvent::leftdown_keyboard_circle.
* INPUT: none.
* OUTPUT: void.
* DESCRIPTION: Let the user draw circle through keyboard. It only sets flag,
the handling procedure is in Main.cpp and KeyboardInput.cpp file.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void ItemEvent::leftdown_keyboard_circle() {
	Event::KeyboardInput = Event::INPUT_CIRCLE;
	Event::draw = Event::CIRCLE;
	be_active(item);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: ItemEvent::leftdown_keyboard_square.
* INPUT: none.
* OUTPUT: void.
* DESCRIPTION: Let the user draw square through keyboard. It only sets flag,
the handling procedure is in Main.cpp and KeyboardInput.cpp file.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void ItemEvent::leftdown_keyboard_square() {
	Event::KeyboardInput = Event::INPUT_SQUARE;
	Event::draw = Event::SQUARE;
	be_active(item);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: ItemEvent::leftdown_line.
* INPUT: none.
* OUTPUT: void.
* DESCRIPTION: Set flag Event::draw to Event::LINE for later click-drag line
drawing.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void ItemEvent::leftdown_line() {
	Event::draw = Event::LINE;
	be_active(item);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: ItemEvent::leftdown_circle.
* INPUT: none.
* OUTPUT: void.
* DESCRIPTION: Set flag Event::draw to Event::CIRCLE for later click-drag circle
drawing.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void ItemEvent::leftdown_circle() {
	Event::draw = Event::CIRCLE;
	be_active(item);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: ItemEvent::leftdown_square(.
* INPUT: none.
* OUTPUT: void.
* DESCRIPTION: Set flag Event::draw to Event::SQUARE for later click-drag square
drawing.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void ItemEvent::leftdown_square() {
	Event::draw = Event::SQUARE;
	be_active(item);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: ItemEvent::leftdown_fillcolor.
* INPUT: none.
* OUTPUT: void.
* DESCRIPTION: Set flag Event::draw to Event::FILLCOLOR for later click fill
color.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void ItemEvent::leftdown_fillcolor() {
	mergelayers(Event::item_drawing_area->layers);
	Event::draw = Event::FILLCOLOR;
	be_active(item);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: ItemEvent::leftdown_draw.
* INPUT: none.
* OUTPUT: void.
* DESCRIPTION: Set the viewport for drawing.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void ItemEvent::leftdown_draw() {
	switch (Event::draw) {
		case Event::GRAPH: Event::down_draw_graph(); break;
		case Event::BEZIER: Event::down_draw_bezier(); break;
	}
	if (item->graph) {
		hover_inactive_graph();
		hover_drawing_area();
	}
	void* screen = malloc(imagesize(0, 0, Event::item_drawing_area->parent->itemw, Event::item_drawing_area->parent->itemh));
	getimage(0, 0, Event::item_drawing_area->parent->itemw, Event::item_drawing_area->parent->itemh, screen);
	Event::saved_screens.push(screen);
}

void ItemEvent::leftdrag_draw() {
	switch (Event::draw) {
		case Event::NONE: break;
		case Event::SELECT: Event::drag_select(); break;
		case Event::CIRCLE: Event::drag_draw_circle(); break;
		case Event::ELLIPSE: Event::drag_draw_ellipse(); break;
		case Event::SQUARE: Event::drag_draw_square(); break;
		case Event::LINE: Event::drag_draw_line(); break;
		case Event::GRAPH: Event::drag_draw_graph(); break;
		case Event::PARABOL: Event::drag_draw_parabol(); break;
		case Event::BEZIER: Event::drag_draw_bezier(); break;
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: ItemEvent::leftup_draw.
* INPUT: none.
* OUTPUT: void.
* DESCRIPTION: Release the viewport.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void ItemEvent::leftup_draw() {
	switch (Event::draw) {
		case Event::NONE: break;
		case Event::SELECT: Event::up_select(); break;
		case Event::CIRCLE: Event::up_draw_circle(); break;
		case Event::ELLIPSE: Event::up_draw_ellipse(); break;
		case Event::SQUARE: Event::up_draw_square(); break;
		case Event::LINE: Event::up_draw_line(); break;
		case Event::FILLCOLOR: Event::up_fillcolor(); break;
		case Event::GRAPH: Event::up_draw_graph(); break;
		case Event::PARABOL: Event::up_draw_parabol(); break;
		case Event::BEZIER: Event::up_draw_bezier(); break;
	}
}

void ItemEvent::leftup_color() {
	Event::color = item->style->parameters[0];
	be_active(item);
}

void ItemEvent::leftdown_bezier() {
	Event::draw = Event::BEZIER;
	be_active(item);
}

void ItemEvent::leftdown_character() {
	Event::draw = Event::GRAPH;
	if (Event::graph_sample) {
		delete Event::graph_sample;
		Event::graph_sample = NULL;
	}
	//This may be a souce of problems. Though, time is limited, health is limited. Sorry.
	switch (item->style->text[0]) {
		case 'A': Event::graph_sample = ::characterA(); break;
		case 'B': Event::graph_sample = ::characterB(); break;
		case 'C': Event::graph_sample = ::characterC(); break;
	}
	be_active(item);
}

void ItemEvent::scroll_down() {
	mergelayers(Event::item_drawing_area->layers);
	Event::scroll_down();
}

void ItemEvent::scroll_up() {
	mergelayers(Event::item_drawing_area->layers);
	Event::scroll_up();
}

void ItemEvent::scroll_up_down() {
	mergelayers(Event::item_drawing_area->layers);
	Event::scroll_up_down();
}

void ItemEvent::scroll_right() {
	mergelayers(Event::item_drawing_area->layers);
	Event::scroll_right();
}

void ItemEvent::scroll_left() {
	mergelayers(Event::item_drawing_area->layers);
	Event::scroll_left();
}

void ItemEvent::scroll_left_right() {
	Layer* layer = Event::item_drawing_area->layers->upabove;
	while (layer != NULL) {
		Event::item_drawing_area->layers->remove(layer);
		bool deleted = false;
		if (layer->menu) {
			delete layer->menu;
			deleted = true;
		}
		else if (layer->item) {
			delete layer->item;
			deleted = true;
		}
		if (deleted == false) {
			delete layer;
		}
		layer = Event::item_drawing_area->layers->upabove;
	}
	Event::scroll_left_right();
}

void ItemEvent::leftdown_new() {
	if (Event::graph_sample) {
		delete Event::graph_sample;
		Event::graph_sample = NULL;
		Event::draw = Event::NONE;
	}
	if (item->parent->max_active == -1) {
		item->parent->hide();
	}
	Event::item_drawing_area->scrollbar->~Scrollbar();
	mergelayers(Event::item_drawing_area->layers);
	Event::item_current = NULL;
	Event::old_item_current = NULL;
	Event::old_item_current_leftdown = NULL;
	Event::item_drawing_area->scrollbar->Scrollbar::Scrollbar(Event::item_drawing_area);
	Event::item_drawing_area->scrollbar->show();
	setfillstyle(SOLID_FILL, WHITE);
	bar(Event::item_drawing_area->layer->startx + 1, Event::item_drawing_area->layer->starty + 1, Event::item_drawing_area->layer->endx - Event::item_drawing_area->scrollbar->scrollthick, Event::item_drawing_area->layer->endy - Event::item_drawing_area->scrollbar->scrollthick);
	setfillstyle(EMPTY_FILL, WHITE);
	while (Event::saved_screens.size() > 0) {
		delete Event::saved_screens.top();
		Event::saved_screens.pop();
	}
}

void ItemEvent::leftdown_graph() {
	leftdown_draw();
	if (Event::draw == Event::SHEAR) {
		Event::KeyboardInput = Event::INPUT_SHEAR;
		Event::graph_sample = item->graph;
	}
	else if (Event::draw == Event::STRETCH) {
		Event::KeyboardInput = Event::INPUT_STRETCH;
		Event::graph_sample = item->graph;
	}
	else if (Event::draw == Event::ROTATE) {
		Event::KeyboardInput = Event::INPUT_ROTATE;
		Event::graph_sample = item->graph;
	}
	else if (Event::draw == Event::MOVE) {
		Event::graph_sample = item->graph;
		Event::down_move_graph();
	}
	else {
		Event::item_current = Event::item_drawing_area;
	}
}

void ItemEvent::leftdrag_graph() {
	if (Event::draw == Event::MOVE) {
		Event::drag_move_graph();
	}
	else {
		Event::item_current = Event::item_drawing_area;
		leftdrag_draw();
	}
}

void ItemEvent::leftup_graph() {
	if (Event::draw == Event::MOVE) {
		Event::up_move_graph();
	}
	else {
		Event::item_current = Event::item_drawing_area;
		leftup_draw();
	}
}

void ItemEvent::leftdown_select() {
	Event::draw = Event::SELECT;
	be_active(item);
}

void ItemEvent::leftdown_move() {
	Event::draw = Event::MOVE;
}

void ItemEvent::leftdown_keyboard_rotate() {
	Event::draw = Event::ROTATE;
}

void ItemEvent::leftdown_parabol() {
	Event::draw = Event::PARABOL;
	be_active(item);
}

void ItemEvent::leftdown_undo() {
	item->parent->hide();
	mergelayers(Event::item_drawing_area->layers);
	if (Event::saved_screens.size() > 0) {
		void* screen = Event::saved_screens.top();
		putimage(Event::item_drawing_area->layer->startx + 1, Event::item_drawing_area->layer->starty + 1, screen, 0);
		free(screen);
		Event::saved_screens.pop();
	}
}

void ItemEvent::leftdown_keyboard_stretch() {
	Event::draw = Event::STRETCH;
}

void ItemEvent::leftdown_keyboard_shear() {
	Event::draw = Event::SHEAR;
}

void ItemEvent::leftdown_ellipse() {
	Event::draw = Event::ELLIPSE;
	be_active(item);
}

void ItemEvent::hover_graph() {
	hover_drawing_area();
	item->graph->showlayer();
}

void ItemEvent::hover_inactive_graph() {
	hover_drawing_area();
	putimage(item->layer->startx, item->layer->starty, item->graph->below, 0);
	item->graph->show();
	Layer* layer = item->layer->above;
	while (layer && layer->item && layer->item->graph) {
		layer->item->graph->show();
		layer = layer->above;
	}
	hover_inactive_drawing_area();
}

void ItemEvent::hover_drawing_area() {
	if (Event::is_setviewport == false) {
		setviewport(Event::item_drawing_area->layer->startx + 1, Event::item_drawing_area->layer->starty + 1, Event::item_drawing_area->layer->endx - Event::item_drawing_area->scrollbar->scrollthick, Event::item_drawing_area->layer->endy - Event::item_drawing_area->scrollbar->scrollthick, 1);
		Event::item_drawing_area->layers->is_setviewport = true;
		Event::is_setviewport = true;
	}
}

void ItemEvent::hover_inactive_drawing_area() {
	if (Event::is_setviewport == true) {
		setviewport(0, 0, MAXX, MAXY, 1);
		Event::item_drawing_area->layers->is_setviewport = false;
		Event::is_setviewport = false;
	}
}

void ItemEvent::leftdown_crop() {
	item->parent->hide();
	Event::down_crop();
}

ItemEvent::~ItemEvent() {

}

void mergelayers(Layers* layers) {
	Layer* layer = layers->upabove;
	while (layer != NULL) {
		layers->remove(layer);
		bool deleted = false;
		if (layer->menu) {
			delete layer->menu;
			deleted = true;
		}
		else if (layer->item) {
			delete layer->item;
			deleted = true;
		}
		if (deleted == false) {
			delete layer;
		}
		layer = layers->upabove;
	}
}