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
string toRoman(int k);

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

//we transfer ints to roman numerals.
string toRoman(int k)
{
	string result = "";
	//if its more than 1000 we put M.
	if(k>=1000)
	{
		for(int i = 0; i < k/1000; i++)
		{
			result+="M";
		}
		k %= 1000;
	}
	if(k>=100)
	{
		if(k/100 == 9)
		{
			result += "CM";
		}else if(k/100 >= 5)
		{
			result += "D";
			for(int i = 0; i < k/100 - 5; i++)result += "C";
		}else if(k/100 == 4)
		{
			result += "CD";
		}else if(k/100 >= 1)
		{
			for(int i = 0; i < k/100; i++)result+="C";
		}
		k %= 100;
	}
	if(k>=10)
	{
		if(k/10 == 9)
		{
			result += "XC";
		}else if(k/10 >= 5)
		{
			result += "L";
			for(int i = 0; i < k/10 - 5; i++)result += "X";
		}else if(k/10 == 4)
		{
			result+="XL";
		}else if(k/10 >=1)
		{
			for(int i = 0; i <k/10; i++)result += "X";
		}
		k %= 10;
	}
	if(k >=1)
	{
		if(k == 9)
		{
			result += "IX";
		}else if(k >= 5)
		{
			result += "V";
			for(int i=0; i < k - 5; i++)result += "I";
		}else if(k == 4)
		{
			result += "IV";
		}else if(k >= 1)
		{
			for(int i = 0; i< k; i++)result += "I";
		}
	}
	return result;
}
