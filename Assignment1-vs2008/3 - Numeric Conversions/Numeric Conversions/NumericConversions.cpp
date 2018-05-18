/*
 * File: NumericConversions.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Numeric Conversions problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include <cmath>
#include "simpio.h"
using namespace std;

/* Function prototypes */

string intToString(int n);
int stringToInt(string str);	

/* Main program */

int main() {
    // [TODO: fill in the code]
    return 0;
}

//transfering int to string
string intToString(int n)
{
	if(n==0)return "0";
	if(n<10 && n>0)return string()+char(n+'0');
	if(n>-10 && n<0)return "-" + string()+char(-n+'0');
	if(n<-10)return "-" +intToString(-n/10) + string()+char(-n%10+'0');
	return intToString(n/10)+string()+char(n%10+'0');
}

//transfering string to int
int stringToInt(string str)
{
	if(str == "0") return 0;
	if(str.length()==1) return str[0]-'0';
	if(str[0]=='-')return stringToInt(str.substr(1,str.length()-1))*(-1);
	return (str[0]-'0')*(powf(10,str.length()-1)) + stringToInt(str.substr(1,str.length()-1));
}