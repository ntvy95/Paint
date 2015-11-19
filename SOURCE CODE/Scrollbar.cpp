#include "Scrollbar.h"
#include "Procedure.h"
#include "Global.h"
#include "Event.h"
#include "graphics.h"
#pragma comment(lib, "graphics.lib")

Scrollbar::Scrollbar(Item* p) {
	parent = p;
	style = new Style(this);
	style->normal = &Style::normal_rectangle_border;
	scrollthick = (int)(Min(MAXX, MAXY) * 0.03);
	startx = starty = 0;
	//This is where the generalization may be lost.
	wholeview = new PixelSavior(this);
	HorizontalScroll(this);
	VerticalScroll(this);
}

void Scrollbar::update_show() {
	(style->*(style->normal))();
	update_h_scroll_width();
	update_h_scroll_position();
	update_v_scroll_height();
	update_v_scroll_position();
	(h_left->style->*(h_left->style->normal))();
	(h_right->style->*(h_right->style->normal))();
	(h_scroll->style->*(h_scroll->style->normal))();
	(v_top->style->*(v_top->style->normal))();
	(v_bottom->style->*(v_bottom->style->normal))();
	(v_scroll->style->*(v_scroll->style->normal))();
}

void Scrollbar::show() {
	(style->*(style->normal))();
	Event::layers.add(h_left->layer);
	Event::layers.add(h_right->layer);
	Event::layers.add(h_scroll->layer);
	Event::layers.add(v_top->layer);
	Event::layers.add(v_bottom->layer);
	Event::layers.add(v_scroll->layer);
	(h_left->style->*(h_left->style->normal))();
	(h_right->style->*(h_right->style->normal))();
	(h_scroll->style->*(h_scroll->style->normal))();
	(v_top->style->*(v_top->style->normal))();
	(v_bottom->style->*(v_bottom->style->normal))();
	(v_scroll->style->*(v_scroll->style->normal))();
}

void Scrollbar::update_h_scroll_width() {
	int h_scroll_max = parent->parent->itemw - scrollthick * 3, //max width of scroll
		wholeview_width = wholeview->getwidth(),
		h_scroll_width = (int)(((float)(parent->parent->itemw) / wholeview_width) * h_scroll_max); //true width of scroll
	h_scroll->layer->endx = h_scroll->layer->startx + h_scroll_width;
}

void Scrollbar::update_h_scroll_position() {
	int h_scroll_max = parent->parent->itemw - scrollthick * 3, //max width of scroll
		wholeview_width = wholeview->getwidth(); 
	h_scroll->layer->startx = h_left->layer->endx + (int)(((float)(startx) / wholeview_width) * h_scroll_max);
}

void Scrollbar::update_v_scroll_height() {
	int v_scroll_max = parent->parent->itemh - scrollthick * 3, //max height of scroll
		wholeview_height = wholeview->getheight(),
		v_scroll_height = (int)(((float)(parent->parent->itemh) / wholeview_height) * v_scroll_max);
	v_scroll->layer->endy = v_scroll->layer->starty + v_scroll_height;
}

void Scrollbar::update_v_scroll_position() {
	int v_scroll_max = parent->parent->itemh - scrollthick * 3, //max height of scroll
		wholeview_height = wholeview->getheight(); //true height of scroll
	v_scroll->layer->starty = v_top->layer->endy + (int)(((float)(starty) / wholeview_height) * v_scroll_max);
}

void HorizontalScroll(Scrollbar* scrollbar) {
	Item *h_left = new Item(NULL, "Horizontal Left", NULL, 0, &Style::normal_rectangle_border, &Style::active_rectangle_border),
		*h_right = new Item(NULL, "Horizontal Right", NULL, 0, &Style::normal_rectangle_border, &Style::active_rectangle_border),
		*h_scroll = new Item(NULL, "Horizontal Scroll", NULL, 0, &Style::normal_rectangle_border, &Style::active_rectangle_border);

	scrollbar->h_left = h_left;
	h_left->scrollbar_parent = scrollbar;
	h_left->layer = new Layer(h_left);
	/*h_left->layer->startx = 0;
	h_left->layer->starty = scrollbar->parent->parent->itemh - 1 - scrollbar->scrollthick;*/
	h_left->layer->startx = scrollbar->parent->layer->startx;
	h_left->layer->starty = scrollbar->parent->layer->endy - scrollbar->scrollthick;
	h_left->layer->endx = h_left->layer->startx + scrollbar->scrollthick;
	h_left->layer->endy = h_left->layer->starty + scrollbar->scrollthick;
	h_left->mouse_event->hover = &ItemEvent::hover_menu;
	h_left->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;
	h_left->mouse_event->leftdown = &ItemEvent::scroll_left;

	scrollbar->h_right = h_right;
	h_right->scrollbar_parent = scrollbar;
	h_right->layer = new Layer(h_right);
	/*h_right->layer->endx = scrollbar->parent->parent->itemw - 1 - scrollbar->scrollthick;
	h_right->layer->endy = scrollbar->parent->parent->itemh - 1;*/
	h_right->layer->endx = scrollbar->parent->layer->endx - scrollbar->scrollthick;
	h_right->layer->endy = scrollbar->parent->layer->endy;
	h_right->layer->startx = h_right->layer->endx - scrollbar->scrollthick;
	h_right->layer->starty = h_right->layer->endy - scrollbar->scrollthick;
	h_right->mouse_event->hover = &ItemEvent::hover_menu;
	h_right->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;
	h_right->mouse_event->leftdown = &ItemEvent::scroll_right;

	scrollbar->h_scroll = h_scroll;
	h_scroll->scrollbar_parent = scrollbar;
	h_scroll->layer = new Layer(h_scroll);
	scrollbar->update_h_scroll_position();
	scrollbar->update_h_scroll_width();
	h_scroll->layer->starty = h_left->layer->starty;
	h_scroll->layer->endy = h_scroll->layer->starty + scrollbar->scrollthick;
	h_scroll->mouse_event->hover = &ItemEvent::hover_menu;
	h_scroll->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;
	h_scroll->mouse_event->leftdrag = &ItemEvent::scroll_left_right;
}

void VerticalScroll(Scrollbar* scrollbar) {
	Item *v_top = new Item(NULL, "Vertical Top", NULL, 0, &Style::normal_rectangle_border, &Style::active_rectangle_border),
		*v_bottom = new Item(NULL, "Vertical Bottom", NULL, 0, &Style::normal_rectangle_border, &Style::active_rectangle_border),
		*v_scroll = new Item(NULL, "Vertical Scroll", NULL, 0, &Style::normal_rectangle_border, &Style::active_rectangle_border);

	scrollbar->v_top = v_top;
	v_top->scrollbar_parent = scrollbar;
	v_top->layer = new Layer(v_top);
	/*v_top->layer->startx = scrollbar->parent->parent->itemw - 1 - scrollbar->scrollthick;
	v_top->layer->starty = 0;*/
	v_top->layer->startx = scrollbar->parent->layer->endx - scrollbar->scrollthick;
	v_top->layer->starty = scrollbar->parent->layer->starty;
	v_top->layer->endx = v_top->layer->startx + scrollbar->scrollthick;
	v_top->layer->endy = v_top->layer->starty + scrollbar->scrollthick;
	v_top->mouse_event->hover = &ItemEvent::hover_menu;
	v_top->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;
	v_top->mouse_event->leftdown = &ItemEvent::scroll_up;

	scrollbar->v_bottom = v_bottom;
	v_bottom->scrollbar_parent = scrollbar;
	v_bottom->layer = new Layer(v_bottom);
	/*v_bottom->layer->endx = scrollbar->parent->parent->itemw - 1;
	v_bottom->layer->endy = scrollbar->parent->parent->itemh - 1 - scrollbar->scrollthick;*/
	v_bottom->layer->endx = scrollbar->parent->layer->endx;
	v_bottom->layer->endy = scrollbar->parent->layer->endy - scrollbar->scrollthick;
	v_bottom->layer->startx = v_bottom->layer->endx - scrollbar->scrollthick;
	v_bottom->layer->starty = v_bottom->layer->endy - scrollbar->scrollthick;
	v_bottom->mouse_event->hover = &ItemEvent::hover_menu;
	v_bottom->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;
	v_bottom->mouse_event->leftdown = &ItemEvent::scroll_down;

	scrollbar->v_scroll = v_scroll;
	v_scroll->scrollbar_parent = scrollbar;
	v_scroll->layer = new Layer(v_scroll);
	scrollbar->update_v_scroll_position();
	scrollbar->update_v_scroll_height();
	v_scroll->layer->startx = v_top->layer->startx;
	v_scroll->layer->endx = v_scroll->layer->startx + scrollbar->scrollthick;
	v_scroll->mouse_event->hover = &ItemEvent::hover_menu;
	v_scroll->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;
	v_scroll->mouse_event->leftdrag = &ItemEvent::scroll_up_down;
}

Scrollbar::~Scrollbar() {
	Event::layers.remove(h_left->layer);
	Event::layers.remove(h_right->layer);
	Event::layers.remove(h_scroll->layer);
	Event::layers.remove(v_top->layer);
	Event::layers.remove(v_bottom->layer);
	Event::layers.remove(v_scroll->layer);
	delete wholeview;
	wholeview = NULL;
	delete h_left;
	h_left = NULL;
	delete h_right;
	h_right = NULL;
	delete h_scroll;
	h_scroll = NULL;
	delete v_top;
	v_top = NULL;
	delete v_bottom;
	v_bottom = NULL;
	delete v_scroll;
	v_scroll = NULL;
}