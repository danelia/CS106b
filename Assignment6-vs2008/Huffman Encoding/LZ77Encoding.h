#ifndef LZW77Encoding_Included
#define LZW77Encoding_Included

#include "LZ77Types.h"
#include "vector.h"
#include "bstream.h"
#include <math.h>
#include <fstream>
#include "strlib.h"
#include "LZWEncoding.h"

//encoding method
Vector<Node*> LZ77Encode(ifstream& infile);
//searching curr in search and return node with longest prefix
Node*  findPrefix(string search, string curr, char ch);
//helper method for findPrefix()
int findCommon(string first, string second);

//method for compressing
void LZ77Compress(ifstream& infile, ofbstream& outfile);
//method to conver integer to binary in (bits)-bit
string convertToBit77(int number, int bits);
//method to write bits in outfile
void writeBits(ofbstream& outfile, string positionToBin, string lengthToBin, string charachterToBin);

//method for decoding
Vector<Node*> LZ77Decode(ifbstream& infile);
//method for decompressing
void LZ77Decompress(ifbstream& input, ofstream& output);

//method to free memory
void freeMemory(Vector<Node*> nodes);

#endif