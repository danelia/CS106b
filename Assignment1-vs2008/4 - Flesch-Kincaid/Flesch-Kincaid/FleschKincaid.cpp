/*
 * File: FleschKincaid.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Flesch-Kincaid problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "simpio.h"
#include "tokenscanner.h"

using namespace std;

/* constant doubles. */
const double C0=-15.59;
const double C1=0.39;
const double C2=11.8;

/* Prototypes. */
void initialProgram(bool &debugInf);
void openFile(ifstream &stream);
void readFile(ifstream &stream, bool debugInf,int &words,int &sentences,int &syllables);
int numberOfSyllables(string str);
void finalizeProgram(int words,int sentences,int syllables);

int main() {
	ifstream file;
	bool debugInf=false;
	initialProgram(debugInf);
	openFile(file);
	int words = 0;
	int sentences = 0;
	int syllables = 0;
	readFile(file, debugInf,words,sentences,syllables);
	finalizeProgram(words,sentences,syllables);
	file.close();

    return 0;
}

//we ask if user wants debug information.
void initialProgram(bool &debugInf)
{
	while(true)
	{
		string init = toLowerCase(getLine("Show debug information? "));
		if(init == "yes" || init=="no")
		{
			debugInf = (init == "yes");
			break;
		}
		cout<<"Please enter yes or no."<<endl;
	}

}

//we ask user for file until the file name is valid.
void openFile(ifstream &stream)
{	
	string line;
	string fileName;
	while(true)
	{
		fileName = getLine("Enter input file name: ");
		stream.open(fileName.c_str());
		if(stream.fail())
		{
			stream.clear();
			cout<<"Unable to open file named "<<'\"'<<fileName<<'\"'<<". Try again."<<endl;
		}else
		{
			break;
		}
	}
}


//we read file anc count words sentences and the whole number of syllables. 
//if they want debug information than we tell tham everything about each token.
void readFile(ifstream &stream, bool debugInf,int &words,int &sentences, int &syllables)
{
	TokenScanner scanner(stream);
	scanner.addWordCharacters("'");
	scanner.ignoreWhitespace();
	while(scanner.hasMoreTokens())
	{
		string token = scanner.nextToken();
		if(isalpha(token[0]))
		{
			words++;
			syllables +=numberOfSyllables(token);
			if(debugInf)cout<<"Token : ["<<token<<"]  "<<"(word; "<<numberOfSyllables(token)<<" syllable(s))"<<endl;
		}else if(token[0]=='\.' || token[0]=='\?' || token[0]=='\!')
		{
			sentences++;
			if(debugInf)cout<<"Token : ["<<token<<"]  "<<"(end of sentence)"<<endl;
		}else
		{
			if(debugInf)cout<<"Token : ["<<token<<"]"<<endl;
		}
	}
}


//returns true if the char is vowel.
bool isVowel(char ch)
{
	if(ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' || ch == 'y' )return true;
	return false;
}


//we calculate number of syllables for only current string.
int numberOfSyllables(string str)
{
	
	for(int i = 0; i<str.length();)
	{
		if(isVowel(tolower(str[i])) && isVowel(tolower(str[i+1])))
		{
			str = str.substr(0,i)+str.substr(i+1);
			continue;
		}
		if(str[str.length()-1]=='e')
		{
			str = str.substr(0,str.length()-1);
			continue;
		}
		i++;
	}
	int counter = 0;
	for(int i = 0; i<str.length(); i++)
	{
		if(isVowel(tolower(str[i])))counter++;
	}
	
	if(counter==0)return 1;
	return counter;
}


//we finalize program by counting the final grade.
//with next formula : grad = C0+C1*(words/sentences)+C2*(syllables/words)
void finalizeProgram(int words,int sentences,int syllables)
{
	if(words == 0)words++;
	if(sentences == 0)sentences++;
	cout<<"Words: "<<words<<endl;
	cout<<"Syllables: "<<syllables<<endl;
	cout<<"Sentences: "<<sentences<<endl;

	double grade = C0+C1*((double)words/sentences)+C2*((double)syllables/words);
	cout<<"Grade level: "<<grade<<endl;
}