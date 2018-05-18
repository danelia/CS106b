/*
 * File: Sierpinski.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Sierpinski problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <cmath>
#include "gwindow.h"
#include "console.h"
#include "simpio.h"
using namespace std;

void drawSierpinski(GWindow &gw, int count, int model, int length, GPoint startingPoint);

int main() {
	int model = getInteger("Enter model number: ");
	double triangleLength = getReal("Enter triangle edge length: ");
	//not necessary but more comfortable.
	double width = getReal("Enter width of window: ");
	double height = getReal("Enter height of window: ");
	GWindow gw(width, height);
	
	
	GPoint startingPoint((gw.getWidth()-triangleLength)/2, (gw.getHeight()+triangleLength)/2);

	drawSierpinski(gw, 0, model, triangleLength, startingPoint);
    return 0;
}

void drawSierpinski(GWindow &gw, int count, int model, int length, GPoint startingPoint)
{
	//if count is equal to model number it means its last triangle and we will draw it.
	if(count == model)
	{
		GPoint firstP = gw.drawPolarLine(startingPoint, length, 0);
		GPoint secondP = gw.drawPolarLine(firstP, length, 120);
		gw.drawPolarLine(secondP, length, -120);
	}else
	{
		length = length/2;
		count++;
		//point for recursive step for left triangle
		GPoint secondP(startingPoint.getX() + length, startingPoint.getY());
		//point for recursive step for top triangle
		//we want our last triangle to go up with the height of triangles and the formula for height 
		//is base/2*sqrt(3)
		GPoint lastP(secondP.getX()-length/2, secondP.getY() - length/2 * sqrt(3.0));

		//we draw 3 little triangles for left corner, right corner and top
		drawSierpinski(gw, count, model, length, startingPoint);
		drawSierpinski(gw, count, model, length, secondP);
		drawSierpinski(gw, count, model, length, lastP);
	}
}