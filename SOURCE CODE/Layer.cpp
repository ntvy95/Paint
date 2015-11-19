#include "Layer.h"
#include "Event.h"

Layer::Layer(Menu* m) {
	init_layer(m);
}

Layer::Layer(Item* i) {
	init_layer(NULL, i);
}

Layer::Layer(Graph* g) {
	init_layer(NULL, NULL, g);
}

void Layer::init_layer(Menu* m, Item* i, Graph* g) {
	startx = 0;
	starty = 0;
	endx = 0;
	endy = 0;
	menu = m;
	item = i;
	above = NULL;
	below = NULL;
}

Layer::~Layer() {
	
}

bool Layer::contain(int x, int y) {
	return (x >= startx && x <= endx && y >= starty && y <= endy);
}