/*
 * File: WordLadder.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Word Ladder problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "simpio.h"
#include "console.h"
#include "lexicon.h"
#include "vector.h"
#include "queue.h"
#include "set.h"

using namespace std;

/* Function prototypes */
string findNextWord(string word, Lexicon dictionary, Set<string> alreadyUsed);
void findLadder(Lexicon dictionary, string startWord, string endWord);

int main() {
	//initialize lexicon of words.
	Lexicon english("EnglishWords.dat");
	while(true)
	{
		//we ask user for starting and ending words.
		string start = toLowerCase(getLine("Enter the starting word(or nothing to quit): "));
		if(start=="")
		{
			cout<<"Goodbye!"<<endl;
			break;
		}
		string end = toLowerCase(getLine("Enter the ending word: "));
		cout<<"Searching..."<<endl;
		//with those word and lexicon we try to find ladder.
		findLadder(english, start, end);
	}

	return 0;
}


//we find next word.
string findNextWord(string word, Lexicon dictionary, Set<string> alreadyUsed)
{
	string newWord;
	for (int i =0; i < word.length(); i++)
	{
		newWord = word;
		for (char ch = 'a'; ch <= 'z'; ch++)
		{
			newWord = newWord.replace(i,1,1, ch);
			if (dictionary.contains(newWord))
				if (!alreadyUsed.contains(newWord))
					return newWord;
		}
	}
	return "";
}


void findLadder(Lexicon dictionary, string startWord, string endWord)
{
	//initializing queue, set of used words and string to get next word.
	Queue<Vector<string> > queue;
	Set<string> alreadyUsed;
	string nextStr;
 
	queue.clear();
	//vector that we will be adding in queue.
	Vector<string> addToQueue;
	addToQueue.add(startWord);
	//start the queue.
	queue.enqueue(addToQueue);
 
	while (true)
	{
		//if queue is empty, it means there is no ladder.
		if (queue.size() ==0)
		{
			cout << "No word ladder could be found."<< endl;
			break;
		}
		//we get vector from the queue.
		Vector<string> newString = queue.dequeue();
		while (true)
		{
			//we find the next word to use.
			nextStr = findNextWord(newString[newString.size()-1], dictionary, alreadyUsed);
			//if this word is endWord we we output ladder.
			if (nextStr == endWord) 
			{
				cout << "Ladder found: ";
				foreach (string list in newString)
				{
					cout << list << " - ";
				}
				cout << endWord << endl << endl;
				//after oll is done we will get out of the void.
				return;
			} else if (nextStr != "")
			{
				//otherwise, if there is another word to search with add to the end of the list.
				Vector<string> addMore = newString;
				addMore.add(nextStr);
				queue.enqueue(addMore);
			}
			//else if nothing left to search for, stop.
			else if (nextStr =="")
				break;
			//at the end of loop we add this word to the set of used words.
			alreadyUsed.add(nextStr);
		}
	}
}
