/*
 * File: Boggle.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the main starter file for Assignment #4, Boggle.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
using namespace std;

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;

const string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

/* Function prototypes */

void welcome();
void giveInstructions();
void askForInstuctions();
Vector<string> wantsForceCombination(int boardSize);
Grid<char> setUpBoard(GWindow& gw);
Set<string> humanTurn(Grid<char> board, Lexicon& english);
bool findWord(Grid<char> board, string wordToFind, string wordToFind2, string soFar, int row, int col, Vector<int>& cubesToHighlight);
bool isThere(Vector<int> cubesToHighlight, int numOfCube);
void highlight(Vector<int> cubesToHighlight);
void computerTurn(Grid<char> board, Lexicon& english, Set<string>& wordsHumanEntered);
void RecursiveMethodForComputerTurn(Grid<char> board, Lexicon& english, Set<string>& wordsHumanEntered, string soFar, int row, int col, Set<string>& wordsComputerFound, Vector<int>& cubesUsed);
bool refusesPlayingAgain();

/* Main program */

int main() {
	Lexicon english("EnglishWords.dat");
    GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
    initGBoggle(gw);
    welcome();
	askForInstuctions();
	while(true)
	{
		Grid<char> board = setUpBoard(gw);
		Set<string> wordsHumanEntered = humanTurn(board , english);
		computerTurn(board, english, wordsHumanEntered);
		if(refusesPlayingAgain())break;
	}
    return 0;
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}

//we ask user for instructions and tell it if they want.
void askForInstuctions()
{
	string answer;
	while(true)
	{
		answer = toLowerCase(getLine("Do you need instructions? "));
		if(answer == "yes")
		{
			giveInstructions();
			return;
		}
		else if(answer == "no")return;
		cout<<"Please answer yes or no."<<endl;;
	}
}

//we ask for board size and set up it and return grid with chars on board
Grid<char> setUpBoard(GWindow& gw)
{
	cout<<"You can choose standart Boogle (4x4 grid)"<<endl;
	cout<<"or Big Boogle (5x5)."<<endl;
	string answer;
	int boardSize;
	while(true)
	{
		answer = toLowerCase(getLine("Would you like Big Boogle? "));
		if(answer == "yes")
		{
			drawBoard(5,5);
			boardSize = 5;
			break;
		}
		else if(answer == "no")
		{
			drawBoard(4,4);
			boardSize = 4;
			break;
		}
		cout<<"Please answer yes or no."<<endl;;
	}
	//it will be empty if user doesn't want force combination
	Vector<string> combinations = wantsForceCombination(boardSize);
	Grid<char> allChars(boardSize, boardSize);	
	//and in that case we will take combinations from our constant arrays
	if(combinations.isEmpty())
	{
		if(boardSize == 4)
			foreach(string word in STANDARD_CUBES)
				combinations.add(word);
		else 
			foreach(string word in BIG_BOGGLE_CUBES)
				combinations.add(word);
	}
	
	for(int i = 0; i < combinations.size(); i++)
	{
		int x = randomInteger(i, combinations.size()-1);
		string temp = combinations[i];
		combinations[i] = combinations[x];
		combinations[x] = temp;
	}
	for(int i = 0; i < combinations.size(); i++)
	{
		int x = randomInteger(0, combinations[i].length()-1);
		char ch = combinations[i][x];
		labelCube(i/boardSize,i%boardSize,ch);
		allChars[i/boardSize][i%boardSize] = ch;
	}
	return allChars;
}

//we ask user if he/she wants to tell us combination for board and return empty vector if user doesnt want.
Vector<string> wantsForceCombination(int boardSize)
{
	cout<<"I'll give you a chance to set up the board to your specification, which makes it"<<endl;
	cout<<"easier to confirm your boggle program is working"<<endl;
	string answer;
	Vector<string> charsEntered;
	while(true)
	{
		answer = toLowerCase(getLine("Do you want to force the board configuration? "));
		if(answer == "yes")
		{
			cout<<"Enter a "<<boardSize * boardSize<<"-charachter string to identify which letters you want on cubes."<<endl;
			string chars;
			while(true)
			{
				chars = toUpperCase(getLine("Enter the string: "));
				if(chars.length() >= boardSize * boardSize)break;
				cout<<"String must include "<<boardSize * boardSize<<" charachters."<<endl;
			}
			for(int i = chars.length()-1; i>= chars.length()-boardSize * boardSize; i--)
				charsEntered.add(string()+chars[i]);
			return charsEntered;
		}
		else if(answer == "no")
			break;
		cout<<"Please answer yes or no."<<endl;;
	}
	return charsEntered;
}

//we ask user to input words and we find it on the board if it exists and record it for human
//finally we will return set with words human found.
Set<string> humanTurn(Grid<char> board, Lexicon& english)
{
	Set<string> wordsHumanEntered;
	cout<<"Ok, take all time you want and find all the words you can!"<<endl;
	cout<<"Sygnal that you're finished by entering an empty line."<<endl<<endl;
	string word;
	while(true)
	{
		word = toUpperCase(getLine("Enter a word: "));
		if(word=="")break;
		if(word.length()<4)
		{
			cout<<"I'm sorry, but we have our standarts."<<endl;
			cout<<"That word doesn't meet the minimum word length."<<endl;
			continue;
		}
		else
		{
			if(!english.contains(word))
			{
				cout<<"That's not a word!"<<endl;
				continue;
			}
			Vector<int> cubesToHighlight;
			if(findWord(board, word, word, "", 0, 0, cubesToHighlight))
			{
				recordWordForPlayer(word, HUMAN);
				highlight(cubesToHighlight);
				wordsHumanEntered.add(word);
			}
			else 
				cout<<"You can't make that word!"<<endl;
		}
	}
	return wordsHumanEntered;
}

//we recursivly find word for human
//wordToFind and wordToFind2 are both same input words, but we change the first one but don't touch second
bool findWord(Grid<char> board, string wordToFind, string wordToFind2, string soFar, int row, int col , Vector<int>& cubesToHighlight)
{
	if(soFar == wordToFind2)return true;
	//we try to find first letter
	if(soFar.length()==0)
	{
		for(int i = 0; i < board.numRows(); i++)
			for(int j = 0; j < board.numCols(); j++)
				if(board[i][j]==wordToFind[0])
				{
					soFar+=board[i][j];
					//we need to save all cubes that we allready been on and to do it we multuplay row on 10 and add column
					//so that every number will be unical for it's cube
					cubesToHighlight.add(i*10+j);
					if(findWord(board, wordToFind.substr(1), wordToFind2 , soFar, i, j, cubesToHighlight))
						return true;
					soFar = soFar.substr(0, soFar.length()-1);
					cubesToHighlight.remove(cubesToHighlight.size()-1);
				}
	}
	//after finding first letter we search for others all around the firs one and so on until we find word we are searching for.
	else
	{
		for(int i = -1; i <= 1 ; i++)
			for(int j = -1; j <= 1 ; j++)
				if(row+i>=0 && col+j>=0 && row+i<=board.numRows()-1 && col+j<=board.numCols()-1 && !isThere(cubesToHighlight, (row+i)*10+(col+j)))
					if(!(i==0 && j==0))
						if(board[row+i][col+j]==wordToFind[0])
						{
							soFar+=board[row+i][col+j];
							cubesToHighlight.add((row+i)*10+(col+j));
							if(findWord(board, wordToFind.substr(1), wordToFind2 , soFar, row+i, col+j, cubesToHighlight))
								return true;
							soFar = soFar.substr(0, soFar.length()-1);
							cubesToHighlight.remove(cubesToHighlight.size()-1);
						}

	}
	//if we can't find anything we will return false
	return false;
}

//we check vector if we already used the cube we want to go to
bool isThere(Vector<int> cubesToHighlight, int numOfCube)
{
	foreach(int num in cubesToHighlight)
		if(num == numOfCube)
			return true;
	return false;
}

//we highligh cubes human guessed
void highlight(Vector<int> cubesToHighlight)
{
	for(int i = 0; i < 2; i++)
	{
		bool flag = (i%2==0) ? true:false;
		foreach(int num in cubesToHighlight)
			highlightCube(num/10,num%10,flag);
		pause(500);
	}
}

//after human turn its computers turn and we find all left words on board
void computerTurn(Grid<char> board, Lexicon& english, Set<string>& wordsHumanEntered)
{
	Set<string> wordsComputerFound;
	Vector<int> cubesUsed;
	RecursiveMethodForComputerTurn(board, english, wordsHumanEntered , "", 0, 0, wordsComputerFound, cubesUsed);
}

//this is helper method for computer turn, simmilar for findWord for human
void RecursiveMethodForComputerTurn(Grid<char> board, Lexicon& english, Set<string>& wordsHumanEntered , string soFar, int row, int col, Set<string>& wordsComputerFound, Vector<int>& cubesUsed)
{
	if(soFar.length()==0)
	{
		for(int i = 0; i < board.numRows(); i++)
			for(int j = 0; j < board.numCols(); j++)
			{
				soFar+=board[i][j];
				cubesUsed.add(i*10 + j);
				RecursiveMethodForComputerTurn(board, english, wordsHumanEntered, soFar, i , j, wordsComputerFound, cubesUsed);
				cubesUsed.remove(cubesUsed.size()-1);
				soFar=soFar.substr(0, soFar.length()-1);
			}
	}
	else
	{
		for(int i = -1; i <= 1 ; i++)
			for(int j = -1; j <= 1 ; j++)
				if(row+i>=0 && col+j>=0 && row+i<=board.numRows()-1 && col+j<=board.numCols()-1 && !isThere(cubesUsed, (row+i)*10+(col+j)))
					if(!(i==0 && j==0))
					{
						soFar+=board[row+i][col+j];
						cubesUsed.add((row+i)*10+(col+j));
						if(soFar.length() >= 4 && english.contains(soFar) && !wordsHumanEntered.contains(soFar) && !wordsComputerFound.contains(soFar))
						{
							recordWordForPlayer(soFar, COMPUTER);
							wordsComputerFound.add(soFar);
						}
						if(english.containsPrefix(soFar))
							RecursiveMethodForComputerTurn(board, english, wordsHumanEntered, soFar, row+i , row+j, wordsComputerFound, cubesUsed);
						
						soFar = soFar.substr(0, soFar.length()-1);
						cubesUsed.remove(cubesUsed.size()-1);
					}

	}
}

//finally we ask user if he/she wants to play again
bool refusesPlayingAgain()
{
	string answer;
	while(true)
	{
		answer = toLowerCase(getLine("Do you want to play again? "));
		if(answer == "yes")
			return false;
		if(answer == "no")
			return true;
		cout<<"Please answer yes or no."<<endl;
	}
	return false; //it's not useful and code will not ever come to this line, but why delete this? it doesnt make harm.
}