#ifndef LZ77Types_Included
#define LZ77Types_Included

//constant for search strings maximum size
const int searchSize = 4096;

//constans for current strings maximum size
const int maxLength = 4;

//struct to save position, length and charachter
struct Node
{
	int position;
	int length;
	char charachter;
};


#endif