/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* STRUCT: Layers.
* DESCRIPTION: Layer struct alone is not enough, just like in List data structure:
Node struct without List truct to manage will lose its meaning.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma once
#include "Layer.h"

struct Layer;
typedef struct Layers {
	Layer* upabove;
	bool is_setviewport;
	/*PROCEDURE*/
	Layers();
	~Layers();
	void add(Layer* L);
	void remove(Layer* L);
} Layers;