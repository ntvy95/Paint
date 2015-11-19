/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* STRUCT: Graph.
* DESCRIPTION: As the struct name may suggest: The graph is built on its points
and the relations between its points. There are also height and width attribute,
which may not be the exact parameter but large enough to cover the whole graph.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma once
#include "Relation.h"
#include "Point.h"
#include "Scrollbar.h"
#include "PixelSavior.h"

struct Item;
struct Layer;
struct Relation;
struct Point;
struct PixelSavior;
typedef struct Graph {
	int n;
	Item* item;
	Point* points;
	Relation** relations;
	int height;
	int width;
	vector<vector<bool>> graph_image;
	void* below;
	/*PROCEDURE*/
	Graph();
	Graph(int N);
	Graph(Point start, Graph& G, int w, int h);
	void set(Point start, Graph& G, int w, int h);
	void setrelation(int i, int j, void(Relation::*relate)(), void(Relation::*relate_savior)(Scrollbar* scrollbar), int color);
	void changecolor(int c);
	void resize(int w, int h);
	void rotate(int degree);
	void shear(int g, int h);
	void show();
	void showsavior(Scrollbar* scrollbar);
	void delGraph();
	void initGraph(int N);
	void exact_layer();
	void setbelow();
	void showlayer();
	int getminx();
	int getmaxx();
	int getminy();
	int getmaxy();
	~Graph();
	//These two below procedure is useless so it should live inside comment.
	//int getheight();
	//int getwidth();
} Graph;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*Those below are graph database. We only have character database now and I hope
that there will be no more. Thanks.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
Graph* characterA();
Graph* characterB();
Graph* characterC();