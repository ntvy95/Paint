#include "KeyboardInput.h"

void KeyboardInput_INPUT_CIRCLE() {
	if (Event::is_setviewport == true) {
		setviewport(0, 0, MAXX, MAXY, 1);
		Event::is_setviewport = false;
	}
	bool stop = false;
	Style::POS = 0;
	Style::InputText[0] = Style::InputText[85] = Style::InputText[170] = NULL;
	Style::normal_KEY_Circle();
	while (true) {
		if (Event::draw != Event::CIRCLE) {
			stop = true;
			Style::hide_KEY();
			break;
		}
		if (kbhit()) {
			char c = getch();
			switch (c) {
				case 8: //backspace
					if (Style::POS > 0)
					{
						Style::POS = Style::POS - 1;
						Style::InputText[Style::POS] = NULL;
					}
					break;
				case 9: //tab
				case 32: //spacebar
				case 13: //return
					if (Style::POS < 85) {
						Style::POS = 85;
					}
					else if (Style::POS < 170) {
						Style::POS = 170;
					}
					else {
						stop = true;
						Style::hide_KEY();
					}
					break;
				case 27: //Escape
					if (Style::POS < 85) {
						Style::InputText[0] = NULL;
					}
					else if (Style::POS < 170) {
						Style::InputText[85] = NULL;
					}
					else {
						Style::InputText[170] = NULL;
					}
					break;
				default:
					if (Style::POS < Style::nInputText - 1 && c >= '0' && c <= '9')
					{
						Style::InputText[Style::POS] = c;
						Style::POS = Style::POS + 1;
						Style::InputText[Style::POS] = NULL;
					} break;
			}
			if (stop == false) {
				if (Event::is_setviewport == true) {
					setviewport(0, 0, MAXX, MAXY, 1);
					Event::is_setviewport = false;
				}
				Style::normal_KEY_Circle();
			}
			else {
				break;
			}
		}
	}
	if (Event::draw == Event::CIRCLE) {
		if (Event::is_setviewport == false) {
			setviewport(Event::item_drawing_area->layer->startx + 1, Event::item_drawing_area->layer->starty + 1, Event::item_drawing_area->layer->endx - Event::item_drawing_area->scrollbar->scrollthick, Event::item_drawing_area->layer->endy - Event::item_drawing_area->scrollbar->scrollthick, 1);
			Event::is_setviewport = true;
		}
		int a = atoi(Style::InputText), b = atoi(Style::InputText + 85), r = atoi(Style::InputText + 170);
		CircleMidpointSavior(a, b, r, Event::color, Event::item_drawing_area->scrollbar);
		Event::item_drawing_area->scrollbar->update_show();
		if (Event::is_setviewport == true) {
			setviewport(0, 0, MAXX, MAXY, 1);
			Event::is_setviewport = false;
		}
	}
	Event::KeyboardInput = Event::INPUT_NONE;
}

void KeyboardInput_INPUT_SQUARE() {
	if (Event::is_setviewport == true) {
		setviewport(0, 0, MAXX, MAXY, 1);
		Event::is_setviewport = false;
	}
	bool stop = false;
	Style::POS = 0;
	Style::InputText[0] = Style::InputText[85] = Style::InputText[170] = NULL;
	Style::normal_KEY_Square();
	while (true) {
		if (Event::draw != Event::SQUARE) {
			stop = true;
			Style::hide_KEY();
			break;
		}
		if (kbhit()) {
			char c = getch();
			switch (c) {
				case 8: //backspace
					if (Style::POS > 0)
					{
						Style::POS = Style::POS - 1;
						Style::InputText[Style::POS] = NULL;
					}
					break;
				case 9: //tab
				case 32: //spacebar
				case 13: //return
					if (Style::POS < 85) {
						Style::POS = 85;
					}
					else if (Style::POS < 170) {
						Style::POS = 170;
					}
					else {
						stop = true;
						Style::hide_KEY();
					}
					break;
				case 27: //Escape
					if (Style::POS < 85) {
						Style::InputText[0] = NULL;
					}
					else if (Style::POS < 170) {
						Style::InputText[85] = NULL;
					}
					else {
						Style::InputText[170] = NULL;
					}
					break;
				default:
					if (Style::POS < Style::nInputText - 1 && c >= '0' && c <= '9')
					{
						Style::InputText[Style::POS] = c;
						Style::POS = Style::POS + 1;
						Style::InputText[Style::POS] = NULL;
					} break;
			}
			if (stop == false) {
				if (Event::is_setviewport == true) {
					setviewport(0, 0, MAXX, MAXY, 1);
					Event::is_setviewport = false;
				}
				Style::normal_KEY_Square();
			}
			else {
				break;
			}
		}
	}

	if (Event::draw == Event::SQUARE) {
		if (Event::is_setviewport == false) {
			setviewport(Event::item_drawing_area->layer->startx + 1, Event::item_drawing_area->layer->starty + 1, Event::item_drawing_area->layer->endx - Event::item_drawing_area->scrollbar->scrollthick, Event::item_drawing_area->layer->endy - Event::item_drawing_area->scrollbar->scrollthick, 1);
			Event::is_setviewport = true;
		}
		int x = atoi(Style::InputText), y = atoi(Style::InputText + 85), a = atoi(Style::InputText + 170);
		SquareBresenhamSavior(x, y, a, Event::color, Event::item_drawing_area->scrollbar);
		Event::item_drawing_area->scrollbar->update_show();
		if (Event::is_setviewport == true) {
			setviewport(0, 0, MAXX, MAXY, 1);
			Event::is_setviewport = false;
		}
	}
	Event::KeyboardInput = Event::INPUT_NONE;
}

void KeyboardInput_INPUT_STRETCH() {
	if (Event::is_setviewport == true) {
		setviewport(0, 0, MAXX, MAXY, 1);
		Event::is_setviewport = false;
	}
	bool stop = false;
	Style::POS = 0;
	Style::InputText[0] = NULL; Style::InputText[85] = NULL;
	Style::normal_KEY_Stretch();
	while (true) {
		if (Event::draw != Event::STRETCH) {
			stop = true;
			Style::hide_KEY();
			break;
		}
		if (kbhit()) {
			char c = getch();
			switch (c) {
			case 8: //backspace
				if (Style::POS > 0)
				{
					Style::POS = Style::POS - 1;
					Style::InputText[Style::POS] = NULL;
				}
				break;
			case 9: //tab
			case 32: //spacebar
			case 13: //return
				if (Style::POS < 85) {
					Style::POS = 85;
				}
				else {
					stop = true;
					Style::hide_KEY();
				}
				break;
			case 27: //Escape
				if (Style::POS < 85) {
					Style::InputText[0] = NULL;
				}
				else {
					Style::InputText[85] = NULL;
				}
				break;
			default:
				if (Style::POS < Style::nInputText - 1 && c >= '0' && c <= '9' || c == '.' || c == '-')
				{
					Style::InputText[Style::POS] = c;
					Style::POS = Style::POS + 1;
					Style::InputText[Style::POS] = NULL;
				} break;
			}
			if (stop == false) {
				if (Event::is_setviewport == true) {
					setviewport(0, 0, MAXX, MAXY, 1);
					Event::is_setviewport = false;
				}
				Style::normal_KEY_Stretch();
			}
			else {
				break;
			}
		}
	}

	if (Event::draw == Event::STRETCH) {

		if (Event::is_setviewport == false) {
			setviewport(Event::item_drawing_area->layer->startx + 1, Event::item_drawing_area->layer->starty + 1, Event::item_drawing_area->layer->endx - Event::item_drawing_area->scrollbar->scrollthick, Event::item_drawing_area->layer->endy - Event::item_drawing_area->scrollbar->scrollthick, 1);
			Event::is_setviewport = true;
		}

		float Rx = (float)(atof(Style::InputText)), Ry = (float)(atof(Style::InputText + 85));

		putimage(Event::graph_sample->item->layer->startx, Event::graph_sample->item->layer->starty, Event::graph_sample->below, 0);

		int width = (int)(Rx * Event::graph_sample->width), height = (int)(Ry * Event::graph_sample->height);

		Graph* drawing_graph = new Graph;
		drawing_graph->item = Event::graph_sample->item;
		drawing_graph->item->graph = drawing_graph;

		drawing_graph->set(Point(Event::graph_sample->points[0].x, Event::graph_sample->points[0].y), *Event::graph_sample, Event::graph_sample->width, Event::graph_sample->height);
		drawing_graph->resize(width, height);

		drawing_graph->showsavior(Event::item_drawing_area->scrollbar);

		Event::item_drawing_area->scrollbar->update_show();

		delete Event::graph_sample;
		Event::graph_sample = NULL;

		if (Event::is_setviewport == true) {
			setviewport(0, 0, MAXX, MAXY, 1);
			Event::is_setviewport = false;
		}
	}
	Event::KeyboardInput = Event::INPUT_NONE;
}

void KeyboardInput_INPUT_ROTATE() {
	if (Event::is_setviewport == true) {
		setviewport(0, 0, MAXX, MAXY, 1);
		Event::is_setviewport = false;
	}
	bool stop = false;
	Style::POS = 0;
	Style::InputText[0] = NULL; Style::InputText[85] = NULL;
	Style::normal_KEY_Rotation();
	while (true) {
		if (Event::draw != Event::ROTATE) {
			stop = true;
			Style::hide_KEY();
			break;
		}
		if (kbhit()) {
			char c = getch();
			switch (c) {
			case 8: //backspace
				if (Style::POS > 0)
				{
					Style::POS = Style::POS - 1;
					Style::InputText[Style::POS] = NULL;
				}
				break;
			case 9: //tab
			case 32: //spacebar
			case 13: //return
				stop = true;
				Style::hide_KEY();
				break;
			case 27: //Escape
				Style::InputText[0] = NULL;
				break;
			default:
				if (Style::POS < Style::nInputText - 1 && c >= '0' && c <= '9')
				{
					Style::InputText[Style::POS] = c;
					Style::POS = Style::POS + 1;
					Style::InputText[Style::POS] = NULL;
				} break;
			}
			if (stop == false) {
				if (Event::is_setviewport == true) {
					setviewport(0, 0, MAXX, MAXY, 1);
					Event::is_setviewport = false;
				}
				Style::normal_KEY_Rotation();
			}
			else {
				break;
			}
		}
	}

	if (Event::draw == Event::ROTATE) {

		if (Event::is_setviewport == false) {
			setviewport(Event::item_drawing_area->layer->startx + 1, Event::item_drawing_area->layer->starty + 1, Event::item_drawing_area->layer->endx - Event::item_drawing_area->scrollbar->scrollthick, Event::item_drawing_area->layer->endy - Event::item_drawing_area->scrollbar->scrollthick, 1);
			Event::is_setviewport = true;
		}

		int degree = atoi(Style::InputText);

		putimage(Event::graph_sample->item->layer->startx, Event::graph_sample->item->layer->starty, Event::graph_sample->below, 0);

		Graph* drawing_graph = new Graph;
		drawing_graph->item = Event::graph_sample->item;
		drawing_graph->item->graph = drawing_graph;

		drawing_graph->set(Point(Event::graph_sample->points[0].x, Event::graph_sample->points[0].y), *Event::graph_sample, Event::graph_sample->width, Event::graph_sample->height);
		drawing_graph->rotate(degree);

		drawing_graph->showsavior(Event::item_drawing_area->scrollbar);

		Event::item_drawing_area->scrollbar->update_show();

		delete Event::graph_sample;
		Event::graph_sample = NULL;

		if (Event::is_setviewport == true) {
			setviewport(0, 0, MAXX, MAXY, 1);
			Event::is_setviewport = false;
		}
	}
	Event::KeyboardInput = Event::INPUT_NONE;
}

void KeyboardInput_INPUT_SHEAR() {
	if (Event::is_setviewport == true) {
		setviewport(0, 0, MAXX, MAXY, 1);
		Event::is_setviewport = false;
	}
	bool stop = false;
	Style::POS = 0;
	Style::InputText[0] = NULL; Style::InputText[85] = NULL;
	Style::normal_KEY_Shear();
	while (true) {
		if (Event::draw != Event::SHEAR) {
			stop = true;
			Style::hide_KEY();
			break;
		}
		if (kbhit()) {
			char c = getch();
			switch (c) {
			case 8: //backspace
				if (Style::POS > 0)
				{
					Style::POS = Style::POS - 1;
					Style::InputText[Style::POS] = NULL;
				}
				break;
			case 9: //tab
			case 32: //spacebar
			case 13: //return
				if (Style::POS < 85) {
					Style::POS = 85;
				}
				else {
					stop = true;
					Style::hide_KEY();
				}
				break;
			case 27: //Escape
				if (Style::POS < 85) {
					Style::InputText[0] = NULL;
				}
				else {
					Style::InputText[85] = NULL;
				}
				break;
			default:
				if (Style::POS < Style::nInputText - 1 && c >= '0' && c <= '9' || c == '.' || c == '-')
				{
					Style::InputText[Style::POS] = c;
					Style::POS = Style::POS + 1;
					Style::InputText[Style::POS] = NULL;
				} break;
			}
			if (stop == false) {
				if (Event::is_setviewport == true) {
					setviewport(0, 0, MAXX, MAXY, 1);
					Event::is_setviewport = false;
				}
				Style::normal_KEY_Shear();
			}
			else {
				break;
			}
		}
	}

	if (Event::draw == Event::SHEAR) {

		if (Event::is_setviewport == false) {
			setviewport(Event::item_drawing_area->layer->startx + 1, Event::item_drawing_area->layer->starty + 1, Event::item_drawing_area->layer->endx - Event::item_drawing_area->scrollbar->scrollthick, Event::item_drawing_area->layer->endy - Event::item_drawing_area->scrollbar->scrollthick, 1);
			Event::is_setviewport = true;
		}

		float g = (float)(atof(Style::InputText)), h = (float)(atof(Style::InputText + 85));

		putimage(Event::graph_sample->item->layer->startx, Event::graph_sample->item->layer->starty, Event::graph_sample->below, 0);

		Graph* drawing_graph = new Graph;
		drawing_graph->item = Event::graph_sample->item;
		drawing_graph->item->graph = drawing_graph;

		drawing_graph->set(Point(Event::graph_sample->points[0].x, Event::graph_sample->points[0].y), *Event::graph_sample, Event::graph_sample->width, Event::graph_sample->height);
		drawing_graph->shear((int)(g), (int)(h));

		drawing_graph->showsavior(Event::item_drawing_area->scrollbar);

		Event::item_drawing_area->scrollbar->update_show();

		delete Event::graph_sample;
		Event::graph_sample = NULL;

		if (Event::is_setviewport == true) {
			setviewport(0, 0, MAXX, MAXY, 1);
			Event::is_setviewport = false;
		}
	}
	Event::KeyboardInput = Event::INPUT_NONE;
}