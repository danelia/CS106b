#include "LZWEncoding.h"

//method to convert integer to binary(we use 12-bit)
string convertToBit(int number)
{
	string result = "";
	for(int i = 0; i < 12; i++)
		result += number & (1 << i) ? "1" : "0";

	return result;
	
}

//method to convetr binary to decimal
int convertToDec(string number)
{
	int result = 0;
	for(int i = number.length()-1; i >= 0; i--)
		result += stringToInteger(string()+number[i]) * pow(2.0, (double)i);
	return result;
}

//method to compress file with lzw algorithm
void LZWCompress(ifstream& infile, ofbstream& outfile)
{
	Map<string, int> dictionary;
	for(int i = 0; i < 256; i++)
		dictionary[string(1,i)] = i;
	
	string first;
	int dictionarySize = 256;
	char ch;
	while(infile.get(ch))
	{
		char second = ch;
		string bla = first + second;
		if(dictionary.containsKey(bla))
			first = bla;
		else
		{
			int index = dictionary[first];
			string output = convertToBit(index);
			for(int i = 0; i < output.length(); i++)
				outfile.writeBit(stringToInteger(string() + output[i]));
			dictionary[bla] = dictionarySize++;
			first = string() + second;
		}
	}
	int index = dictionary[first];
	string output = convertToBit(index);
	for(int i = 0; i < output.length(); i++)
		outfile.writeBit(stringToInteger(string() + output[i]));
}

//method to decompress file with lzw algorithm
void LZWDecompress(ifbstream& infile, ofstream& outfile)
{
	Map<int, string> dictionary;
	for(int i = 0; i < 256; i++)
		dictionary[i] = string(1,i);

	int dictionarySize = 256;
	
	string firstThingToOutPut = "";
	for(int i = 0; i < 12; i++)
		firstThingToOutPut += (infile.readBit() == 1) ? "1" : "0";

	string prevcode = dictionary[convertToDec(firstThingToOutPut)];
	outfile << prevcode;
	string entry;
	while(true)
	{
		string currcode = "";
		int bit = infile.readBit();
		if(bit == EOF)
			break;
		currcode += (bit == 1) ? "1" : "0";
		for(int i = 0; i < 11; i++)
			currcode += (infile.readBit() == 1) ? "1" : "0";
		if(dictionary.containsKey(convertToDec(currcode)))
			entry = dictionary[convertToDec(currcode)];
		else if(convertToDec(currcode) == dictionarySize)
			entry = prevcode + prevcode[0];
		else
			throw "Bad compression";
		outfile<<entry;
		dictionary[dictionarySize++] = prevcode+entry[0];
		prevcode = entry;
	}

}
