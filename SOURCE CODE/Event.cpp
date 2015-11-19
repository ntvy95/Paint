#include "Event.h"
#include "DrawingAlgorithm.h"
#include "Procedure.h"

namespace Event {
	int x1, y1, x2, y2; //Mainly used for Drawing Area.
	bool is_leftdown = false;
	bool is_dragging = false;
	void *save = NULL,
		 *save1 = NULL; //Mainly used for Drawing Area: The place to save the old not yet decided drawing.
	int left, top, right, bottom,
		left1, top1, right1, bottom1; //Mainly used for Drawing Area.
	Graph* drawing_graph;
	int each_scroll = 20;
	vector<Point> storedpoints;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: Event::event_leftdown.
* INPUT: int x, int y.
* OUTPUT: void.
* DESCRIPTION: This the mouse handler for WM_LBUTTONDOWN event.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void Event::event_leftdown(int x, int y) {
	if (is_dragging) {
		event_leftup(x, y);
	}
	else {
		if (old_item_current_leftdown != item_current
			&& old_item_current_leftdown
			&& old_item_current_leftdown->parent
			&& old_item_current_leftdown->parent->max_active == -2) {
			struct viewporttype viewport = old_item_current_leftdown->parent->viewport;
			setviewport(viewport.left, viewport.top, viewport.right, viewport.bottom, 1);
			old_item_current_leftdown->parent->hide();
			setviewport(0, 0, MAXX, MAXY, 1);
		}
		old_item_current_leftdown = item_current;
	}

	if (Event::draw != Event::BEZIER && storedpoints.size() != 0) { //A little specific.
		free(save1);
		save1 = NULL;
		setviewport(Event::item_drawing_area->layer->startx + 1, Event::item_drawing_area->layer->starty + 1, Event::item_drawing_area->layer->endx - Event::item_drawing_area->scrollbar->scrollthick, Event::item_drawing_area->layer->endy - Event::item_drawing_area->scrollbar->scrollthick, 1);
		BezierSavior(storedpoints, Event::color, Event::item_drawing_area->scrollbar);
		setviewport(0, 0, MAXX, MAXY, 1);
		storedpoints.clear();
		Event::item_drawing_area->scrollbar->update_show();
	}

	x1 = x;
	y1 = y;

	is_leftdown = true;

	if (item_current && item_current->mouse_event && item_current->mouse_event->leftdown) {
		(item_current->mouse_event->*(item_current->mouse_event->leftdown))();
	}

	if (is_setviewport) {
		struct viewporttype viewport_info;
		getviewsettings(&viewport_info);
		x1 = x1 - viewport_info.left - 1;
		y1 = y1 - viewport_info.top - 1;
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: Event::event_move.
* INPUT: int x, int y.
* OUTPUT: void.
* DESCRIPTION: This the mouse handler for WM_MOUSEMOVE event.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void Event::event_move(int x, int y) {
	x2 = x;
	y2 = y;

	if (is_setviewport) {
		struct viewporttype viewport_info;
		getviewsettings(&viewport_info);
		x2 = x2 - viewport_info.left - 1;
		y2 = y2 - viewport_info.top - 1;
	}

	if (is_leftdown == false) {
		//Determine which item we will be working with. This is the reason why we have Menu-Item-Layer concept.
		if (save) {
			free(save);
			save = NULL;
		}
		Layer* layer = layers.upabove;
		Item* temp_item = NULL;
		while (layer != NULL) {
			item_current = NULL;
			if (layer->contain(x, y) == true) {
				if (layer->menu) {
					Menu* menu = layer->menu;
					unsigned int itemindex = menu->getitem(x, y);
					if (itemindex < menu->menu.size()) {
						item_current = menu->menu.at(itemindex);
					}
				}
				else if (layer->item) {
					item_current = layer->item;
				}
				if (item_current && item_current->layers) {
					if (item_current->layers->is_setviewport == true) {
						struct viewporttype viewport_info;
						getviewsettings(&viewport_info);
						x = x - viewport_info.left - 1;
						y = y - viewport_info.top - 1;
					}
					layer = item_current->layers->upabove;
					temp_item = item_current;
				}
				else {
					break;
				}
			}
			else {
				layer = layer->below;
			}
			if (temp_item) {
				item_current = temp_item;
			}
		}
	}
	else {
		is_dragging = true;
		if (item_current && item_current->mouse_event && item_current->mouse_event->leftdrag) {
			if (save) {
				putimage(left, top, save, 0);
				free(save);
				save = NULL;
			}
			(item_current->mouse_event->*(item_current->mouse_event->leftdrag))();
		}
	}
	if (item_current != old_item_current) {
		//If the item_current is on a hover-dropdown menu.
		if (item_current && item_current->parent && item_current->parent->max_active == -1) {
			//Then the old_item_current must be its parent or its fellow, we should set the item style to normal if possible
			//and we must not hide its parent nor its child menu.
			if (old_item_current->style && old_item_current->style->normal) {
				(old_item_current->style->*(old_item_current->style->normal))();
			}
		}
		else if (old_item_current) {
			//If the old_item_current is on a hover-dropdown menu but the item_current is not then we should hide that menu.
			if (old_item_current->parent && old_item_current->parent->max_active == -1) {
				old_item_current->parent->hide();
				//If the parent item of old_item_current is in active state then we turn the parent item back into active style state.
				if (old_item_current->parent->parent && old_item_current->parent->parent->is_active) {
					Item* parent_item = old_item_current->parent->parent;
					(parent_item->style->*(parent_item->style->active))();
				}
			}
			//If not then we just use the hover_inactive effect if it has one.
			else if (old_item_current->mouse_event && old_item_current->mouse_event->hover_inactive) {
				(old_item_current->mouse_event->*(old_item_current->mouse_event->hover_inactive))();
			}
		}
		//Set the old_item_current = item_current and take the hover effect of it.
		old_item_current = item_current;
		if (old_item_current && old_item_current->mouse_event && old_item_current->mouse_event->hover) {
			(old_item_current->mouse_event->*(old_item_current->mouse_event->hover))();
		}
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: Event::event_leftup.
* INPUT: int x, int y.
* OUTPUT: void.
* DESCRIPTION: This the mouse handler for WM_LBUTTONUP event.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void Event::event_leftup(int x, int y) {
	x2 = x;
	y2 = y;
	if (is_setviewport) {
		struct viewporttype viewport_info;
		getviewsettings(&viewport_info);
		x2 = x2 - viewport_info.left - 1;
		y2 = y2 - viewport_info.top - 1;
	}

	if (save) {
		putimage(left, top, save, 0);
		free(save);
		save = NULL;
	}
	if (item_current && item_current->mouse_event && item_current->mouse_event->leftup) {
		(item_current->mouse_event->*(item_current->mouse_event->leftup))();
	}
	is_leftdown = false;
	is_dragging = false;
}

void Event::drag_draw_line() {
	if (x1 < x2) {
		left = x1;
		right = x2;
	}
	else {
		left = x2;
		right = x1;
	}
	if (y1 < y2) {
		top = y1;
		bottom = y2;
	}
	else {
		top = y2;
		bottom = y1;
	}
	save = malloc(imagesize(left, top, right, bottom));
	getimage(left, top, right, bottom, save);
	LineBresenham(x1, y1, x2, y2, Event::color);
}

void Event::up_draw_line() {
	if (item_current->scrollbar) {
		Graph* Line = new Graph(2);
		Line->points[0] = Point(x1, y1);
		Line->points[1] = Point(x2, y2);
		Line->setrelation(0, 1, &Relation::line, &Relation::line_savior, Event::color);
		Line->width = abs(x1 - x2);
		Line->height = abs(y1 - y2);

		Line->item = new Item(NULL, "Line", NULL, 0, NULL, NULL);
		Line->item->graph = Line;
		Line->item->mouse_event->hover = &ItemEvent::hover_graph;
		Line->item->mouse_event->hover_inactive = &ItemEvent::hover_inactive_graph;
		Line->item->mouse_event->leftdown = &ItemEvent::leftdown_graph;
		Line->item->mouse_event->leftdrag = &ItemEvent::leftdrag_graph;
		Line->item->mouse_event->leftup = &ItemEvent::leftup_graph;

		Line->item->layer = new Layer(Line->item);
		Line->item->layer->startx = Min(x1, x2);
		Line->item->layer->endx = Max(x1, x2);
		Line->item->layer->starty = Min(y1, y2);
		Line->item->layer->endy = Max(y1, y2);
		Line->showsavior(item_current->scrollbar);
		//LineBresenhamSavior(x1, y1, x2, y2, Event::color, item_current->scrollbar);
		item_current->scrollbar->update_show();
		item_current->layers->add(Line->item->layer);
	}
}

void Event::drag_draw_circle() {
	int a = (x1 + x2) / 2,
		b = (y1 + y2) / 2,
		R = (int)round(distance(x1, y1, a, b));
	left = a - R, top = b - R, right = a + R, bottom = b + R;
	save = malloc(imagesize(left, top, right, bottom));
	getimage(left, top, right, bottom, save);
	CircleMidpoint(a, b, R, Event::color);
}

void Event::up_draw_circle() {
	if (item_current->scrollbar) {
		int a = (x1 + x2) / 2,
			b = (y1 + y2) / 2,
			R = (int)round(distance(x1, y1, a, b));
		Graph* Circle = new Graph(2);
		Circle->points[0] = Point(x1, y1);
		Circle->points[1] = Point(x2, y2);

		Circle->setrelation(0, 1, &Relation::circle135and315, &Relation::circle135and315_savior, Event::color);
		Circle->width = 2 * R;
		Circle->height = 2 * R;

		Circle->item = new Item(NULL, "Circle", NULL, 0, NULL, NULL);
		Circle->item->graph = Circle;
		Circle->item->mouse_event->hover = &ItemEvent::hover_graph;
		Circle->item->mouse_event->hover_inactive = &ItemEvent::hover_inactive_graph;
		Circle->item->mouse_event->leftdown = &ItemEvent::leftdown_graph;
		Circle->item->mouse_event->leftdrag = &ItemEvent::leftdrag_graph;
		Circle->item->mouse_event->leftup = &ItemEvent::leftup_graph;

		Circle->item->layer = new Layer(Circle->item);
		int d = (int)(R * 0.05) + 1;
		Circle->item->layer->startx = a - R - d;
		Circle->item->layer->endx = a + R + d;
		Circle->item->layer->starty = b - R - d;
		Circle->item->layer->endy = b + R + d;
		Circle->showsavior(item_current->scrollbar);
		//CircleMidpointSavior(x1, y1, x2, y2, Event::color, item_current->scrollbar);
		item_current->scrollbar->update_show();
		item_current->layers->add(Circle->item->layer);
	}
}

void Event::drag_draw_square() {
	int dx = abs(x1 - x2), dy = abs(y1 - y2);
	if (x1 < x2) {
		if (dx > dy) {
			x2 = x1 + dy;
		}
		left = x1;
		right = x2;
	}
	else {
		if (dx > dy) {
			x2 = x1 - dy;
		}
		left = x2;
		right = x1;
	}
	if (y1 < y2) {
		if (dy > dx) {
			y2 = y1 + dy;
		}
		top = y1;
		bottom = y2;
	}
	else {
		if (dy > dx) {
			y2 = y1 - dy;
		}
		top = y2;
		bottom = y1;
	}
	save = malloc(imagesize(left, top, right, bottom));
	getimage(left, top, right, bottom, save);
	SquareBresenham(x1, y1, x2, y2, Event::color);
}

void Event::up_draw_square() {
	if (item_current->scrollbar) {
		int dx = abs(x1 - x2), dy = abs(y1 - y2);
		if (dx < dy) {
			if (y2 > y1) {
				y2 = y1 + dx;
			}
			else {
				y2 = y1 - dx;
			}
		}
		else {
			if (x2 > x1) {
				x2 = x1 + dy;
			}
			else {
				x2 = x1 - dy;
			}
		}
		Graph* Square = new Graph(4);
		Square->points[0] = Point(x1, y1);
		Square->points[1] = Point(x2, y2);
		Square->points[2] = Point(x2, y1);
		Square->points[3] = Point(x1, y2);
		Square->setrelation(0, 2, &Relation::line, &Relation::line_savior, Event::color);
		Square->setrelation(1, 2, &Relation::line, &Relation::line_savior, Event::color);
		Square->setrelation(0, 3, &Relation::line, &Relation::line_savior, Event::color);
		Square->setrelation(1, 3, &Relation::line, &Relation::line_savior, Event::color);
		Square->width = abs(x1 - x2);
		Square->height = abs(y1 - y2);

		Square->item = new Item(NULL, "Square", NULL, 0, NULL, NULL);
		Square->item->graph = Square;
		Square->item->mouse_event->hover = &ItemEvent::hover_graph;
		Square->item->mouse_event->hover_inactive = &ItemEvent::hover_inactive_graph;
		Square->item->mouse_event->leftdown = &ItemEvent::leftdown_graph;
		Square->item->mouse_event->leftdrag = &ItemEvent::leftdrag_graph;
		Square->item->mouse_event->leftup = &ItemEvent::leftup_graph;

		Square->item->layer = new Layer(Square->item);
		Square->item->layer->startx = Min(x1, x2);
		Square->item->layer->endx = Max(x1, x2);
		Square->item->layer->starty = Min(y1, y2);
		Square->item->layer->endy = Max(y1, y2);
		Square->showsavior(item_current->scrollbar);
		//SquareBresenhamSavior(x1, y1, x2, y2, Event::color, item_current->scrollbar);
		item_current->scrollbar->update_show();
		item_current->layers->add(Square->item->layer);
	}
}

void Event::drag_select() {
	if (x1 < x2) {
		left = x1;
		right = x2;
	}
	else {
		left = x2;
		right = x1;
	}
	if (y1 < y2) {
		top = y1;
		bottom = y2;
	}
	else {
		top = y2;
		bottom = y1;
	}
	save = malloc(imagesize(left, top, right, bottom));
	getimage(left, top, right, bottom, save);
	setlinestyle(DASHED_LINE, 0, 1);
	rectangle(x1, y1, x2, y2);
}

void Event::up_select() {
	if (x1 != x2 && y1 != y2) {
		if (x1 < x2) {
			left = x1;
			right = x2;
		}
		else {
			left = x2;
			right = x1;
		}
		if (y1 < y2) {
			top = y1;
			bottom = y2;
		}
		else {
			top = y2;
			bottom = y1;
		}
		/*if (item_current->child) {
			delete item_current->child;
			item_current->child = NULL;
		}
		item_current->child = new Menu(left, top, right - left, bottom - top, right - left, bottom - top, false);
		item_current->child->max_active = -2;
		item_current->child->add(new Item(NULL, "Select", NULL, 0, NULL, NULL));
		item_current->child->setbelow();
		old_item_current_leftdown = item_current->child->menu.at(0);
		getviewsettings(&item_current->child->viewport);
		rectangle(x1, y1, x2, y2);
		setlinestyle(SOLID_FILL, 0, 1);*/
		int width = right - left + 1, height = bottom - top + 1;
		unsigned char** arr = new unsigned char*[width];
		for (int i = 0; i < width; i++) {
			arr[i] = new unsigned char[height];
			for (int j = 0; j < height; j++) {
				arr[i][j] = getpixel(left + i, top + j);
			}
		}
		Item* item = item_current;
		item_current->mouse_event->leftdown_new();
		setviewport(Event::item_drawing_area->layer->startx + 1, Event::item_drawing_area->layer->starty + 1, Event::item_drawing_area->layer->endx - Event::item_drawing_area->scrollbar->scrollthick, Event::item_drawing_area->layer->endy - Event::item_drawing_area->scrollbar->scrollthick, 1);
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				putpixel(i, j, arr[i][j]);
			}
			delete[] arr[i];
		}
		delete[] arr;
		setviewport(0, 0, MAXX, MAXY, 1);
	}
}

void Event::down_crop() {
	
}

void Event::up_fillcolor() {
	if (item_current->scrollbar) {
		Fill(x2, y2, Event::color, item_current->scrollbar);
	}
}

void Event::drag_draw_ellipse() {
	if (x2 != x1 || y2 != y1) {
		int a = abs(x2 - x1) / 2, b = abs(y2 - y1) / 2,
			h = (x2 + x1) / 2, k = (y2 + y1) / 2,
			dx = a + 5, dy = b + 5;
		if (a != 0 && b != 0) {
			left = h - dx;
			top = k - dy;
			right = h + dx;
			bottom = k + dy;
			save = malloc(imagesize(left, top, right, bottom));
			getimage(left, top, right, bottom, save);
			EllipseMidpoint(h, k, a, b, Event::color);
		}
	}
}

void Event::up_draw_ellipse() {
	if (x2 != x1 || y2 != y1) {
		int a = abs(x2 - x1) / 2, b = abs(y2 - y1) / 2,
			h = (x2 + x1) / 2, k = (y2 + y1) / 2,
			dx = a + 10, dy = b + 10;
		if (a != 0 && b != 0) {
			EllipseMidpointSavior(h, k, a, b, Event::color, item_current->scrollbar);
			item_current->scrollbar->update_show();
		}
	}
}

void Event::down_draw_bezier() {
	if (save1) {
		putimage(left1, top1, save1, 0);
		free(save1);
		save1 = NULL;
	}
	if (storedpoints.size() == 0) {
		storedpoints.push_back(Point(x1, y1));
	}
}

void Event::drag_draw_bezier() {
	if (storedpoints.size() == 4) {
		storedpoints.clear();
	}
	if (storedpoints.size() == 0) {
		drag_draw_line();
	}
	else {
		Point last = Point(storedpoints.back());
		storedpoints.pop_back();
		storedpoints.push_back(Point(x2, y2));
		storedpoints.push_back(last);
		left = minx(storedpoints);
		right = maxx(storedpoints);
		top = miny(storedpoints);
		bottom = maxy(storedpoints);
		save = malloc(imagesize(left, top, right, bottom));
		getimage(left, top, right, bottom, save);
		Bezier(storedpoints, Event::color);
		storedpoints.pop_back();
		storedpoints.pop_back();
		storedpoints.push_back(last);
	}
}

void Event::up_draw_bezier() {
	if (storedpoints.size() != 0) {
		Point last = Point(storedpoints.back());
		storedpoints.pop_back();
		storedpoints.push_back(Point(x2, y2));
		storedpoints.push_back(last);
		if (storedpoints.size() < 4) {
			left1 = minx(storedpoints);
			right1 = maxx(storedpoints);
			top1 = miny(storedpoints);
			bottom1 = maxy(storedpoints);
			save1 = malloc(imagesize(left1, top1, right1, bottom1));
			getimage(left1, top1, right1, bottom1, save1);
		}
		if (storedpoints.size() == 4) {
			BezierSavior(storedpoints, Event::color, item_current->scrollbar);
			storedpoints.clear();
			item_current->scrollbar->update_show();
		}
		else {
			Bezier(storedpoints, Event::color);
		}
	}
}

void Event::drag_draw_parabol() {
	if (y2 != y1) {
		int h = (x1 + x2) / 2,
			k = y2;
		if (x1 - h != 0) {
			float a = float(y1 - k) / ((x1 - h) * (x1 - h));
			if (x1 < x2) {
				left = x1;
				right = x2;
			}
			else {
				left = x2;
				right = x1;
			}
			if (y1 < y2) {
				top = y1;
				bottom = y2;
			}
			else {
				top = y2;
				bottom = y1;
			}
			int dx = 5, dy = 5;
			left = left - dx;
			bottom = bottom + dy;
			save = malloc(imagesize(left, top, right, bottom));
			getimage(left, top, right, bottom, save);
			Parabol(a, h, k, x1, Event::color);
		}
	}
}

void Event::up_draw_parabol() {
	if (y2 != y1) {
		int h = (x1 + x2) / 2,
			k = y2;
		if (x1 - h != 0) {
			float a = float(y1 - k) / ((x1 - h) * (x1 - h));
			ParabolSavior(a, h, k, x1, Event::color, item_current->scrollbar);
			item_current->scrollbar->update_show();
		}
	}
}

void Event::down_draw_graph() {
	if (graph_sample) {
		graph_sample->changecolor(Event::color);
		drawing_graph = new Graph();
	}
}

void Event::drag_draw_graph() {
	if (x2 - x1 > 0 && y2 - y1 > 0 && graph_sample) {
		//Despite which two points that you are on, the size of the drawing_graph
		//will not exceed the range of the rectangle containing one point of the graph
		//that is double-height and double-width of it. The proof is quite simple, though.
		int width = x2 - x1, height = y2 - y1;
		left = x1 - width;
		top = y1 - height;
		right = x1 + width;
		bottom = y1 + height;
		save = malloc(imagesize(left, top, right, bottom));
		getimage(left, top, right, bottom, save);
		//We cannot use the resize procedure of Graph struct because of floating-point error
		//in Affine matrix will lead to a distorted graph.
		drawing_graph->set(Point(x1, y1), *graph_sample, width, height);
		drawing_graph->show();
	}
}

void Event::up_draw_graph() {
	if (x2 - x1 > 0 && y2 - y1 > 0 && graph_sample) {
		if (item_current->scrollbar) {
			int width = x2 - x1, height = y2 - y1;

			drawing_graph->item = new Item(NULL, "Graph", NULL, 0, NULL, NULL);
			drawing_graph->item->graph = drawing_graph;
			drawing_graph->item->mouse_event->hover = &ItemEvent::hover_graph;
			drawing_graph->item->mouse_event->hover_inactive = &ItemEvent::hover_inactive_graph;
			drawing_graph->item->mouse_event->leftdown = &ItemEvent::leftdown_graph;
			drawing_graph->item->mouse_event->leftdrag = &ItemEvent::leftdrag_graph;
			drawing_graph->item->mouse_event->leftup = &ItemEvent::leftup_graph;

			drawing_graph->set(Point(x1, y1), *graph_sample, width, height);

			Graph old_layer(2);
			old_layer.points[0] = Point(graph_sample->points[0].x, graph_sample->points[0].y);
			old_layer.points[1] = Point(graph_sample->item->layer->endx + graph_sample->points[0].x - graph_sample->item->layer->startx,
										graph_sample->item->layer->endy + graph_sample->points[0].y - graph_sample->item->layer->starty);
			old_layer.setrelation(0, 1, NULL, NULL, 0);
			old_layer.width = graph_sample->width;
			old_layer.height = graph_sample->height;

			Graph new_layer(Point(x1, y1), old_layer, width, height);

			drawing_graph->item->layer = new Layer(drawing_graph->item);
			int dx = (int)((float)(graph_sample->points[0].x - graph_sample->item->layer->startx) / old_layer.width * new_layer.width),
				dy = (int)((float)(graph_sample->points[0].y - graph_sample->item->layer->starty) / old_layer.height * new_layer.height);
			drawing_graph->item->layer->startx = new_layer.points[0].x - dx;
			drawing_graph->item->layer->starty = new_layer.points[0].y - dy;
			drawing_graph->item->layer->endx = new_layer.points[1].x - dx;
			drawing_graph->item->layer->endy = new_layer.points[1].y - dy;

			drawing_graph->showsavior(item_current->scrollbar);

			item_current->scrollbar->update_show();
			item_current->layers->add(drawing_graph->item->layer);
		}
	}
}

void Event::down_move_graph() {
	if (graph_sample) {
		drawing_graph = new Graph();
		drawing_graph->item = graph_sample->item;

		left = drawing_graph->item->layer->startx;
		right = drawing_graph->item->layer->endx;
		top = drawing_graph->item->layer->starty;
		bottom = drawing_graph->item->layer->endy;
		//Event::item_drawing_area->layers->upabove may be a souce of problems.
		Layer* layer = Event::item_drawing_area->layers->upabove;
		while (layer && layer != graph_sample->item->layer) {
			putimage(layer->startx, layer->starty, layer->item->graph->below, 0);
			layer = layer->below;
		}
		putimage(left, top, graph_sample->below, 0);
		if (layer) {
			layer = layer->above;
		}
		Event::item_drawing_area->layers->remove(graph_sample->item->layer);
		Event::item_drawing_area->layers->add(graph_sample->item->layer);
		while (layer && layer != graph_sample->item->layer) {
			layer->item->graph->showsavior(Event::item_drawing_area->scrollbar);
			layer = layer->above;
		}
		graph_sample->showsavior(Event::item_drawing_area->scrollbar);
		save = graph_sample->below;
	}
}

void Event::drag_move_graph() {
	if (graph_sample) {
		int dx = x2 - x1, dy = y2 - y1;
		drawing_graph->set(Point(graph_sample->points[0].x + dx, graph_sample->points[0].y + dy), *graph_sample, graph_sample->width, graph_sample->height);
		left = drawing_graph->item->layer->startx + dx;
		right = drawing_graph->item->layer->endx + dx;
		top = drawing_graph->item->layer->starty + dy;
		bottom = drawing_graph->item->layer->endy + dy;
		save = malloc(imagesize(left, top, right, bottom));
		getimage(left, top, right, bottom, save);
		drawing_graph->show();
	}
}

void Event::up_move_graph() {
	if (graph_sample) {
		int dx = x2 - x1, dy = y2 - y1;
		drawing_graph->set(Point(graph_sample->points[0].x + dx, graph_sample->points[0].y + dy), *graph_sample, graph_sample->width, graph_sample->height);
		drawing_graph->item->layer->startx = drawing_graph->item->layer->startx + dx;
		drawing_graph->item->layer->endx = drawing_graph->item->layer->endx + dx;
		drawing_graph->item->layer->starty = drawing_graph->item->layer->starty + dy;
		drawing_graph->item->layer->endy = drawing_graph->item->layer->endy + dy;
		drawing_graph->showsavior(Event::item_drawing_area->scrollbar);
		delete graph_sample;
		graph_sample = NULL;
		drawing_graph->item->graph = drawing_graph;
	}
}

void Event::scroll_down() {
	Scrollbar* scrollbar = item_current->scrollbar_parent;
	int inc = Min(each_scroll, scrollbar->v_bottom->layer->starty - scrollbar->v_scroll->layer->endy);
	if (inc > 0) {
		scrollbar->starty = scrollbar->starty + inc;
		scrollbar->update_show();
		Item* item = scrollbar->parent;
		left = item->layer->startx + 1; top = item->layer->starty + 1 + inc; right = scrollbar->h_right->layer->endx - 1; bottom = scrollbar->v_bottom->layer->endy - 1;
		save = malloc(imagesize(left, top, right, bottom));
		getimage(left, top, right, bottom, save);
		setviewport(left, top - inc, right, bottom, 0);
		for (int i = 0; i <= right - left; i++) {
			for (int j = bottom - top; j <= bottom - top + inc; j++) {
				putpixel(i, j, scrollbar->wholeview->get(i, j));
			}
		}
		setviewport(0, 0, MAXX, MAXY, 1);
		top = top - inc;
		putimage(left, top, save, 0);
		free(save);
		save = NULL;
	}
}

void Event::scroll_up() {
	Scrollbar* scrollbar = item_current->scrollbar_parent;
	int inc = Max(-each_scroll, scrollbar->v_top->layer->endy - scrollbar->v_scroll->layer->starty);
	if (inc < 0) {
		scrollbar->starty = scrollbar->starty + inc;
		scrollbar->update_show();
		Item* item = scrollbar->parent;
		left = item->layer->startx + 1; top = item->layer->starty + 1; right = scrollbar->h_right->layer->endx - 1; bottom = scrollbar->v_bottom->layer->endy - 1 + inc;
		save = malloc(imagesize(left, top, right, bottom));
		getimage(left, top, right, bottom, save);
		setviewport(left, top, right, bottom - inc, 0);
		for (int i = 0; i <= right - left; i++) {
			for (int j = 0; j <= - inc; j++) {
				putpixel(i, j, scrollbar->wholeview->get(i, j));
			}
		}
		setviewport(0, 0, MAXX, MAXY, 1);
		top = top - inc;
		putimage(left, top, save, 0);
		free(save);
		save = NULL;
	}
}

void Event::scroll_up_down() {
	each_scroll = 2;
	if (y2 < y1) {
		scroll_up();
	}
	if(y2 > y1) {
		scroll_down();
	}
	each_scroll = 20;
}

void Event::scroll_right() {
	Scrollbar* scrollbar = item_current->scrollbar_parent;
	int inc = Min(each_scroll, scrollbar->h_right->layer->startx - scrollbar->h_scroll->layer->endx);
	if (inc > 0) {
		scrollbar->startx = scrollbar->startx + inc;
		scrollbar->update_show();
		Item* item = scrollbar->parent;
		left = item->layer->startx + 1 + inc; top = item->layer->starty + 1; right = scrollbar->h_right->layer->endx - 1; bottom = scrollbar->v_bottom->layer->endy - 1;
		save = malloc(imagesize(left, top, right, bottom));
		getimage(left, top, right, bottom, save);
		setviewport(left - inc, top, right, bottom, 0);
		for (int i = right - left; i <= right - left + inc; i++) {
			for (int j = 0; j <= bottom - top; j++) {
				putpixel(i, j, scrollbar->wholeview->get(i, j));
			}
		}
		setviewport(0, 0, MAXX, MAXY, 1);
		left = left - inc;
		putimage(left, top, save, 0);
		free(save);
		save = NULL;
	}
}

void Event::scroll_left() {
	Scrollbar* scrollbar = item_current->scrollbar_parent;
	int inc = Max(-each_scroll, scrollbar->h_left->layer->endx - scrollbar->h_scroll->layer->startx);
	if (inc < 0) {
		scrollbar->startx = scrollbar->startx + inc;
		scrollbar->update_show();
		Item* item = scrollbar->parent;
		left = item->layer->startx + 1; top = item->layer->starty + 1; right = scrollbar->h_right->layer->endx - 1 + inc; bottom = scrollbar->v_bottom->layer->endy - 1;
		save = malloc(imagesize(left, top, right, bottom));
		getimage(left, top, right, bottom, save);
		setviewport(left, top, right - inc, bottom, 0);
		for (int i = 0; i <= - inc; i++) {
			for (int j = 0; j <= bottom - top; j++) {
				putpixel(i, j, scrollbar->wholeview->get(i, j));
			}
		}
		setviewport(0, 0, MAXX, MAXY, 1);
		left = left - inc;
		putimage(left, top, save, 0);
		free(save);
		save = NULL;
	}
}

void Event::scroll_left_right() {
	each_scroll = 2;
	if(x2 < x1) {
		scroll_left();
	}
	if(x2 > x1) {
		scroll_right();
	}
	each_scroll = 20;
}