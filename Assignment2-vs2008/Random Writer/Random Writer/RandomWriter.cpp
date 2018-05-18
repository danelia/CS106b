/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Writer problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include <iterator>
#include "console.h"
#include "simpio.h"
#include "strlib.h"
#include "filelib.h"
#include "vector.h"
#include "map.h"
#include "random.h"

using namespace std;

/* Function Prototipes */
void openFile(ifstream &stream);
void readText(ifstream &stream, int markov, Map<string, Vector<char>> &all);
void writeText(Map<string, Vector<char>> &all);
char getNextChar(Map<string, Vector<char>> &all, string str);

int main()
{
	ifstream stream;
	openFile(stream);
	int markov;
	while(true)
	{
		markov = getInteger("Enter the Markov number[1-10]: ");
		if(markov<1 || markov>10) cout<<"That value is out of range."<<endl;
		else break;
	}
	cout<<"Processing file..."<<endl;
	Map<string, Vector<char>> all;
	readText(stream, markov, all);
	stream.close();
	writeText(all);
	return 0;
}


//Opens stream for filename user entered.
void openFile(ifstream &stream)
{	
	string fileName;
	while(true)
	{
		fileName = getLine("Enter input file name: ");
		stream.open(fileName.c_str());
		if(stream.fail())
		{
			stream.clear();
			cout<<"Unable to open file named "<<'\"'<<fileName<<'\"'<<". Try again."<<endl;
		}else break;
	}
}


//Reads text and put strings and vextors in map.
void readText(ifstream &stream, int markov, Map<string, Vector<char>> &all)
{
	char c;
	string word;
	while(stream.get(c))
	{
		word += c;
		if(word.length()==markov)
		{
			stream.get(c);
			char v = c;
			stream.putback(c);
			if(!all.containsKey(word))
			{
				Vector<char> value;
				value.add(v);
				all.put(word, value);
			}else 
			{
				Vector<char> value = all.get(word);
				value.add(v);
				all.put(word, value);
			}
			word = word.substr(1);
		}
	}
}

//writes text.
void writeText(Map<string, Vector<char>> &all)
{
	//we get longest vector to know with wich string we should start.
	string first;
	int max = 0;
	Map<string,Vector<char>>::iterator it;
	for (it = all.begin(); it != all.end(); it++)
	{
		if(all.get(*it).size()>max)
		{
			max = all.get(*it).size();
			first = *it;
		}
	}
	//we count our symbols, because we want program to end at 2000 symbol
	int count = first.length();
	cout<<first;
	while(count<2000)
	{
		//if there aren't anything more to write we will end program.
		if(!all.containsKey(first)) break;
		char c = getNextChar(all, first);
		cout<<c;
		count ++;
		first = first.substr(1)+c;
	}

	cout<<endl;
	
	
}

//we get next char that sould be written.
char getNextChar(Map<string, Vector<char>> &all, string str)
{
	Vector<char> allChar = all.get(str);
	int	i = randomInteger(0, allChar.size()-1);

	return allChar.get(i);
}