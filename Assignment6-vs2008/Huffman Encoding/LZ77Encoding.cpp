#include "LZ77Encoding.h"

//encoding method
Vector<Node*> LZ77Encode(ifstream& infile)
{
	Vector<Node*> result;
	string search = "";
	string curr = "";
	char ch;
	infile.get(ch);
	Node* node = new Node;
	node -> charachter = ch;
	node -> position = 0;
	node -> length = 0;
	search = search + ch;
	for(int i = 0; i < maxLength; i++)
	{
		infile.get(ch);
		curr += ch;
	}
	
	while(infile.get(ch))
	{
		Node* putIn = findPrefix(search, curr, ch);
		result.add(putIn);
		for(int i = 0; i <= putIn -> length; i ++)
		{
			search += curr[0];
			if(search.length() > searchSize)
				search = search.substr(1);
			curr = curr.substr(1) + ch;
		}
	}


	return result;
}

//searching curr in search and return node with longest prefix
Node* findPrefix(string search, string curr, char ch)
{
	Node* result = new Node;
	int max = 0;
	int position = 0;
	for(int i = 0; i < search.length(); i++)
		if(findCommon(search.substr(i), curr) > max)
		{
			max = findCommon(search.substr(i), curr);
			position = i;
		}

	result -> length = max;
	if(max = 0)
		position = search.length();
	result -> position = search.length() - position;
	if(max == maxLength)
		result -> charachter = ch;
	else
		result -> charachter = curr[max];

	return result;
}

//helper method for findPrefix()
int findCommon(string first, string second)
{
	int result = 0;
	while(first[result] == second[result])
	{
		result++;
		if(result == first.length())
			break;
	}
	
	return result;
}

//method for compressing
void LZ77Compress(ifstream& infile, ofbstream& outfile)
{
	Vector<Node*> nodes = LZ77Encode(infile);
	for(int i = 0; i < nodes.size(); i++)
	{
		Node* node = nodes[i];
		string positionToBin = convertToBit77(node->position, 12);
		string lengthToBin = convertToBit77(node->length, 5);
		int ch = node->charachter;
		string charachterToBin = convertToBit77(ch, 8);
		writeBits(outfile, positionToBin, lengthToBin, charachterToBin);
	}
	freeMemory(nodes);
}

//method to conver integer to binary in (bits)-bit
//we will use 12 - bit for position because it's maximum meaning in our code is 4096
//we will use 5 - bit for length because it's maximum meaning in ur code is 4
//we will use 8 - bit for charachter because it's maximum meaning in ASCII is 256
string convertToBit77(int number, int bits)
{
	string result = "";
	for(int i = 0; i < bits; i++)
		result += number & (1 << i) ? "1" : "0";

	return result;
}

//method to write bits in outfile
void writeBits(ofbstream& outfile, string positionToBin, string lengthToBin, string charachterToBin)
{
	for(int i = 0; i<positionToBin.length(); i++)
		outfile.writeBit(stringToInteger(string() + positionToBin[i]));
	
	for(int i = 0; i<lengthToBin.length(); i++)
		outfile.writeBit(stringToInteger(string() + lengthToBin[i]));
	
	for(int i = 0; i<charachterToBin.length(); i++)
		outfile.writeBit(stringToInteger(string() + charachterToBin[i]));
}

//method for decoding
Vector<Node*> LZ77Decode(ifbstream& infile)
{
	Vector<Node*> result;
	while(true)
	{
		int bit = infile.readBit();
		if(bit == EOF)
			break;
		string positionBit = integerToString(bit);
		string lengthBit = "";
		string charachterBit = "";
		for(int i = 0; i < 11; i++)
		{
			bit = infile.readBit();
			positionBit += integerToString(bit);
		}
		for(int i = 0; i < 5; i++)
		{
			bit = infile.readBit();
			lengthBit += integerToString(bit);
		}
		for(int i = 0; i < 8; i++)
		{
			bit = infile.readBit();
			charachterBit += integerToString(bit);
		}
		int Position = convertToDec(positionBit);
		int Length = convertToDec(lengthBit);
		int Charachter = convertToDec(charachterBit);
		Node* node = new Node;
		char ch = Charachter;
		node -> charachter = ch;
		node -> length = Length;
		node -> position = Position;
		result.add(node);
	}

	return result;
}

//method for decompressing
void LZ77Decompress(ifbstream& input, ofstream& output)
{
	Vector<Node*> nodes = LZ77Decode(input);
	Node* node = nodes.get(1);
	output << node -> charachter;
	
	string search = string() + node->charachter;

	for(int i = 1; i < nodes.size(); i++)
	{
		node = nodes.get(i);
		if(node->position + node->length - 1 > search.length())//this probably shouldn't come up
			throw "Something went wrong!!!";
		output<<search.substr(node -> position, node -> length);
		output<<node->charachter;
		search += search.substr(node -> position, node -> length) + node->charachter;
		while(search.length() > searchSize)
			search = search.substr(1);
	}
	
	freeMemory(nodes);
}

//method to free memory
void freeMemory(Vector<Node*> nodes)
{
	foreach(Node* node in nodes)
		delete node;
}