#include "Graph.h"
#include "Global.h"
#include "Procedure.h"
#include "Affine.h"
#include "graphics.h"
#pragma comment(lib, "graphics.lib")

Graph::Graph() {
	item = NULL;
	below = NULL;
	initGraph(0);
}

Graph::Graph(int N) {
	item = NULL;
	below = NULL;
	initGraph(N);
}

Graph::Graph(Point start, Graph& G, int w, int h) {
	item = NULL;
	below = NULL;
	initGraph(0);
	set(start, G, w, h);
}

void Graph::initGraph(int N) {
	if (below) {
		free(below);
		below = NULL;
	}
	n = N;
	height = 0;
	width = 0;
	if (n == 0) {
		points = NULL;
		relations = NULL;
	}
	else {
		points = new Point[n];
		relations = new Relation*[n];
		for (int i = 0; i < n; i++) {
			relations[i] = new Relation[i + 1]();
		}
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: Graph::set.
* INPUT: Point start, Graph& G, int w, int h.
* OUTPUT: void.
* DESCRIPTION: We set up the current graph at the Point with width w, height h
and based on the shape of Graph G.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void Graph::set(Point start, Graph& G, int w, int h) {
	delGraph();
	initGraph(G.n);
	Affine transformation;
	points[0] = start;

	float size = 1;

	if (h == 0 || w == 0) {
		size = Max((float)w / G.width, (float)h / G.height);
	}
	else {
		size = Min((float)w / G.width, (float)h / G.height);
	}
	transformation.resize(G.points[0], size, size);
	transformation.translation(G.points[0], points[0]);
	for (int i = 1; i < n; i++) {
		points[i] = transformation.transform(G.points[i]);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			setrelation(i, j, G.relations[i][j].relate, G.relations[i][j].relate_savior, G.relations[i][j].color);
		}
	}
	width = size * G.width * 1.003;
	height = size * G.height * 1.003;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: Graph::changecolor.
* INPUT: int c.
* OUTPUT: void.
* DESCRIPTION: Change all the color of the relation into color.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void Graph::changecolor(int c) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			relations[i][j].color = c;
		}
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: Graph::resize.
* INPUT: int w, int h.
* OUTPUT: void.
* DESCRIPTION: Resize the current graph in the way that it will fit the
width w and height h.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void Graph::resize(int w, int h) {
	Affine transformation;

	float sizex = 1, sizey = 1;

	if (w != 0) {
		sizex = (float)w / width;
	}
	if (h != 0) {
		sizey = (float)h / height;
	}

	transformation.resize(Point(item->layer->startx, item->layer->starty), sizex, sizey);

	for (int i = 0; i < n; i++) {
		points[i] = transformation.transform(points[i]);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			setrelation(i, j, relations[i][j].relate, relations[i][j].relate_savior, relations[i][j].color);
		}
	}
	
	int dx = sizex * width, dy = sizey * height;

	if (item == NULL) {
		item = new Item(NULL, NULL, NULL, 0, NULL, NULL);
	}

	if (item->layer == NULL) {
		item->layer = new Layer(item);
	}

	int	x1 = item->layer->startx, y1 = item->layer->starty,
		x2 = item->layer->startx + 1.03 * dx, y2 = item->layer->starty + 1.03 * dy;

	item->layer->startx = Min(x1, x2);
	item->layer->starty = Min(y1, y2);
	item->layer->endx = Max(x1, x2);
	item->layer->endy = Max(y1, y2);

	width = abs(dx);
	height = abs(dy);
}

void Graph::rotate(int degree) {
	Affine transformation;

	transformation.rotate(Point((item->layer->startx + item->layer->endx) / 2, (item->layer->starty + item->layer->endy) / 2), degree);

	for (int i = 0; i < n; i++) {
		points[i] = transformation.transform(points[i]);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			setrelation(i, j, relations[i][j].relate, relations[i][j].relate_savior, relations[i][j].color);
		}
	}

	Graph old_layer(4);
	old_layer.points[0] = Point(item->layer->startx, item->layer->starty);
	old_layer.points[1] = Point(item->layer->startx, item->layer->endy);
	old_layer.points[2] = Point(item->layer->endx, item->layer->endy);
	old_layer.points[3] = Point(item->layer->endx, item->layer->starty);

	for (int i = 0; i < old_layer.n; i++) {
		old_layer.points[i] = transformation.transform(old_layer.points[i]);
	}

	item->layer->startx = old_layer.getminx();
	item->layer->starty = old_layer.getminy();
	item->layer->endx = old_layer.getmaxx();
	item->layer->endy = old_layer.getmaxy();

	width = item->layer->endx - item->layer->startx + 1;
	height = item->layer->endy - item->layer->starty + 1;
}

void Graph::shear(int g, int h) {
	Affine transformation;

	transformation.shear(Point((item->layer->startx + item->layer->endx) / 2, (item->layer->starty + item->layer->endy) / 2), g, h);

	for (int i = 0; i < n; i++) {
		points[i] = transformation.transform(points[i]);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			setrelation(i, j, relations[i][j].relate, relations[i][j].relate_savior, relations[i][j].color);
		}
	}

	Graph old_layer(4);
	old_layer.points[0] = Point(item->layer->startx, item->layer->starty);
	old_layer.points[1] = Point(item->layer->startx, item->layer->endy);
	old_layer.points[2] = Point(item->layer->endx, item->layer->endy);
	old_layer.points[3] = Point(item->layer->endx, item->layer->starty);

	for (int i = 0; i < old_layer.n; i++) {
		old_layer.points[i] = transformation.transform(old_layer.points[i]);
	}

	item->layer->startx = old_layer.getminx();
	item->layer->starty = old_layer.getminy();
	item->layer->endx = old_layer.getmaxx();
	item->layer->endy = old_layer.getmaxy();

	width = item->layer->endx - item->layer->startx + 1;
	height = item->layer->endy - item->layer->starty + 1;
}

int Graph::getminx() {
	int minx = points[0].x;
	for (int i = 1; i < n; i++) {
		if (points[i].x < minx) {
			minx = points[i].x;
		}
	}
	return minx;
}

int Graph::getmaxx() {
	int maxx = points[0].x;
	for (int i = 1; i < n; i++) {
		if (points[i].x > maxx) {
			maxx = points[i].x;
		}
	}
	return maxx;
}

int Graph::getminy() {
	int miny = points[0].y;
	for (int i = 1; i < n; i++) {
		if (points[i].y < miny) {
			miny = points[i].y;
		}
	}
	return miny;
}

int Graph::getmaxy() {
	int maxy = points[0].y;
	for (int i = 1; i < n; i++) {
		if (points[i].y > maxy) {
			maxy = points[i].y;
		}
	}
	return maxy;
}

void Graph::delGraph() {
	if (points) {
		delete[] points;
	}
	if (relations) {
		for (int i = 0; i < n; i++) {
			delete[] relations[i];
		}
		delete[] relations;
	}
}

void Graph::setrelation(int i, int j, void(Relation::*relate)(), void(Relation::*relate_savior)(Scrollbar* scrollbar), int color) {
	if (j > i) {
		swap(i, j);
	}
	relations[i][j].set(points[i], points[j], relate, relate_savior, color);
}

void Graph::show() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			if (relations[i][j].relate != NULL) {
				(relations[i][j].*(relations[i][j].relate))();
			}
		}
	}
}
void Graph::exact_layer() {
	int mini = 0,
		minj = item->layer->endy - item->layer->starty;
	for (int i = 0; i < graph_image.size(); i++) {
		bool transparent = true;
		for (int j = 0; j < graph_image.at(i).size(); j++) {
			if (graph_image.at(i).at(j) == true) {
				transparent = false;
				if (j < minj) {
					minj = j;
					break;
				}
			}
		}
		if (transparent == false && mini == 0) {
			mini = i;
		}
	}
	item->layer->startx = item->layer->startx + mini;
	item->layer->starty = item->layer->starty + minj;
	mini = 0;
	minj = item->layer->endy - item->layer->starty;
	for (int i = graph_image.size() - 1; i >= 0; i--) {
		bool transparent = true;
		for (int j = graph_image.at(i).size() - 1; j >= 0; j--) {
			if (graph_image.at(i).at(j) == true) {
				transparent = false;
				if (graph_image.at(i).size() - j - 1 < minj) {
					minj = graph_image.at(i).size() - j - 1;
					break;
				}
			}
		}
		if (transparent == false && mini == 0) {
			mini = graph_image.size() - i - 1;
		}
	}
	item->layer->endx = item->layer->endx - mini;
	item->layer->endy = item->layer->endy - minj;
	width = item->layer->endx - item->layer->startx;
	height = item->layer->endy - item->layer->starty;
}

void Graph::setbelow() {
	if (below) {
		free(below);
		below = NULL;
	}
	below = malloc(imagesize(item->layer->startx, item->layer->starty, item->layer->endx, item->layer->endy));
	getimage(item->layer->startx, item->layer->starty, item->layer->endx, item->layer->endy, below);
}

void Graph::showlayer() {
	setcolor(BLACK);
	setlinestyle(DASHED_LINE, 0, NORM_WIDTH);
	rectangle(item->layer->startx, item->layer->starty, item->layer->endx, item->layer->endy);
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
}

void Graph::showsavior(Scrollbar* scrollbar) {
	//printf("Loading... Please wait.\n");
	/*if (item && item->layer == NULL) {
		item->layer = new Layer(item);
	}
	int x1 = points[0].x, y1 = points[0].y;
	item->layer->startx = x1 - width;
	item->layer->starty = y1 - height;
	item->layer->endx = x1 + width;
	item->layer->endy = y1 + height;
	if (item->layer->startx < 0) {
		item->layer->startx = 0;
	}
	if (item->layer->starty < 0) {
		item->layer->starty = 0;
	}*/

	setbelow();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			if (relations[i][j].relate_savior != NULL) {
				(relations[i][j].*(relations[i][j].relate_savior))(scrollbar);
			}
		}
	}

	/*void *image = malloc(imagesize(item->layer->startx, item->layer->starty, item->layer->endx, item->layer->endy));
	getimage(item->layer->startx, item->layer->starty, item->layer->endx, item->layer->endy, image);
	putimage(item->layer->startx, item->layer->starty, below, 0);
	putimage(item->layer->startx, item->layer->starty, image, XOR_PUT);
	int maxw = item->layer->endx - item->layer->startx,
		maxh = item->layer->endy - item->layer->starty;
	graph_image.reserve(maxw);
	for (int i = 0; i < maxw; i++) {
		vector<bool> row;
		graph_image.push_back(row);
		graph_image.at(i).reserve(maxh);
		for (int j = 0; j < maxh; j++) {
			if (getpixel(item->layer->startx + i, item->layer->starty + j) == 0) {
				graph_image.at(i).push_back(false);
			}
			else {
				graph_image.at(i).push_back(true);
			}
		}
	}
	putimage(item->layer->startx, item->layer->starty, image, 0);
	free(image);
	exact_layer();*/
	//printf("DONE.\n");
}

Graph::~Graph() {
	delGraph();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: characterA.
* INPUT: none.
* OUTPUT: void.
* DESCRIPTION: This procedure is like an A character database. What we are
trying to save is the position relation between points of A character, not 
the size (though the output Graph* can be used to draw immediately). By the
way, this character database may not be quite good.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
Graph* characterA() {
	Graph* A = new Graph(13);

	A->points[0].set(135, 0);
	A->points[1].set(60, 300);
	A->points[2].set(265, 0);
	A->points[3].set(340, 300);
	A->points[4].set(300, 300);
	A->points[5].set(275, 185);
	A->points[6].set(125, 185);
	A->points[7].set(100, 300);

	A->points[8].set(137, 150);
	A->points[9].set(157, 40);
	A->points[10].set(240, 40);
	A->points[11].set(260, 150);
	A->points[12].set(137, 150);

	A->setrelation(1, 0, &Relation::line, &Relation::line_savior, WHITE);
	A->setrelation(0, 2, &Relation::line, &Relation::line_savior, WHITE);
	A->setrelation(2, 3, &Relation::line, &Relation::line_savior, WHITE);
	A->setrelation(3, 4, &Relation::line, &Relation::line_savior, WHITE);
	A->setrelation(4, 5, &Relation::line, &Relation::line_savior, WHITE);
	A->setrelation(5, 6, &Relation::line, &Relation::line_savior, WHITE);
	A->setrelation(6, 7, &Relation::line, &Relation::line_savior, WHITE);
	A->setrelation(7, 1, &Relation::line, &Relation::line_savior, WHITE);

	A->setrelation(8, 9, &Relation::line, &Relation::line_savior, WHITE);
	A->setrelation(9, 10, &Relation::line, &Relation::line_savior, WHITE);
	A->setrelation(10, 11, &Relation::line, &Relation::line_savior, WHITE);
	A->setrelation(11, 12, &Relation::line, &Relation::line_savior, WHITE);
	A->setrelation(12, 8, &Relation::line, &Relation::line_savior, WHITE);

	A->height = 300;
	A->width = 280;

	A->item = new Item(NULL, NULL, NULL, 0, NULL, NULL);
	A->item->layer = new Layer(A->item);
	A->item->layer->startx = 50;
	A->item->layer->endx = 350;
	A->item->layer->starty = -10;
	A->item->layer->endy = 310;

	return A;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: characterB.
* INPUT: none.
* OUTPUT: void.
* DESCRIPTION: This procedure is like an B character database. What we are
trying to save is the position relation between points of B character, not
the size (though the output Graph* can be used to draw immediately). By the
way, this character database may not be quite good.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
Graph* characterB() {
	Graph* B = new Graph(14);

	B->points[0].set(0, 0);
	B->points[1].set(50, 0);
	B->points[2].set(50, 100);
	B->points[3].set(100, 100);
	B->points[4].set(100, 300);
	B->points[5].set(0, 300);

	B->points[6].set(25, 25);
	B->points[7].set(50, 25);
	B->points[8].set(50, 75);
	B->points[9].set(25, 75);

	B->points[10].set(25, 125);
	B->points[11].set(100, 125);
	B->points[12].set(25, 275);
	B->points[13].set(100, 275);

	B->setrelation(0, 1, &Relation::line, &Relation::line_savior, WHITE);
	B->setrelation(1, 2, &Relation::arc270to90, &Relation::arc270to90_savior, WHITE);
	B->setrelation(2, 3, &Relation::line, &Relation::line_savior, WHITE);
	B->setrelation(3, 4, &Relation::arc270to90, &Relation::arc270to90_savior, WHITE);
	B->setrelation(4, 5, &Relation::line, &Relation::line_savior, WHITE);
	B->setrelation(0, 5, &Relation::line, &Relation::line_savior, WHITE);

	B->setrelation(6, 7, &Relation::line, &Relation::line_savior, WHITE);
	B->setrelation(7, 8, &Relation::arc270to90, &Relation::arc270to90_savior, WHITE);
	B->setrelation(8, 9, &Relation::line, &Relation::line_savior, WHITE);
	B->setrelation(6, 9, &Relation::line, &Relation::line_savior, WHITE);

	B->setrelation(10, 11, &Relation::line, &Relation::line_savior, WHITE);
	B->setrelation(11, 13, &Relation::arc270to90, &Relation::arc270to90_savior, WHITE);
	B->setrelation(12, 13, &Relation::line, &Relation::line_savior, WHITE);
	B->setrelation(10, 12, &Relation::line, &Relation::line_savior, WHITE);

	B->height = 300;
	B->width = 200;

	B->item = new Item(NULL, NULL, NULL, 0, NULL, NULL);
	B->item->layer = new Layer(B->item);
	B->item->layer->startx = -10;
	B->item->layer->endx = 210;
	B->item->layer->starty = -10;
	B->item->layer->endy = 310;

	return B;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: characterC.
* INPUT: none.
* OUTPUT: void.
* DESCRIPTION: This procedure is like an C character database. What we are
trying to save is the position relation between points of C character, not
the size (though the output Graph* can be used to draw immediately). By the
way, this character database may not be quite good.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
Graph* characterC() {
	Graph* C = new Graph(4);

	C->points[0].set(256, 44);
	C->points[1].set(256, 256);
	C->points[2].set(238, 62);
	C->points[3].set(238, 238);

	C->setrelation(0, 2, &Relation::line, &Relation::line_savior, WHITE);
	C->setrelation(0, 1, &Relation::arc45to315, &Relation::arc45to315_savior, WHITE);
	C->setrelation(1, 3, &Relation::line, &Relation::line_savior, WHITE);
	C->setrelation(2, 3, &Relation::arc45to315, &Relation::arc45to315_savior, WHITE);

	C->height = 300;
	C->width = 260;

	C->item = new Item(NULL, NULL, NULL, 0, NULL, NULL);
	C->item->layer = new Layer(C->item);
	C->item->layer->startx = -10;
	C->item->layer->endx = 280;
	C->item->layer->starty = -10;
	C->item->layer->endy = 310;

	return C;
}