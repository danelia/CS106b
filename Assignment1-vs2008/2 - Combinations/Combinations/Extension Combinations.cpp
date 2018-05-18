/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <iomanip>
#include <string>
#include "console.h"
#include "gwindow.h"
#include "gobjects.h"
#include "simpio.h"
#include "strlib.h"
using namespace std;

/* Prototypes/ */
int C(int n, int k);

int main() {
	//we add canvas.
	GWindow gw;
	int l = getInteger("Enter number of rows: ");
	string font = "SansSerif-"+integerToString(gw.getHeight()/l);
	for(int i=0; i<l; i++)
	{
		cout<<setw(l-i);
		for(int j=0; j<=i; j++)
		{
			//we draw pyramid on console and on cavas.
			cout<<C(i,j)<<" ";
			GLabel *label = new GLabel("  "+integerToString(C(i,j))+"  ");
			label->setFont(font);
			gw.add(label,(gw.getWidth()/2-(label->getWidth())*(j+1)+label->getWidth()/2*i)+label->getWidth()/2,(i+1)*(label->getFontAscent()));
		}
		cout<<endl;
	}

    return 0;
}

//we calculate C with recursion.
int C(int n, int k)
{
	if(k==0 || n==k)return 1;
	return C(n-1, k-1)+C(n-1, k);
}