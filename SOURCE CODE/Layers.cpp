#include "Layers.h"

Layers::Layers() {
	upabove = NULL;
	is_setviewport = false;
}

Layers::~Layers() {
	upabove = NULL;
	is_setviewport = false;
}

void Layers::add(Layer* L) {
	if (upabove) {
		upabove->above = L;
	}
	L->below = upabove;
	upabove = L;
}

void Layers::remove(Layer* L) {
	Layer *above = L->above,
		  *below = L->below;
	if (above) {
		above->below = below;
	}
	if (below) {
		below->above = above;
	}
	if (L == upabove) {
		upabove = below;
	}
	L->above = L->below = NULL;
}