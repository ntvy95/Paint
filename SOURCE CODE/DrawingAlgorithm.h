/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*COLLECTION: DrawingAlgorithm.
*DESCRIPTION: All the custom drawing procedures are stored here.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma once
#include "Scrollbar.h"
#include <vector>
#include "Point.h"
using std::vector;

/* Procedures for line drawing */
void LineBresenham(int x1, int y1, int x2, int y2, int color);
void SquareBresenham(int x1, int y1, int a, int color);
void SquareBresenham(int x1, int y1, int x2, int y2, int color);

/* Procedures for circle drawing */
void Put8(int a, int b, int x, int y, int color);
void CircleMidpoint(int a, int b, int R, int color); 
void CircleMidpoint(int x1, int y1, int x2, int y2, int color);
void ArcMidpoint(int a, int b, int stangle, int endangle, int R, int color);
void ArcPut8right(int x, int y, int a, int b, int stangle, int endangle, int R, int color);
void ArcPut8left(int x, int y, int a, int b, int stangle, int endangle, int R, int color); 
void EllipseMidpoint(int h, int k, int a, int b, int color);
void EllipsePut4(int x, int y, int h, int k, int color);
void Parabol(float a, int h, int k, int x, int color);
void ParabolPut2(int x, int y, int h, int k, int color);
void Bezier(vector<Point> control, int color);
void BezierPut(double t, vector<Point> control, vector<Point>& lines, int color);

/*Coloring*/
void Fill(int x, int y, int fillcolor, Scrollbar* scrollbar);

/*Saviors - Our heros*/
void LineBresenhamSavior(int x1, int y1, int x2, int y2, int color, Scrollbar* scrollbar);
void SquareBresenhamSavior(int x1, int y1, int x2, int y2, int color, Scrollbar* scrollbar);
void CircleMidpointSavior(int a, int b, int R, int color, Scrollbar* scrollbar);
void CircleMidpointSavior(int x1, int y1, int x2, int y2, int color, Scrollbar* scrollbar);
void Put8Savior(int a, int b, int x, int y, int color, Scrollbar* scrollbar);
void ArcMidpointSavior(int a, int b, int stangle, int endangle, int R, int color, Scrollbar* scrollbar);
void ArcPut8right(int x, int y, int a, int b, int stangle, int endangle, int R, int color, Scrollbar* scrollbar);
void ArcPut8leftSavior(int x, int y, int a, int b, int stangle, int endangle, int R, int color, Scrollbar* scrollbar);
void ArcPut8rightSavior(int x, int y, int a, int b, int stangle, int endangle, int R, int color, Scrollbar* scrollbar);
void SquareBresenhamSavior(int x1, int y1, int a, int color, Scrollbar* scrollbar);
void EllipseMidpointSavior(int h, int k, int a, int b, int color, Scrollbar* scrollbar);
void EllipsePut4Savior(int x, int y, int h, int k, int color, Scrollbar* scrollbar);
void ParabolSavior(float a, int h, int k, int x, int color, Scrollbar* scrollbar);
void ParabolPut2Savior(int x, int y, int h, int k, int color, Scrollbar* scrollbar);
void BezierPutSavior(double t, vector<Point> control, vector<Point>& lines, int color, Scrollbar* scrollbar);
void BezierSavior(vector<Point> control, int color, Scrollbar* scrollbar);