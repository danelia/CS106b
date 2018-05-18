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

/* prototypes */
void classicMode();
string initProgram();
void adventureMode();

int main() {
	string mode = initProgram();
	while(mode == "again")
	{
		cout<<"Enter valid choice."<<endl;
		mode = initProgram();
	}
	if(mode == "c")classicMode();
	if(mode == "a")adventureMode();
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

//we ask user to choose mode or aks for help. if user's input something more
//we return again to know this. and in main ask again.
string initProgram()
{
	string line = toLowerCase(getLine("Choose mode(c for classic, a for adventure, h for help): "));
	if(line=="c")return "c";
	if(line=="a")return "a";
	if(line=="h")
	{
		cout<<"Classic mode is when u wait for 3 consecutive sides and "<<endl;
		cout<<"adventure is when u tell us what u want to wait."<<endl;
		return initProgram();
	}
	return "again";
}


//we wait for user input and calculate flips until its same as users choice.
void adventureMode()
{
	string input = toLowerCase(getLine("Enter sequence you want(h for head and t for tail, f.e. hhtht): "));
	for(int i = 0; i<input.length();)
	{
		if(input[i]!='h' && input[i]!='t')
		{
			cout<<"Enter only h or t."<<endl;
			input = toLowerCase(getLine("Enter sequence you want(h for head and t for tail, f.e. hhtht): "));
			i=0;
			continue;
		}
		i++;
	}
	int flips = 0;
	string comenSides = "";
	while(comenSides != input)
	{
		int k = randomInteger(1,2);
		if(k == 1)
		{
			cout<<"Head"<<endl;
			comenSides += "h";
			flips++;
		}else if(k==2)
		{
			cout<<"Tail"<<endl;
			comenSides += "t";
			flips++;
		}
		if(comenSides.length()>input.length())comenSides = comenSides.substr(1);
	}

	cout<<"It took "<<flips<<" flips to get your choice: "<<'\"'<<toUpperCase(input)<<'\"'<<"."<<endl;
}