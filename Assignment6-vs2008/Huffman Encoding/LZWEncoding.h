#ifndef LZWEncoding_Included
#define LZWEncoding_Included

#include "map.h"
#include <fstream>
#include "strlib.h"
#include "bstream.h"
#include <math.h>

//method to compress file with lzw algorithm
void LZWCompress(ifstream& infile, ofbstream& outfile);

//method to decompress file with lzw algorithm
void LZWDecompress(ifbstream& infile, ofstream& outfile);

//method to convert integer to binary(we use 12-bit)
string convertToBit(int number);

//method to convert bindary to decimal
int convertToDec(string number);

#endif