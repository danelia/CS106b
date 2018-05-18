/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Consecutive Heads problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "random.h"
#include "strlib.h"
#include "simpio.h"
#include <string>

using namespace std;

/* Prototypes. */
void classicMode();

int main() {
	classicMode();
    return 0;
}


//it calculates flips until we have 3 consecutive.
void classicMode()
{
	int previous;
	int curr;
	int k = randomInteger(1,2);
	previous = k;
	curr = k;
	if(k==1)cout<<"Head"<<endl;
	if(k==2)cout<<"Tail"<<endl;

	int count = 1;

	int a = 0;
	while(a!=3)
	{
		int k = randomInteger(1,2);
		previous = curr;
		curr = k;
		if(k==1 && previous==curr ){
			cout<<"Head"<<endl;
			a++;
		}else if(k==1 && previous!=curr){
			cout<<"Head"<<endl;
			a=1;
		}
		if(k==2 && previous==curr ){
			cout<<"Tail"<<endl;
			a++;
		}else if(k==2 && previous!=curr){
			cout<<"Tail"<<endl;
			a=1;
		}
		count++;
	}
	
	string winner ="";

	if(curr = 1){
		winner = "Head";
	}else{
		winner = "Tail";
	}
	
	cout<<"It took "<<count<<" flips to get 3 consecutive "<<winner<<"."<<endl;
		
}